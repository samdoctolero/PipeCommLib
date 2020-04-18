#include "pch.h"
#include "implementations.h"

class PipeCommTest : public ::testing::Test {
protected:
	RxPipeComm* rxPipe;
	TxPipeComm* txPipe;
	void SetUp() {
		rxPipe = new RxPipeComm("rxPipe", new DummyMessage());
		rxPipe->Start();
		txPipe = new TxPipeComm("txPipe", new DummyMessage());
		txPipe->Start();
	}
};

TEST_F(PipeCommTest, CheckPipesRunning) {
	Sleep(5000); // Ensure the loop running
	EXPECT_TRUE(rxPipe->IsRunning());
	EXPECT_TRUE(txPipe->IsRunning());
}