#include "stdafx.h"
#include "OneSourceNecInWritterException.h"

OneSourceNecInWritterException::~OneSourceNecInWritterException()
{
}

OneSourceNecInWritterException::OneSourceNecInWritterException() {
	message = "An file exception thrown";
}

OneSourceNecInWritterException::OneSourceNecInWritterException(const char *message) {
	this->message = std::string(message);
}

OneSourceNecInWritterException::OneSourceNecInWritterException(std::string message) {
	this->message = message;
}

std::string OneSourceNecInWritterException::getMessage() {
	return this->message;
}
