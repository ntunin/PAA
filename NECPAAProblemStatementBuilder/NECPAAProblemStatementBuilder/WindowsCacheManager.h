#pragma once
#include "CacheManager.h"


#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 


class WindowsCacheManager :
	public CacheManager
{
private:
	std::string cachedFileName(std::string name);
	std::string subdir;
public:
	NECPAAPROBLEMSTATEMENTBUILDER_API WindowsCacheManager(std::string path, std::string subdir);
	NECPAAPROBLEMSTATEMENTBUILDER_API bool cached(std::string filename);
	NECPAAPROBLEMSTATEMENTBUILDER_API void fill(std::string filename, NecOut **out);
	NECPAAPROBLEMSTATEMENTBUILDER_API void cache(std::string filename);
	NECPAAPROBLEMSTATEMENTBUILDER_API ~WindowsCacheManager();
};

