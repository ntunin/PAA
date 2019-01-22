#pragma once
#include <fstream>
#include <vector>
#include "NecIn.h"
#include "FileParser.h"
#include "StringHandler.h"

#ifdef NECDATA_EXPORTS  
#define NECDATA_API __declspec(dllexport)   
#else  
#define NECDATA_API __declspec(dllimport)   
#endif 

class NecInParser: FileParser {
public:
	NECDATA_API NecInParser(std::string &fileName, NecIn *in);
	NECDATA_API ~NecInParser();
protected:
	NECDATA_API void readFile(std::ifstream *file);
private: 
	void searchContentByKeywordsHandlers(std::ifstream *file, int handlersCount, StringHandler **handlers);
	NecIn *in;
};

