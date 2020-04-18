#include "pch.h"
#include "implementations.h"

class APipeCommTest : public ::testing::Test {
protected:
	MyPipeComm* pipe;
	void SetUp() {
		// Create pipe instance
		pipe = new MyPipeComm("myPipe", new DummyMessage());
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