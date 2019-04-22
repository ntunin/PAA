#pragma once
#include "PAAProblemStatement.h"
class GamsWritter
{
public:
	void write(std::string fileName, PAA::ProblemStatement *statement);
	GamsWritter();
	~GamsWritter();
};

