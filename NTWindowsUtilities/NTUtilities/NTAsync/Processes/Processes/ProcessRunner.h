#pragma once

#ifdef PROCESSES_EXPORTS  
#define PROCESSES_API __declspec(dllexport)   
#else  
#define PROCESSES_API __declspec(dllimport)   
#endif 

class ProcessRunner
{
protected:
	virtual void startInNewThread() = 0;
public:
	PROCESSES_API virtual void run() = 0;
	PROCESSES_API virtual void wait() = 0;
	PROCESSES_API virtual virtual void dispatch() = 0;
	PROCESSES_API ProcessRunner();
	PROCESSES_API ~ProcessRunner();
};

