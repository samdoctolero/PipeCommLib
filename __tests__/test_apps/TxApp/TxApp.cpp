#include "PipeComm.h"
#include "StringMessage.h"

// The argument would be the
// string message to be sent
int main(int argc, char** argv)
{
	TxPipeComm* TxAppPipe =
		new TxPipeComm("RxAppPipe", new StringMessage());
	TxAppPipe->Start();

	Sleep(2000); // Wait for the receiver to initialize

	TxAppPipe->Send(new StringMessage(argv[1]));

	Sleep(20000); // Stay up for the receiver to listen

	return 0;
}