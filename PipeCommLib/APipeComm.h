#pragma once
#include <string>
#include <memory>
#include <Windows.h>

class IMessage;

// abstract class for pipe communication
class APipeComm
{
private:
	std::string mName;
	DWORD mMode;

	APipeComm();
protected:
	DWORD mBufLen;
	HANDLE pPipe;				// main pipe handle
	HANDLE pThreadHandle;		// main thread handle
	BOOL mIsRunning;			// indicates if the main loop is running
	CRITICAL_SECTION mLockMech;

	IMessage * pMsg;  // message to be sent out (buffer)

	const std::string CLOSE = "close";

	// function threads
	static DWORD WINAPI ThreadRun(LPVOID lpParam);

	// attemps to open a pipe (assuming already created). 
	// if pipe not created, create a new one
	void InitializePipe();

	std::wstring str2wstr(std::string str);

	// called by the ThreadRun static function
	void Loop();

	// called by the Loop function.
	// this is completely implemented by the 
	// derived classes
	virtual void Action() {}

	APipeComm(DWORD mode,
			std::string uniqueName,
			IMessage * msg, 
			size_t bufLen);
public:
	virtual ~APipeComm();

	BOOL IsRunning();
	std::string Name();

	void Start();
	void Stop();
	void Reset();
};

