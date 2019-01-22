#pragma once
#include "NecCommand.h"

class FR: public NecCommand{
private:
	int steppingType;
	int stepsNumber;
	double frequency;
public:
	FR(int steppingType, int stepsNumber, double frequency);
	FR(FR &fr);
	~FR();
	std::string toString();
};

