#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class FRHandler: public StringHandler
{
public:
	FRHandler();
	~FRHandler();
	void readContent(std::string str, FileStructure *structure);
};

