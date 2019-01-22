#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class GNHandler:  public StringHandler
{
public:
	GNHandler();
	~GNHandler();
	void readContent(std::string str, FileStructure *structure);
};

