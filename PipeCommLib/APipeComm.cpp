#include "stdafx.h"
#include "APipeComm.h"
#include <Windows.h>
#include <iostream>
#include <algorithm>

using namespace std;

APipeComm::APipeComm()
{
	mName = "";
	mBufLen = 0;
	pPipe = INVALID_HANDLE_VALUE;
	pThreadHandle = INVALID_HANDLE_VALUE;
}


DWORD __stdcall APipeComm::ThreadRun(LPVOID lpParam)
{
	shared_ptr<APipeComm> sPtr
		= shared_ptr<APipeComm>(
		(APipeComm*)lpParam);
	sPtr->Loop();
	return 0;
}


void APipeComm::InitializePipe()
{
	pPipe = INVALID_HANDLE_VALUE;

	// try open
	string pipeNameFormat = "\\\\.\\pipe\\";
	pipeNameFormat += mName;

	wstring wPipeNameFormat = str2wstr(pipeNameFormat);

	pPipe = CreateFile(
		wPipeNameFormat.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (pPipe != INVALID_HANDLE_VALUE)
	{
		cout << Name() << " pipe opened." << endl;
		return;
	}

	// was not opened, create one
	pPipe = CreateNamedPipe(
		wPipeNameFormat.c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		mBufLen,
		mBufLen,
		0,
		NULL);

	if (pPipe != INVALID_HANDLE_VALUE)
	{
		cout << Name() << " pipe created." << endl;
		return;
	}

	cout << "ERROR!" << Name() << " pipe could not be opened nor created." << endl;
}

wstring APipeComm::str2wstr(string str)
{
	std::wstring str2(str.length(), L' '); // Make room for characters

	// Copy string to wstring.
	std::copy(str.begin(), str.end(), str2.begin());
	return str2;
}

void APipeComm::Loop()
{
	ConnectNamedPipe(pPipe, NULL);

	while (IsRunning())
	{
		Action();
		// May even be alright to remove this
		//Sleep(1);
	}

	DisconnectNamedPipe(pPipe);
}

APipeComm::APipeComm(DWORD mode,
	std::string uniqueName,
	IMessage * msg,
	size_t bufLen)
{
	mMode = mode;
	mName = uniqueName;
	mBufLen = bufLen;
	pMsg = msg;
	mIsRunning = FALSE;
	pPipe = INVALID_HANDLE_VALUE;

	InitializeCriticalSection(&mLockMech);
}

APipeComm::~APipeComm()
{
	mIsRunning = FALSE;
	//pMsg.reset();
	// TO DO: clear all handles
	if (pThreadHandle != INVALID_HANDLE_VALUE)
		CloseHandle(pThreadHandle);
	if (pPipe != INVALID_HANDLE_VALUE)
		CloseHandle(pPipe);

	DeleteCriticalSection(&mLockMech);
}

BOOL APipeComm::IsRunning()
{
	BOOL result = FALSE;

	EnterCriticalSection(&mLockMech);
	result = mIsRunning;
	LeaveCriticalSection(&mLockMech);

	return result;
}

string APipeComm::Name()
{
	return mName;
}


void APipeComm::Start()
{
	if (IsRunning() == TRUE)
	{
		cout << Name() << " is already running. Ignoring Start()" << endl;
		return;
	}

	// initialize pipe
	InitializePipe();

	if (pPipe == INVALID_HANDLE_VALUE)
	{
		cout << Name() << " cannot start. Invalid pipe." << endl;
		return;
	}

	// set isRunning to true
	EnterCriticalSection(&mLockMech);
	mIsRunning = TRUE;

	// create and run the thread
	pThreadHandle = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ThreadRun,				// thread function name
		this,					// argument to thread function 
		0,                      // use default creation flags 
		0);   // returns the thread identifier 
	LeaveCriticalSection(&mLockMech);

}

void APipeComm::Stop()
{
	if (IsRunning() == FALSE)
	{
		cout << Name() << " is already stopped. Ignoring Stop()" << endl;
		return;
	}

	EnterCriticalSection(&mLockMech);
	// set isRunning to FALSE
	mIsRunning = FALSE;
	LeaveCriticalSection(&mLockMech);
	// wait a few ms to assure 
	// loop ended	
	Sleep(50);

	//EnterCriticalSection(&mLockMech);
	// close thread handle
	//CloseHandle(pThreadHandle);
	// close pipe handle
	//CloseHandle(pPipe);
	//LeaveCriticalSection(&mLockMech);
}

void APipeComm::Reset()
{
	Stop();
	Start();
}
