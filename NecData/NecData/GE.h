#pragma once
#include "NecCommand.h"
#include <string>
class GE :
	public NecCommand
{
private:
	int flag;
public:
	GE(int falg);
	GE(GE &ge);
	~GE();
	std::string toString();
};

