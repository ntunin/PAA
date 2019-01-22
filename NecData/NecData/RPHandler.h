#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class RPHandler: public StringHandler
{
public:
	RPHandler();
	~RPHandler();
	void readContent(std::string str, FileStructure *structure);
};

