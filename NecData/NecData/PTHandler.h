#pragma once
#include "StringHandler.h"
#include <string>
#include "FileStructure.h"

class PTHandler: public StringHandler
{
public:
	PTHandler();
	~PTHandler();
	void readContent(std::string str, FileStructure *structure);
};

