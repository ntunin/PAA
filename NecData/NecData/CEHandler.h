#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class CEHandler: public StringHandler
{
public:
	CEHandler();
	~CEHandler();
	void readContent(std::string str, FileStructure *structure);
};

