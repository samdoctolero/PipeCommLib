#pragma once
#include <memory>
#include <string>
#include <Windows.h>
#include "IMessage.h"

class TxPipeComm
{
private:
	class ImplTxPipeComm;
	std::shared_ptr<ImplTxPipeComm> pImpl;
public:
	TxPipeComm(std::string name, 
		std::shared_ptr<IMessage> msg, 
		size_t bufLen = 255);
	~TxPipeComm();

	// changes the stored buffer to the new message
	void Send(std::shared_ptr<IMessage> msg);
	
	// starts the pipe connection
	void Start();
	// stops the pipe connection
	void Stop();
	// stops then starts the pipe connection
	void Reset();
};

