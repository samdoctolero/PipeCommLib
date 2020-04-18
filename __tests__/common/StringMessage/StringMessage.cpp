#include "StringMessage.h"

StringMessage::StringMessage(std::string value) {
	this->value = value;
}

std::string StringMessage::ToString() {
	return this->value;
}

void StringMessage::ToStruct(std::string str) {}