#pragma once
#include "NTMath.h"
#include <vector>

#ifdef PAAPROBLEMSTATEMENTPROJECT_EXPORTS  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllexport)   
#else  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class ProblemStatement
	{
	public:
		ProblemStatement();
		PAAPROBLEMSTATEMENTPROJECT_API ~ProblemStatement();
		PAAPROBLEMSTATEMENTPROJECT_API virtual Math::Matrix<double> *getA() = 0;
		PAAPROBLEMSTATEMENTPROJECT_API virtual std::vector<Math::Matrix<double> *> *getB() = 0;
	};
}

