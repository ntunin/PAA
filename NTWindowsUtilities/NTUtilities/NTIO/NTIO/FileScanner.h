#pragma once
#include "Scanner.h"
#include <string>
#include <fstream>

#ifdef NTIO_EXPORTS  
#define NTIO_API __declspec(dllexport)   
#else  
#define NTIO_API __declspec(dllimport)   
#endif 


class FileScanner :
	public Scanner
{
private:
	std::ifstream *file;
public:
	NTIO_API int readInt(std::string message);
	NTIO_API int readInt();
	NTIO_API std::string readString();
	NTIO_API std::string readString(std::string message);
	NTIO_API double readDouble();
	NTIO_API double readDouble(std::string message);
	NTIO_API bool readBool();
	NTIO_API bool readBool(std::string message);
	NTIO_API FileScanner(std::string path);
	NTIO_API ~FileScanner();
};

