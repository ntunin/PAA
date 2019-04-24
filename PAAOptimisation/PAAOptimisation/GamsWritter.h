#pragma once
#include "PAAProblemStatement.h"
#include <string>

class GamsWritter
{
public:
	void write(std::string fileName, PAA::ProblemStatement *statement);
	GamsWritter();
	~GamsWritter();
};

