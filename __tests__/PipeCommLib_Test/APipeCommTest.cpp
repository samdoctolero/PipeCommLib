#include "pch.h"
#include "APipeComm.h"
#include "PipeComm.h"

// Create a generic
// implementation of APipeComm
class MyPipeComm : public APipeComm {
private:
	bool mActionInvoked = false; // Indicates true if Action is invoked
public:
	MyPipeComm(std::string uniqueName,
		IMessage* msg) :
		APipeComm(0, uniqueName, msg, 0) {
	}
	void Action() {
		EnterCriticalSection(&mLockMech);
		mActionInvoked = true;
		LeaveCriticalSection(&mLockMech);
	}
	bool WasActionInvoked() {
		return this->mActionInvoked;
	}
};

class DummyMessage : public IMessage {
public:
	std::string ToString() {
		return "";
	}
	void ToStruct(std::string str) {
		// Do nothing
	}
};

class APipeCommTest : public ::testing::Test {
protected:
	IMessage* msg;
	MyPipeComm* pipe;
	void SetUp() {
		this->msg = new DummyMessage();
		// Create pipe instance
		pipe = new MyPipeComm("myPipe", msg);
		pipe->Start();
	}
};

TEST_F(APipeCommTest, PipeIsRunning) {
	EXPECT_TRUE(pipe->IsRunning());
}

TEST_F(APipeCommTest, WasActionPerformed) {
	Sleep(5000); // Make sure the loop was called
	EXPECT_TRUE(pipe->WasActionInvoked());
}