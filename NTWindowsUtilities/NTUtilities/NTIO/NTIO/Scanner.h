#pragma once
#include <string>

#ifdef NTIO_EXPORTS  
#define NTIO_API __declspec(dllexport)   
#else  
#define NTIO_API __declspec(dllimport)   
#endif 

class Scanner
{
private:
	static Scanner *shared;
public:
	static NTIO_API Scanner *getSharedScanner();
	static NTIO_API void setSharedScanner(Scanner *scanner);
	NTIO_API virtual int readInt(std::string message) = 0;
	NTIO_API virtual int readInt() = 0;
	NTIO_API virtual std::string readString() = 0;
	NTIO_API virtual std::string readString(std::string message) = 0;
	NTIO_API virtual double readDouble() = 0;
	NTIO_API virtual double readDouble(std::string message) = 0;
	NTIO_API virtual bool readBool() = 0;
	NTIO_API virtual bool readBool(std::string message) = 0;
	NTIO_API Scanner();
	NTIO_API ~Scanner();
};

