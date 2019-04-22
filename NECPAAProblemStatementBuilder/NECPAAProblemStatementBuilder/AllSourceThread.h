#pragma once
#include "ProcessRunner.h"
#include "NecIn.h"
#include "NecOut.h"
#include "NTMath.h"

#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 

class AllSourceThread: public ProcessRunner
{
public:
	NECPAAPROBLEMSTATEMENTBUILDER_API AllSourceThread(NecIn *in, Math::Vector<Math::Complex> *sources, const char *fileName, NecOut *out);
	NECPAAPROBLEMSTATEMENTBUILDER_API ~AllSourceThread();
	NECPAAPROBLEMSTATEMENTBUILDER_API void dispatch();
	NECPAAPROBLEMSTATEMENTBUILDER_API NecOut *getOut();
private:
	NecIn *in;
	Math::Vector<Math::Complex> *sources;
	std::string fileName;
	NecOut *out;
	int sourceNumber;
};

