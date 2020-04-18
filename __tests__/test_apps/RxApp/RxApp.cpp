#include "PipeComm.h"
#include "StringMessage.h"
#include <chrono>

// The argument would be the message expected
int main(int argc, char** argv)
{
	RxPipeComm* RxAppPipe =
		new RxPipeComm("RxAppPipe", new StringMessage());
	RxAppPipe->Start();

	// Continiuously get the message for 5 seconds or when
	// the toString value matches the passed argument
	auto start = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds;
	do
	{
		if (RxAppPipe->Get()->ToString() == argv[1]) {
			RxAppPipe->Stop();
			return 0;
		}

		elapsed_seconds =
			std::chrono::steady_clock::now() - start;
	}
	while (elapsed_seconds.count() >= 15);

	return -1;
}