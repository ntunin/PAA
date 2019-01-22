#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class CMHandler: public StringHandler
{
public:
	CMHandler();
	~CMHandler();
	void readContent(std::string str, FileStructure *structure);
};

