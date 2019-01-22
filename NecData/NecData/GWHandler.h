#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class GWHandler: public StringHandler
{
public:
	GWHandler();
	~GWHandler();
	void readContent(std::string str, FileStructure *structure);
};

