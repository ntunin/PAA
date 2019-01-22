#pragma once
#include "StringHandler.h"

class GEHandler :
	public StringHandler
{
public:
	GEHandler();
	~GEHandler();
	void readContent(std::string str, FileStructure *structure);
};

