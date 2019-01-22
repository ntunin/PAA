#pragma once
#include "RandomGenerator.h"
#include <mutex>
#include "Task.h"

#ifdef WINDOWSUTILITIES_EXPORTS  
#define WINDOWSUTILITIES_API __declspec(dllexport)   
#else  
#define WINDOWSUTILITIES_API __declspec(dllimport)   
#endif 


class WindowsRandomGenerator :
	public RandomGenerator
{
private:
	class GeneratorTask : public Task {
	private:
		std::mutex randMtx;
		int value;
		int squireIndex;
		bool running;
	public:
		WINDOWSUTILITIES_API int next();
		WINDOWSUTILITIES_API void stop();
		WINDOWSUTILITIES_API void execute();
	};
	GeneratorTask *task;
public:
	WINDOWSUTILITIES_API int next();
	WINDOWSUTILITIES_API void stop();
	WINDOWSUTILITIES_API WindowsRandomGenerator();
	WINDOWSUTILITIES_API ~WindowsRandomGenerator();

};

