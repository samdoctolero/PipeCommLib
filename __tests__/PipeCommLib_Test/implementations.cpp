#include "pch.h"
#include "implementations.h"

MyPipeComm::MyPipeComm(std::string uniqueName,
	IMessage* msg) :
	APipeComm(0, uniqueName, msg, 0) {
}

void MyPipeComm::Action() {
	EnterCriticalSection(&mLockMech);
	mActionInvoked = true;
	LeaveCriticalSection(&mLockMech);
}

bool MyPipeComm::WasActionInvoked() {
	return this->mActionInvoked;
}

std::string DummyMessage::ToString() {
	return "";
}