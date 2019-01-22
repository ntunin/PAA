#pragma once
#include "NTMath.h"

#ifdef PAAPROBLEMSTATEMENTPROJECT_EXPORTS  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllexport)   
#else  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class PhysicalSystem
	{

	private:
		int sourceCount;
		int iStep;
		int jStep;
		Math::Matrix<Math::Complex> *Y;
		Math::Complex ****beamPattern;
	public:
		PAAPROBLEMSTATEMENTPROJECT_API PhysicalSystem(int sourceCount, int iStep, int jStep, Math::Matrix<Math::Complex> *Y, Math::Complex ****beamPattern);
		PAAPROBLEMSTATEMENTPROJECT_API int getSourceCount();
		PAAPROBLEMSTATEMENTPROJECT_API Math::Matrix<Math::Complex> *getY();
		PAAPROBLEMSTATEMENTPROJECT_API Math::Complex ****getBeamPattern();
		PAAPROBLEMSTATEMENTPROJECT_API int getIStep();
		PAAPROBLEMSTATEMENTPROJECT_API int getJStep();
		PAAPROBLEMSTATEMENTPROJECT_API ~PhysicalSystem();
	};
}
