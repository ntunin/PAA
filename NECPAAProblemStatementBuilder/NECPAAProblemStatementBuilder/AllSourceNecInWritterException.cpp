#include "stdafx.h"
#include "AllSourceNecInWritterException.h"

AllSourceNecInWritterException::~AllSourceNecInWritterException() {
}

AllSourceNecInWritterException::AllSourceNecInWritterException() {
	message = "An file exception thrown";
}

AllSourceNecInWritterException::AllSourceNecInWritterException(const char *message) {
	this->message = std::string(message);
}

AllSourceNecInWritterException::AllSourceNecInWritterException(std::string message) {
	this->message = message;
}

std::string AllSourceNecInWritterException::getMessage() {
	return this->message;
}
