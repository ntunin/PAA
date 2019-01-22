#pragma once
#include <string>

#ifdef NECDATA_EXPORTS  
#define NECDATA_API __declspec(dllexport)   
#else  
#define NECDATA_API __declspec(dllimport)   
#endif 

class NecCommand {
public:
	NECDATA_API NecCommand();
	NECDATA_API ~NecCommand();
	NECDATA_API virtual std::string toString() = 0;
	NECDATA_API std::string toString(int value, int stringSize);
	NECDATA_API std::string toString(double value, int stringSize);
	NECDATA_API std::string toString(double value, int stringSize, bool exp);
};

