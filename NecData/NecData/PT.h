#pragma once
#include "NecCommand.h"

class PT: public NecCommand {
public:
	PT(int flag);
	PT(PT &pt);
	~PT();
	std::string toString();
private:
	int flag;
};

