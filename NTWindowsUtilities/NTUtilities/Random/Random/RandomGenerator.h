#pragma once
#include <mutex>

#ifdef RANDOM_EXPORTS  
#define RANDOM_API __declspec(dllexport)   
#else  
#define RANDOM_API __declspec(dllimport)   
#endif 

class RandomGenerator
{
private:
	static RandomGenerator *shared;
public:
	RANDOM_API static void setSharedGenerator(RandomGenerator *generator);
	RANDOM_API static RandomGenerator *getSharedGenerator();
	RANDOM_API virtual int next() = 0;
	RANDOM_API RandomGenerator();
	RANDOM_API ~RandomGenerator();
};

