#pragma once
#include "ProcessManager.h"
#include <mutex>

#ifdef WINDOWSUTILITIES_EXPORTS  
#define WINDOWSUTILITIES_API __declspec(dllexport)   
#else  
#define WINDOWSUTILITIES_API __declspec(dllimport)   
#endif 


std::mutex processManagerMtx;

class WindowsProcessManager :
	public ProcessManager
{
private:
	std::unique_lock<std::mutex> lck;
protected:
	WINDOWSUTILITIES_API void ping();
	WINDOWSUTILITIES_API void lock();
	WINDOWSUTILITIES_API void unlock();
public:
	WINDOWSUTILITIES_API int getCoresCount();
	WINDOWSUTILITIES_API WindowsProcessManager();
	WINDOWSUTILITIES_API ~WindowsProcessManager();
};

