#pragma once
#include "APipeComm.h"
#include "PipeComm.h"

// Create a generic
// implementation of APipeComm
class MyPipeComm : public APipeComm {
private:
	bool mActionInvoked = false; // Indicates true if Action is invoked
public:
	MyPipeComm(std::string uniqueName,
		IMessage* msg);

	void Action();
	bool WasActionInvoked();
};

class DummyMessage : public IMessage {
public:
	std::string ToString();
	void ToStruct(std::string str) {}
};