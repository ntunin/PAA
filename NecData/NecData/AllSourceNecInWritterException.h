#pragma once
#include <string>
class AllSourceNecInWritterException
{
private:
	std::string message;
public:
	AllSourceNecInWritterException();
	AllSourceNecInWritterException(const char *message);
	AllSourceNecInWritterException(std::string message);
	std::string getMessage();
	~AllSourceNecInWritterException();
};

