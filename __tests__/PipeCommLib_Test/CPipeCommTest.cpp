#include "pch.h"
#include "CPipeComm.h"

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

class CPipeCommTest : public ::testing::Test {
protected:
	TxPipeComm* cTxPipe;
	RxPipeComm* cRxPipe;
	void SetUp() {
		// Just allocate a random pointer
		cTxPipe = CreateCTxPipeComm("cTxPipe",
			malloc(sizeof(double)));
		StartTx(cTxPipe);

		cRxPipe = CreateCRxPipeComm("cRxPipe",
			malloc(sizeof(double)));
		StartRx(cRxPipe);
	}
};

TEST_F(CPipeCommTest, CheckPipesRunning) {
	Sleep(5000); // Ensure the loop running
	EXPECT_TRUE(IsRunningTx(cTxPipe));
	EXPECT_TRUE(IsRunningRx(cRxPipe));
}