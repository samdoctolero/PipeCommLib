# PipeCommLib
A simple (perhaps for now)  windows C++ library that uses pipes to create communication lines. It contains three main classes:
+ TxPipeComm - creates/opens a pipe to establish a transmit communication line (i.e. server)
+ RxPipeComm - creates/opens a pipe to establish a receive communicationline (i.e. client)
+ IMessage - message container that must be inherited for any messages that need to be transferred via RxPipeComm and TxPipeComm

NOTE: This is a mock-up code. NOT FULLY TESTED. Feel free to use it as you please but you've been warned. 
