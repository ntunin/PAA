#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class EXHandler: public StringHandler
{
public:
	EXHandler();
	~EXHandler();
	void readContent(std::string str, FileStructure *structure);
};

