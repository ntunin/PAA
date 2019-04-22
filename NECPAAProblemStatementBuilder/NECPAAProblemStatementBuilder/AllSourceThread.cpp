#include "stdafx.h"
#include "AllSourceThread.h"
#include <sstream>
#include <iostream>
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include "AllSourceNecInWritter.h"
#include "Log.h"
#include "NecOutParser.h"

#define BUFSIZE 4096



using namespace std;

AllSourceThread::AllSourceThread(NecIn *in, Math::Vector<Math::Complex> *sources, const char *fileName, NecOut *out) {
	this->in = in;
	this->sources = sources;
	this->fileName = string(fileName);
	this->out = out;
	//this->createThread();
}


void AllSourceThread::dispatch() {
	string inName = string(this->fileName).append(".nec");
	string outName = string(this->fileName).append(".out");
	AllSourceNecInWritter(this->sources, this->in, inName);
	stringstream command;
	command << inName << endl;
	command << outName << endl;
	string commandString = command.str();
	//Shared::bundle().log()->print(string("Please wait while nec2 making calculations for optimased sources. i/o name: ").append(this->fileName).append("\n"));
	//this->exe(string("nec2dxs11k.exe"), commandString);
	//Shared::bundle().log()->print(string("The nec2 finised. i/o name: ").append(this->fileName).append("\n"));
	NecOutParser(outName, out);
}

NecOut *AllSourceThread::getOut() {
	return this->out;
}

AllSourceThread::~AllSourceThread()
{
}