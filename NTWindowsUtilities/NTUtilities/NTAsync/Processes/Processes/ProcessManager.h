#pragma once
#include <queue>
#include "ProcessRunner.h"

#ifdef PROCESSES_EXPORTS  
#define PROCESSES_API __declspec(dllexport)   
#else  
#define PROCESSES_API __declspec(dllimport)   
#endif 

class ProcessManager {
private: 
	static ProcessManager *sharedManager;
protected:
	int countOfDispatched;
	std::queue<ProcessRunner *> queuedRunners;
	virtual void ping() = 0;
	virtual void lock() = 0;
	virtual void unlock() = 0;
public:
	PROCESSES_API static ProcessManager *getSharedManager();
	PROCESSES_API static void setSharedManager(ProcessManager *manager);
	PROCESSES_API virtual int getCoresCount() = 0;
	PROCESSES_API void run(ProcessRunner *runner);
	PROCESSES_API ProcessManager();
	PROCESSES_API ~ProcessManager();
};

