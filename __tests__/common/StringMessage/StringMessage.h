#pragma once
#include "PipeComm.h"

class StringMessage : public IMessage {
	std::string value;
public:
	StringMessage(std::string value = "");

	std::string ToString();
	void ToStruct(std::string str);
};