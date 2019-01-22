#pragma once
#include "FARProblemStatement.h"
#include <string>
#include "NecIn.h"
#include "NecOut.h"
#include "CacheManager.h"

namespace PAA {
	class NECStatementBuilder
	{
	private:
		NecIn *in;
		CacheManager *cacheManager;
		std::string filename;
	public:
		ProblemStatement *buildStatement(double theta, double phi);
		NecOut *buildOuts();
		NECStatementBuilder(std::string filename);
		~NECStatementBuilder();
	};
}

