#include "pch.h"
#include "implementations.h"

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
	Sleep(5000); // Make sure the loop was called
	EXPECT_TRUE(pipe->IsRunning());
}

TEST_F(APipeCommTest, WasActionPerformed) {
	Sleep(5000); // Make sure the loop was called
	EXPECT_TRUE(pipe->WasActionInvoked());
}