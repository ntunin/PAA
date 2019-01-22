#include "stdafx.h"
#include "OneSourceNecInWritter.h"
#include "OneSourceNecInWritterException.h"

using namespace std;

OneSourceNecInWritter::OneSourceNecInWritter(int sourceNumber, NecIn *in, string name) {
	try {
		this->name = name;
		this->sourceNumber = sourceNumber;
		this->in = in;
		ofstream file(this->name);
		this->writeStream(file);
		file.close();
	}
	catch (exception e) {
		throw OneSourceNecInWritterException("An error occured while trying to write one-source nec-in file");
	}
}

void write(ofstream &file, NecCommand *command) {
	if (command) {
		std::string str = command->toString();
		file << str << endl;
	}
}

void write(ofstream &file, vector<EX *> *commandsPointer, int sourceNumber) {
	if (commandsPointer) {
		vector<EX *> commands = *commandsPointer;
		int size = (int)commands.size();
		for (int i = 0; i < size; i++) {
			if (i == sourceNumber) {
				NecCommand *command = commands[i];
				std::string str = command->toString();
				file << str << endl;
			} else {
				NecCommand *command = new EX(*commands[i], true);
				std::string str = command->toString();
				file << str << endl;
				delete command;
			}
		}
	}
}

void write(ofstream &file, vector<NecCommand *> *commandsPointer) {
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

void OneSourceNecInWritter::writeStream(ofstream &stream) {
	write(stream, this->in->getCM());
	write(stream, this->in->getCE());
	write(stream, (vector<NecCommand *> *)this->in->getGW());
	write(stream, this->in->getGE());
	write(stream, this->in->getGN());
	write(stream, this->in->getFR());
	write(stream, this->in->getEX(), this->sourceNumber);
	write(stream, this->in->getPT());
	write(stream, this->in->getRP());
	write(stream, this->in->getEN());
}



OneSourceNecInWritter::~OneSourceNecInWritter()
{
}
