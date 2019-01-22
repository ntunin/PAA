#pragma once
#include <string>

#ifdef NTIO_EXPORTS  
#define NTIO_API __declspec(dllexport)   
#else  
#define NTIO_API __declspec(dllimport)   
#endif 

class Log
{
private:
	static Log *shared;
public:
	static NTIO_API Log *getSharedLog();
	static NTIO_API void setSharedLog(Log *log);
	NTIO_API Log();
	NTIO_API virtual void print(double **m, int size) = 0;
	NTIO_API virtual void print(double *v, int size) = 0;
	NTIO_API virtual void print(std::string &m) = 0;
	NTIO_API virtual void print(const char *m) = 0;
	NTIO_API virtual void print(double d) = 0;
	NTIO_API virtual void print(double d, int size) = 0;
	NTIO_API virtual void reset() = 0;

	NTIO_API ~Log();
};

