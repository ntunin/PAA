#pragma once
#include "NecIn.h"
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h> 

#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 

class OneSourceNecInWritter {

private:
	void writeStream(std::ofstream &stream);
	int sourceNumber;
	NecIn *in;
	std::string name;

public:
	NECPAAPROBLEMSTATEMENTBUILDER_API OneSourceNecInWritter(int sourceNumber, NecIn *in, std::string name);
	NECPAAPROBLEMSTATEMENTBUILDER_API ~OneSourceNecInWritter();
};

