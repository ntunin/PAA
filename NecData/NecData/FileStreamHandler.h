#pragma once
#include "KeywordsHandler.h"
class FileStreamHandler :
	public KeywordsHandler
{

public:
	FileStreamHandler();
	~FileStreamHandler();
	virtual void readContent(std::ifstream *file, FileStructure *structure) = 0;
	bool checkString(std::string str);
};

