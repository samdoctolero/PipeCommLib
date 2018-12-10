#include "stdafx.h"
#include "CPipeComm.h"
#include "PipeComm.h"

TxPipeComm* CreateCTxPipeComm(std::string name, void* msg)
{
	return new TxPipeComm(name, (IMessage*)msg);
}

void DestroyCTxPipeComm(TxPipeComm* ptr)
{
	delete ptr;
}

void Send(TxPipeComm* ptr, void* msg) 
{
	ptr->Send((IMessage*)msg);
}

void StartTx(TxPipeComm* ptr)
{
	ptr->Start();
}

void StopTx(TxPipeComm* ptr)
{
	ptr->Stop();
}

void ResetTx(TxPipeComm* ptr)
{
	ptr->Reset();
}

int IsRunningTx(TxPipeComm* ptr)
{
	return ptr->IsRunning();
}

RxPipeComm* CreateCRxPipeComm(std::string name, void* msg)
{
	return new RxPipeComm(name, (IMessage*)msg);
}

void DestroyCRxPipeComm(RxPipeComm* ptr)
{
	delete ptr;
}

void* Get(RxPipeComm* ptr)
{
	return (void*)ptr->Get();
}

void StartRx(RxPipeComm* ptr)
{
	ptr->Start();
}

void StopRx(RxPipeComm* ptr)
{
	ptr->Stop();
}

void ResetRx(RxPipeComm* ptr)
{
	ptr->Reset();
}

int IsRunningRx(RxPipeComm* ptr)
{
	return ptr->IsRunning();
}