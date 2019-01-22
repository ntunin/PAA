#pragma once
#include "Log.h"
#include <mutex> 

#ifdef NTIO_EXPORTS  
#define NTIO_API __declspec(dllexport)   
#else  
#define NTIO_API __declspec(dllimport)   
#endif 

class FileLog :
	public Log
{
private:
	std::ofstream *file;
	std::mutex consoleMtx;
public:
	NTIO_API void print(double **m, int size);
	NTIO_API void print(double *v, int size);
	NTIO_API void print(std::string &m);
	NTIO_API void print(const char *m);
	NTIO_API void print(double d);
	NTIO_API void print(double d, int size);
	NTIO_API void reset();
	NTIO_API FileLog(std::string path);
	NTIO_API ~FileLog();
};

