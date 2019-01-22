#pragma once
#include <iostream>

class FileException : public std::exception
{
private:
	std::string message;
public:
	FileException();
	FileException(char *message);
	FileException(std::string message);
	~FileException();

	std::string getMessage();
};

