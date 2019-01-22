#pragma once
#include "KeywordsHandler.h"
#include <string>
#include "FileStructure.h"

class StringHandler : public KeywordsHandler {
public:
	StringHandler();
	~StringHandler();
	virtual void readContent(std::string str, FileStructure *structure) = 0;
	bool checkString(std::string str);
};

