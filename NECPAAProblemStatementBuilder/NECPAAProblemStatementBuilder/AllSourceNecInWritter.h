#pragma once
#include "NTMath.h"
#include <fstream>
#include "NecIn.h"

#ifdef NECPAAPROBLEMSTATEMENTBUILDER_EXPORTS  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllexport)   
#else  
#define NECPAAPROBLEMSTATEMENTBUILDER_API __declspec(dllimport)   
#endif 


class AllSourceNecInWritter {

private:
	void writeStream(std::ofstream &stream);
	Math::Vector<Math::Complex>  *sources;
	NecIn *in;
	std::string name;

	void write(std::ofstream &file, std::vector<NecCommand *> *commandsPointer);
	void write(std::ofstream &file, std::vector<EX *> *commandsPointer, Math::Vector<Math::Complex> *sources);
	void write(std::ofstream &file, NecCommand *command);

public:
	NECPAAPROBLEMSTATEMENTBUILDER_API AllSourceNecInWritter(Math::Vector<Math::Complex> *sourceValues, NecIn *in, std::string name);
	NECPAAPROBLEMSTATEMENTBUILDER_API ~AllSourceNecInWritter();
};

