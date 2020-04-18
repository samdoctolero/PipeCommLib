#include "PipeComm.h"
#include "StringMessage.h"

// The argument would be the message expected
int main(int argc, char** argv)
{
	if (argc != 1) {
		// Invalid number of args
		return -1;
	}

	RxPipeComm* RxAppPipe =
		new RxPipeComm("RxAppPipe", new StringMessage());
	RxAppPipe->Start();

	Sleep(2000);
	IMessage* msg = RxAppPipe->Get();

	// Return non-zero if msg doesn't match the argument
	if (msg->ToString() != argv[0]) {
		return -1;
	}

	return 0;
}