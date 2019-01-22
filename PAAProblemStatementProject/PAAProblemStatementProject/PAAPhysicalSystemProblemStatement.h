#pragma once
#include "PAAProblemStatement.h"
#include "PAAPhysicalSystem.h"

#ifdef PAAPROBLEMSTATEMENTPROJECT_EXPORTS  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllexport)   
#else  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class PhysicalSystemProblemStatement: public ProblemStatement
	{

	protected:
		Math::Matrix<Math::Complex> *buildProjector(int k, int N);
		PhysicalSystem *physicalSystem;
		std::vector<double> constraints;
		int iDirect = 0;
		int jDirect = 0;
	public:
		PAAPROBLEMSTATEMENTPROJECT_API void setDirection(double theta, double phi);
		PAAPROBLEMSTATEMENTPROJECT_API void setConstraints(std::vector<double> constraints);
		PAAPROBLEMSTATEMENTPROJECT_API PhysicalSystemProblemStatement(PhysicalSystem *physicalSystem, std::vector<double> constraints, double theta, double phi);
		PAAPROBLEMSTATEMENTPROJECT_API ~PhysicalSystemProblemStatement();
		PAAPROBLEMSTATEMENTPROJECT_API Math::Matrix<double> *getA();
		PAAPROBLEMSTATEMENTPROJECT_API virtual std::vector<Math::Matrix<double> *> *getB() = 0;
	};
}

