#pragma once
#include "Log.h"
#include <string>

#ifdef NTIO_EXPORTS  
#define NTIO_API __declspec(dllexport)   
#else  
#define NTIO_API __declspec(dllimport)   
#endif 

class ConsoleLog :
	public Log
{
public:
	NTIO_API ConsoleLog();
	NTIO_API void print(double **m, int size);
	NTIO_API void print(double *v, int size);
	NTIO_API void print(std::string &m);
	NTIO_API void print(const char *m);
	NTIO_API void print(double d);
	NTIO_API void print(double d, int size);
	NTIO_API void reset();
	NTIO_API ~ConsoleLog();
};

