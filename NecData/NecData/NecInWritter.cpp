#include "stdafx.h"
#include "NecInWritter.h"
#include <fstream>
#include "AntenaInputsKeywordsHandler.h"
#include "AllSourceNecInWritterException.h"


using namespace std;
using namespace Math;

NecInWritter::NecInWritter(NecIn *in, std::string name) {
	try {
		this->name = name;
		this->in = in;
		ofstream file(this->name);
		this->writeStream(file);
		file.close();
	}
	catch (exception e) {
		throw AllSourceNecInWritterException("An error occured while trying to replace sources of nec-in file");
	}
}

void NecInWritter::write(ofstream &file, NecCommand *command) {
	if (command) {
		std::string str = command->toString();
		file << str << endl;
	}
}

void NecInWritter::write(ofstream &file, vector<EX *> *commandsPointer, Vector<Complex> *sources) {
	if (commandsPointer) {
		vector<EX *> commands = *commandsPointer;
		int size = (int)commands.size();
		for (int i = 0; i < size; i++) {
			if (i >= sources->size()) {
				return;
			}
			Complex source = (*sources)[i];
			NecCommand *command = new EX(*commands[i], source);
			std::string str = command->toString();
			file << str << endl;
			delete command;
		}
	}
}

void NecInWritter::write(ofstream &file, vector<NecCommand *> *commandsPointer) {
	if (commandsPointer) {
		vector<NecCommand *> commands = *commandsPointer;
		int size = (int)commands.size();
		for (int i = 0; i < size; i++) {
			NecCommand *command = commands[i];
			std::string str = command->toString();
			file << str << endl;
		}
	}
}

void NecInWritter::writeStream(ofstream &stream) {
	write(stream, this->in->getCM());
	write(stream, this->in->getCE());
	write(stream, (vector<NecCommand *> *)this->in->getGW());
	write(stream, this->in->getGE());
	write(stream, this->in->getGN());
	write(stream, this->in->getFR());
	write(stream, (vector<NecCommand *> *)this->in->getEX());
	write(stream, this->in->getPT());
	write(stream, this->in->getRP());
	write(stream, this->in->getEN());
}

NecInWritter::~NecInWritter()
{
}
