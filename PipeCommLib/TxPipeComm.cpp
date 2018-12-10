#include "stdafx.h"
#include "PipeComm.h"
#include "APipeComm.h"
#include <sstream>
#include <iostream>

using namespace std;

//**************************************************************
// ImplTxPipeComm
//**************************************************************
class TxPipeComm::ImplTxPipeComm
	: public APipeComm
{
public:
	ImplTxPipeComm(string name
		, IMessage* msg
		, size_t bufLen);
	~ImplTxPipeComm();

	void Action();
	void Send(IMessage* msg);
};

TxPipeComm::ImplTxPipeComm::ImplTxPipeComm(
	string name, IMessage* msg, size_t bufLen)
	: APipeComm(PIPE_ACCESS_OUTBOUND,name, msg, bufLen)
{
}

TxPipeComm::ImplTxPipeComm::~ImplTxPipeComm()
{
}

void TxPipeComm::ImplTxPipeComm::Action()
{
	EnterCriticalSection(&mLockMech);
	string msg = pMsg->ToString();
	DWORD bytesWritten = 0;

	BOOL success = WriteFile(pPipe
		, msg.c_str()
		, strlen(msg.c_str())
		, &bytesWritten
		, NULL);

	FlushFileBuffers(pPipe);
	LeaveCriticalSection(&mLockMech);
	
	if (success == FALSE)
	{
		cout << Name() << " client may have stopped. Stopping..." << endl;
		Stop();
	}
}

void TxPipeComm::ImplTxPipeComm::Send(IMessage* msg)
{
	EnterCriticalSection(&mLockMech);
	pMsg = msg;
	LeaveCriticalSection(&mLockMech);
}

//**************************************************************
// TxPipeComm
//**************************************************************

TxPipeComm::TxPipeComm(std::string name
	, IMessage* msg
	, size_t bufLen)
{
	pImpl = shared_ptr<ImplTxPipeComm>(
		new ImplTxPipeComm(name, msg, bufLen));
}


TxPipeComm::~TxPipeComm()
{
	pImpl->Stop();
	pImpl.reset();
}

void TxPipeComm::Send(IMessage* msg)
{
	pImpl->Send(msg);
}

void TxPipeComm::Start()
{
	pImpl->Start();
}

void TxPipeComm::Stop()
{
	pImpl->Stop();
}

void TxPipeComm::Reset()
{
	pImpl->Reset();
}

BOOL TxPipeComm::IsRunning()
{
	return pImpl->IsRunning();
}