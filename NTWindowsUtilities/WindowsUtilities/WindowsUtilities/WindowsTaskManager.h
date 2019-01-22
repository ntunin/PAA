#pragma once
#include "TaskManager.h"
#include <vector>
#include <thread>

#ifdef WINDOWSUTILITIES_EXPORTS  
#define WINDOWSUTILITIES_API __declspec(dllexport)   
#else  
#define WINDOWSUTILITIES_API __declspec(dllimport)   
#endif 


class WindowsTaskManager :
	public TaskManager
{
private:
	std::vector<std::thread *> threads;
	int indexOf(Task *task);
public:
	WINDOWSUTILITIES_API void execute(Task *task);
	WINDOWSUTILITIES_API void wait(Task *task);
	WINDOWSUTILITIES_API WindowsTaskManager();
	WINDOWSUTILITIES_API ~WindowsTaskManager();
};

