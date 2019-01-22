#pragma once
#include <fstream>
#include <vector>
#include "NecOut.h"
#include "FileParser.h"
#include "FileStreamHandler.h"

#ifdef NECDATA_EXPORTS  
#define NECDATA_API __declspec(dllexport)   
#else  
#define NECDATA_API __declspec(dllimport)   
#endif 




class NecOutParser: FileParser {
public:
	NECDATA_API NecOutParser(std::string &filename, NecOut *out);
	NECDATA_API ~NecOutParser();
private:
	NecOut *out;
	void searchContentByKeywordsHandlers(std::ifstream *file, int handlersCount, FileStreamHandler **handlers);
protected:
	NECDATA_API void readFile(std::ifstream *file);
};