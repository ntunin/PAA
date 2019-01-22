#pragma once
#include "NecIn.h"
#include "Vector.h"


using namespace Math;

class NecInWritter
{
	void writeStream(std::ofstream &stream);
	NecIn *in;
	std::string name;

	void write(std::ofstream &file, std::vector<NecCommand *> *commandsPointer);
	void write(std::ofstream &file, std::vector<EX *> *commandsPointer, Vector<Complex> *sources);
	void write(std::ofstream &file, NecCommand *command);

public:
	NecInWritter(NecIn *in, std::string name);
	~NecInWritter();
};

