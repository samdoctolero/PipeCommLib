#include "PipeComm.h"
#include "StringMessage.h"

// The argument would be the
// string message to be sent
int main(int argc, char** argv)
{
	if (argc != 1) {
		// Invalid number of args
		return -1;
	}

	TxPipeComm* TxAppPipe =
		new TxPipeComm("RxAppPipe", new StringMessage());
	TxAppPipe->Start();

	Sleep(1000);
	// Send the message specified in argv
	TxAppPipe->Send(new StringMessage(argv[0]));

	Sleep(3000);

	return 0;
}