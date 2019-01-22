#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class ENHandler: public StringHandler
{
public:
	ENHandler();
	~ENHandler();
	void readContent(std::string str, FileStructure *structure);
};

