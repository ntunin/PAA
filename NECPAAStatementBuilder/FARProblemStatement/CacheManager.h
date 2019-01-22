#pragma once
#include "NecOut.h"
#include "FARProblemStatement.h"
#include <string>

class CacheManager {
public:
	CacheManager();
	~CacheManager();
	virtual bool cached(std::string filename) = 0;
	virtual void fill(std::string filename, NecOut **out) = 0;
	virtual void cache(std::string filename, NecOut **out) = 0;
protected:
	std::string path;
};

