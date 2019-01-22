#pragma once
#include "WindowsProcessRunner.h"
#include "NecIn.h",
#include <thread>
#include "WindowsCacheManager.h"

#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 

class NecRunner: public WindowsProcessRunner
{
public:
	NECPAAPROBLEMSTATEMENTBUILDER_API NecRunner();
	NECPAAPROBLEMSTATEMENTBUILDER_API NecRunner(NecIn *in);
	NECPAAPROBLEMSTATEMENTBUILDER_API ~NecRunner();
	NECPAAPROBLEMSTATEMENTBUILDER_API std::string createName(std::thread::id id, int number);
	NECPAAPROBLEMSTATEMENTBUILDER_API void removeFile(std::string &name);
	NECPAAPROBLEMSTATEMENTBUILDER_API void dispatch();
	//void runNEC(WindowsCacheManager *manager);
	NECPAAPROBLEMSTATEMENTBUILDER_API void runNEC(WindowsCacheManager *manager, int sourceNumber, NecOut **outs);
private:
	NecOut **outs;
	int sourceNumber;
	WindowsCacheManager *cacheManager;
	NecIn *in;
	void randomize();
};

