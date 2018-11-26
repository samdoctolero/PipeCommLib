# PipeCommLib
A simple (perhaps for now)  windows C++ library that uses pipes to create communication lines. It contains three main classes:
+ TxPipeComm - creates/opens a pipe to establish a transmit communication line (i.e. server)
+ RxPipeComm - creates/opens a pipe to establish a receive communicationline (i.e. client)
+ IMessage - message container that must be inherited for any messages that need to be transferred via RxPipeComm and TxPipeComm

TxPipeComm and RxPipeComm each have two threads going on, the main thread where the user can command Start/Stop/Reset and a child thread that reads to or writes from a pipe. All of these are hidden from the user. 

NOTE: This is a mock-up code. NOT FULLY TESTED. Feel free to use it as you please but you've been warned. 

The way I use it:
- Create a library that is used by similar applications (what I mean by similar is that these applications  
  use a common library). This library creates message containers that inherit IMessage. 
- Create an application/server that spits out data. Let's call this app_1.
- Create a secondary application that reads data from another application. Let's call this secondary application app_2.
- app_1 contains an instance of TxPipeComm to transmit data as soon as the receiving pipe is created.
- app_2 contains an instance of RxPipeComm to receive data as soon as it connects to a pipe. 

NOTE: Server (TxPipeComm) must launch first before the client. This is a current limitation to simplify implementation.
