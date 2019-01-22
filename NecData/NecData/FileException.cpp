#include "stdafx.h"
#include "FileException.h"


FileException::FileException() {
	message = "An file exception thrown";
}

FileException::FileException(char *message) {
	this->message = std::string(message);
}

FileException::FileException(std::string message) {
	this->message = message;
}

FileException::~FileException() {
}

std::string FileException::getMessage() {
	return this->message;
}
