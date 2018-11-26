#pragma once
#include <string>
#include <memory>
#include <string>
#include <Windows.h>

//*********************************************************
// IMessage
// Description:	A interface for container messages. 
//				Messages that need to be transferred
//				must inherit this class and create the
//				abstract methods. 
//*********************************************************
class IMessage
{
public:
	// Converts the structured message into a 
	// readable string. 
	virtual std::string ToString() = 0;

	// Converts the string into its structured 
	// format.
	virtual void ToStruct(std::string str) = 0;
};

//*********************************************************
// RxPipeComm
// Description: Creates/opens a pipe to receive messages
//				from a server (TxPipeComm).
//*********************************************************
class RxPipeComm
{
private:
	// hidden implementation
	class ImplRxPipeComm;
	// implementation object
	std::shared_ptr<ImplRxPipeComm> pImpl;
public:
	RxPipeComm(std::string name,
		std::shared_ptr<IMessage> msg,
		size_t bufLen = 255);
	~RxPipeComm();

	// retreive the latest message
	std::shared_ptr<IMessage> Get();

	// starts the pipe connection
	void Start();
	// stops the pipe connection
	void Stop();
	// stops then starts the pipe connection
	void Reset();
};

//*********************************************************
// RxPipeComm
// Description: Creates/opens a pipe to transmit messages
//				to a client (RxPipeComm).
//*********************************************************
class TxPipeComm
{
private:
	// hidden implementation
	class ImplTxPipeComm;
	// implementation object
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