#pragma once
#include <string>

#ifdef ASYNCTASKS_EXPORTS  
#define ASYNCTASKS_API __declspec(dllexport)   
#else  
#define ASYNCTASKS_API __declspec(dllimport)   
#endif 

class Task
{
private:
	std::string id;
public:
	ASYNCTASKS_API virtual void execute() = 0;
	ASYNCTASKS_API void assign(std::string id);
	ASYNCTASKS_API std::string getId();
	ASYNCTASKS_API Task();
	ASYNCTASKS_API ~Task();
};

