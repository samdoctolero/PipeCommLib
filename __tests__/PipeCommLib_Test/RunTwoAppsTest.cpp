#include "pch.h"
#include <thread>
#include <future>

class RunTwoAppsTest : public ::testing::Test {
protected:
	int txResult, rxResult;

	void SetUp() {
		const char msg[] = "ajwoepihabhIEOHAFhwoghweg";

		// Create objects to store
		// results from async threads
		std::promise<int> pT, pR;
		std::future<int> txResultF =
			pT.get_future();
		std::future<int> rxResultF =
			pR.get_future();

		// Execute RxApp and TxApp
		// on parallel threads
		std::thread thr_Tx(
			[msg](std::promise<int>&& p) {
			char command[50];
			sprintf(command, "TxApp %s", msg);
			p.set_value(system(command));
		},
			std::move(pT)
		);
		std::thread thr_Rx(
			[msg](std::promise<int>&& p) {
			char command[50];
			sprintf(command, "RxApp %s", msg);
			p.set_value(system(command));
		},
			std::move(pR)
		);
		// Join the threads before
		// getting the results
		thr_Rx.join();
		thr_Tx.join();

		txResult = txResultF.get();
		rxResult = rxResultF.get();
	}
};

TEST_F(RunTwoAppsTest, TxResults) {
	EXPECT_EQ(txResult, 0);
}

TEST_F(RunTwoAppsTest, RxResults) {
	EXPECT_EQ(rxResult, 0);
}