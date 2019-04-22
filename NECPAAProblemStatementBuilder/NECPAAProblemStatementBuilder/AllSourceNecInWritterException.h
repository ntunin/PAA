#pragma once
#include <string>


#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 


class AllSourceNecInWritterException
{
private:
	std::string message;
public:
	NECPAAPROBLEMSTATEMENTBUILDER_API AllSourceNecInWritterException();
	NECPAAPROBLEMSTATEMENTBUILDER_API AllSourceNecInWritterException(const char *message);
	NECPAAPROBLEMSTATEMENTBUILDER_API AllSourceNecInWritterException(std::string message);
	NECPAAPROBLEMSTATEMENTBUILDER_API std::string getMessage();
	NECPAAPROBLEMSTATEMENTBUILDER_API ~AllSourceNecInWritterException();
};

