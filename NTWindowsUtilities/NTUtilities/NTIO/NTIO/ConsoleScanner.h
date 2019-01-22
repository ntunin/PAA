#pragma once
#include "Scanner.h"

#ifdef NTIO_EXPORTS  
#define NTIO_API __declspec(dllexport)   
#else  
#define NTIO_API __declspec(dllimport)   
#endif 

class ConsoleScanner :
	public Scanner
{
public:
	NTIO_API int readInt(std::string message);
	NTIO_API int readInt();
	NTIO_API std::string readString();
	NTIO_API std::string readString(std::string message);
	NTIO_API double readDouble();
	NTIO_API double readDouble(std::string message);
	NTIO_API bool readBool();
	NTIO_API bool readBool(std::string message);
	NTIO_API ConsoleScanner();
	NTIO_API ~ConsoleScanner();
};

