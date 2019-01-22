#pragma once
#include "KeywordsHandler.h"
#include <string>
#include <fstream>
#include "FileStructure.h"
#include "FileStreamHandler.h"

class RadiationKeywordsHandler :
	protected FileStreamHandler
{
public:
	~RadiationKeywordsHandler();
	RadiationKeywordsHandler();
	void readContent(std::ifstream *file, FileStructure *structure);
};

