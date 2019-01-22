#pragma once
#include "NecCommand.h"

class GN: public NecCommand {
public:
	GN(int groundType, int radialWiresNumber, double dielectricConstant, double conductivity);
	GN(GN &gn);
	~GN();
	std::string toString();
	int getType();

private:
	int groundType;
	int radialWiresNumber;
	double dielectricConstant;
	double conductivity;
};

