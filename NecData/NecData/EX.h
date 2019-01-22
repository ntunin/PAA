#pragma once
#include "NecCommand.h"
#include "Complex.h"

#ifdef NECDATA_EXPORTS  
#define NECDATA_API __declspec(dllexport)   
#else  
#define NECDATA_API __declspec(dllimport)   
#endif 


using namespace Math;

class EX : public NecCommand {
private:
	int type;
	int tag;
	int seg;
	int admittance;
	Complex value;
public:
	NECDATA_API EX(int type, int tag, int seg, int admittance, double valueRe, double valueIm);
	NECDATA_API EX(EX &ex);
	NECDATA_API EX(EX &ex, Complex &source);
	NECDATA_API EX(EX &ex, bool disabled);
	NECDATA_API int getTag();
	NECDATA_API void setTag(int tag);
	NECDATA_API ~EX();
	NECDATA_API std::string toString();
	NECDATA_API Complex &getValue();
};

