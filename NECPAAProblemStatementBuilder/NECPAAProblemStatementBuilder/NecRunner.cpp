#include "stdafx.h"
#include "NecRunner.h"
#include <sstream>
#include <iostream>
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include "Log.h"
#include "RandomGenerator.h"
#include "NecOutParser.h"
#include "OneSourceNecInWritter.h"

using namespace std;

NecRunner::NecRunner(NecIn *in) {
	this->in = in;
}


void NecRunner::runNEC(WindowsCacheManager *manager, int sourceNumber, NecOut **outs) {
	this->sourceNumber = sourceNumber;
	this->cacheManager = manager;
	this->outs = outs;
	this->startInNewThread();
}

string buildInOutArgs(string inName, string outName) {
	stringstream command;
	command << inName << endl;
	command << outName << endl;
	string commandString = command.str();
	return commandString;
}

void NecRunner::dispatch() {
	randomize();
	string name = createName(this->thread.get_id(), this->sourceNumber);
	string inName = string(name).append(".nec");
	string outName = string(name).append(".out");
	OneSourceNecInWritter(this->sourceNumber, this->in, inName);
	string commandString = buildInOutArgs(inName, outName);
	Log::getSharedLog()->print(string("Temporary i/o name: ").append(name).append("\n"));
	this->exe("nec2dxs11k.exe", commandString);
	Log::getSharedLog()->print(string("The nec2 finised. Temporary i/o with name: ").append(name).append(" was removed\n"));
	stringstream command;
	command << "tmp-" << this->sourceNumber << ".out";
	string tmpName = command.str();
	NecOutParser(outName, outs[sourceNumber]);
	cacheManager->cache(outName);
	removeFile(inName);
	removeFile(outName);
}

void NecRunner::randomize() {
	stringstream s;
	s << this->thread.get_id();
	int i = atoi(s.str().c_str());
	int t = time(NULL) % 10 + time(NULL) % 20 * 50 + time(NULL) % 50 * 20;
	t *= i * 10 * (this->sourceNumber + 1);
	srand(t);
}

string NecRunner::createName(thread::id id, int number) {
	stringstream s;
	s << "tmp-" << abs(RandomGenerator::getSharedGenerator()->next() % 1000 + 1) << "-";
	s << id;
	s << "-" << number;
	return s.str();
}

void NecRunner::removeFile(string &name) {
	if (remove(name.c_str()) != 0) {
		Log::getSharedLog()->print(string("could not remove the file ").append(name).append("\n"));
	}
}

NecRunner::NecRunner()
{
}


NecRunner::~NecRunner()
{
}
