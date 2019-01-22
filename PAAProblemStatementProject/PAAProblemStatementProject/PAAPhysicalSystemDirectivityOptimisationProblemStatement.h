#pragma once
#include "PAAPhysicalSystemProblemStatement.h"


#ifdef PAAPROBLEMSTATEMENTPROJECT_EXPORTS  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllexport)   
#else  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class PhysicalSystemDirectivityOptimisationProblemStatement: public PhysicalSystemProblemStatement
	{
	public:
		PAAPROBLEMSTATEMENTPROJECT_API PhysicalSystemDirectivityOptimisationProblemStatement(PhysicalSystem *physicalSystem, std::vector<double> constraints, double theta, double phi);
		PAAPROBLEMSTATEMENTPROJECT_API ~PhysicalSystemDirectivityOptimisationProblemStatement();
		PAAPROBLEMSTATEMENTPROJECT_API std::vector<Math::Matrix<double> *> *getB();
	};
}

