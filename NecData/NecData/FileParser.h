#pragma once
#include <fstream>
#include <vector>
#include "KeywordsHandler.h"

class FileParser {
public:
	FileParser();
	~FileParser();
private:
	std::string getAbsolutePath(std::string &fileName);
	std::ifstream openFile(std::string &fileName);
	void onOpenFileError(std::string &fileName);
protected:
	virtual void readFile(std::ifstream *file) = 0;
	void parse(std::string &fileName);
};

