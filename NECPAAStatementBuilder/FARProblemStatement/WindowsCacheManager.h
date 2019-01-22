#pragma once
#include "CacheManager.h"
class WindowsCacheManager :
	public CacheManager
{
private:
	std::string WindowsCacheManager::cachedFileName(std::string name);
public:
	WindowsCacheManager(std::string path);
	bool cached(std::string filename);
	void fill(std::string filename, NecOut **out);
	void cache(std::string filename, NecOut **out);
	~WindowsCacheManager();
};

