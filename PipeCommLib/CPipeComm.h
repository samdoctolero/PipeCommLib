#pragma once

#ifdef __cpusplus
extern "C"
{
#endif
	//*********************************************************
	// TxPipeComm
	//*********************************************************
	// TxPipeComm struct
	struct TxPipeComm;
	typedef struct TxPipeComm TxPipeComm;

	// TxPipeComm constructor/destructor
	TxPipeComm * CreateCTxPipeComm(char * name, void * msg);
	void DestroyCTxPipeComm(TxPipeComm* ptr);

	// TxPipeComm methods
	void Send(TxPipeComm * ptr, void * msg);
	void StartTx(TxPipeComm * ptr);
	void StopTx(TxPipeComm * ptr);
	void ResetTx(TxPipeComm * ptr);
	int IsRunningTx(TxPipeComm * ptr);

	//*********************************************************
	// RxPipeComm
	//*********************************************************
	// RxPipeComm struct
	struct RxPipeComm;
	typedef struct RxPipeComm RxPipeComm;

	// RxPipeComm constructor/destructor
	RxPipeComm * CreateCRxPipeComm(char * name, void * msg);
	void DestroyCRxPipeComm(RxPipeComm * ptr);

	// RxPipeComm methods
	void * Get(RxPipeComm * ptr);
	void StartRx(RxPipeComm * ptr);
	void StopRx(RxPipeComm * ptr);
	void ResetRx(RxPipeComm * ptr);
	int IsRunningRx(RxPipeComm * ptr);

#ifdef __cpusplus
}
#endif