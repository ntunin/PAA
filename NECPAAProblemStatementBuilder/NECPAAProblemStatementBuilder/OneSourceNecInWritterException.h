#pragma once
#include <exception>
#include <string>

#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 

class OneSourceNecInWritterException: public std::exception {
private:
	std::string message;
public:
	NECPAAPROBLEMSTATEMENTBUILDER_API OneSourceNecInWritterException();
	NECPAAPROBLEMSTATEMENTBUILDER_API OneSourceNecInWritterException(const char *message);
	NECPAAPROBLEMSTATEMENTBUILDER_API OneSourceNecInWritterException(std::string message);
	NECPAAPROBLEMSTATEMENTBUILDER_API std::string getMessage();
	NECPAAPROBLEMSTATEMENTBUILDER_API ~OneSourceNecInWritterException();
};

