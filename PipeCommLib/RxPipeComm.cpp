#include "stdafx.h"
#include "PipeComm.h"
#include "APipeComm.h"
#include <sstream>
#include <iostream>

using namespace std;

//****************************************************************
// ImplRxPipeComm
//****************************************************************
class RxPipeComm::ImplRxPipeComm
	: public APipeComm
{
public:
	ImplRxPipeComm(string name
		, IMessage* msg
		, size_t bufLen);
	~ImplRxPipeComm();

	void Action();
	IMessage* Get();
};

RxPipeComm::ImplRxPipeComm::ImplRxPipeComm(string name
	, IMessage* msg, size_t bufLen)
	: APipeComm(PIPE_ACCESS_INBOUND, name, msg, bufLen)
{
}

RxPipeComm::ImplRxPipeComm::~ImplRxPipeComm()
{
}

void RxPipeComm::ImplRxPipeComm::Action()
{
	char * buff = new char[mBufLen];
	DWORD numBytesToRead = 0;
	EnterCriticalSection(&mLockMech);
	// read the content
	BOOL success = ReadFile(pPipe,
		buff,
		mBufLen,
		&numBytesToRead,
		NULL);

	// store data inside a IMessage
	// remove uncessary lines
	string str = "";
	for (size_t i = 0; i < numBytesToRead; i++)
		str += buff[i];
	pMsg->ToStruct(str);

	LeaveCriticalSection(&mLockMech);

	if (success == FALSE)
	{
		cout << Name() << " server probably ended. Stopping..." << endl;
		Stop();
	}

	delete buff;
}

IMessage* RxPipeComm::ImplRxPipeComm::Get()
{
	return pMsg;
}


//****************************************************************
// RxPipeComm
//****************************************************************

RxPipeComm::RxPipeComm(std::string name, 
	IMessage* msg, 
	size_t bufLen)
{
	pImpl = shared_ptr<ImplRxPipeComm>(
		new ImplRxPipeComm(name, msg, bufLen));
}

RxPipeComm::~RxPipeComm()
{
}

IMessage* RxPipeComm::Get()
{
	return pImpl->Get();
}

void RxPipeComm::Start()
{
	pImpl->Start();
}

void RxPipeComm::Stop()
{
	pImpl->Stop();
}

void RxPipeComm::Reset()
{
	pImpl->Reset();
}

BOOL RxPipeComm::IsRunning()
{
	return pImpl->IsRunning();
}
