#pragma once
#include "PAAProblemStatement.h"
#include <string>
#include "NecIn.h"
#include "NecOut.h"
#include "WindowsCacheManager.h"
#include "NTMath.h"
#include "PAAPhysicalSystem.h"

#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 


namespace PAA {
	class NECPhysicalSystemBuilder
	{
	private:
		WindowsCacheManager *cacheManager;
		std::string filename;
		NecOut **buildOuts(bool);
		Math::Complex ****buildBeamPattern(int sourceCount, NecIn *in, NecOut **outs);
		Math::Matrix<Math::Complex> *buildY(int sourceCont, NecOut **outs);
	public:
		NecIn *in;
		NECPAAPROBLEMSTATEMENTBUILDER_API PhysicalSystem *buildSystem(bool);
		NECPAAPROBLEMSTATEMENTBUILDER_API NECPhysicalSystemBuilder(std::string filename);
		NECPAAPROBLEMSTATEMENTBUILDER_API ~NECPhysicalSystemBuilder();
	};
}

