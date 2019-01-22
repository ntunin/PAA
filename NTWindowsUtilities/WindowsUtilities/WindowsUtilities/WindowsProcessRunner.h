#pragma once
#include "ProcessRunner.h"
#include <string>
#include <thread>
#include <Windows.h>

#ifdef WINDOWSUTILITIES_EXPORTS  
#define WINDOWSUTILITIES_API __declspec(dllexport)   
#else  
#define WINDOWSUTILITIES_API __declspec(dllimport)   
#endif 


class WindowsProcessRunner: public ProcessRunner
{
protected:
	WINDOWSUTILITIES_API void exe(std::string command, std::string arguments);
	WINDOWSUTILITIES_API void exe(std::string command);
	WINDOWSUTILITIES_API void startInNewThread();
	std::thread thread;
public:
	WINDOWSUTILITIES_API void run();
	WINDOWSUTILITIES_API void wait();
	WINDOWSUTILITIES_API WindowsProcessRunner();
	WINDOWSUTILITIES_API ~WindowsProcessRunner();
private:
	HANDLE g_hChildStd_IN_Rd = NULL;
	HANDLE g_hChildStd_IN_Wr = NULL;
	HANDLE g_hChildStd_OUT_Rd = NULL;
	HANDLE g_hChildStd_OUT_Wr = NULL;

	HANDLE g_hInputFile = NULL;

	void CreateChildProcess(LPWSTR cmd, std::string &input);
	void WriteToPipe(std::string &str);
	void ReadFromPipe(void);
	void ErrorExit(PTSTR);
};

