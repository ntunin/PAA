#pragma once
#include "RandomGenerator.h"

#ifdef RANDOM_EXPORTS  
#define RANDOM_API __declspec(dllexport)   
#else  
#define RANDOM_API __declspec(dllimport)   
#endif 

class DefaultRandomGenerator :
	public RandomGenerator
{
public:
	RANDOM_API int next();
	RANDOM_API DefaultRandomGenerator();
	RANDOM_API ~DefaultRandomGenerator();
};

