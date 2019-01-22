#pragma once
#include "FileStreamHandler.h"
#include <string>
#include <fstream>
#include "FileStructure.h"

class AntenaInputsKeywordsHandler :
	protected FileStreamHandler {
public:
	AntenaInputsKeywordsHandler();
	~AntenaInputsKeywordsHandler(); 
	void readContent(std::ifstream *file, FileStructure *structure);
};

