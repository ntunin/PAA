#pragma once
#include <fstream>
#include "FileStructure.h"

class KeywordsHandler {
public:
	KeywordsHandler();
	~KeywordsHandler();
	bool checkString(std::string str);
	void setKeywords(const char *keywords);
protected:
	void skip(std::ifstream *file, int count);
	std::string getKeywords();
private:
	const char *keywords;
};