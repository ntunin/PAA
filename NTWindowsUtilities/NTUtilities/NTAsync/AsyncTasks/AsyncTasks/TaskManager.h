#pragma once
#include "Task.h"

#ifdef ASYNCTASKS_EXPORTS  
#define ASYNCTASKS_API __declspec(dllexport)   
#else  
#define ASYNCTASKS_API __declspec(dllimport)   
#endif 

class TaskManager
{
private:
	static TaskManager *manager;
public:
	ASYNCTASKS_API static TaskManager *getSharedManager();
	ASYNCTASKS_API static void setSharedManager(TaskManager *);
	ASYNCTASKS_API virtual void execute(Task *task) = 0;
	ASYNCTASKS_API virtual void wait(Task *task) = 0;
	ASYNCTASKS_API TaskManager();
	ASYNCTASKS_API ~TaskManager();
};

