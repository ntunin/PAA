#include "stdafx.h"
#include "NecInParser.h"
#include <sstream>
#include <stdlib.h>
#include "CMHandler.h"
#include "CEHandler.h"
#include "GWHandler.h"
#include "GEHandler.h"
#include "GNHandler.h"
#include "FRHandler.h"
#include "EXHandler.h"
#include "PTHandler.h"
#include "ENHandler.h"
#include "RPHandler.h"


using namespace std;

NecInParser::NecInParser(std::string &fileName, NecIn *in) {
	this->in = in;
	this->parse(fileName);
}


StringHandler **createKeywordsHandlers(int &count) {
	count = 10;
	return new StringHandler*[count] {
		new CMHandler,
		new CEHandler,
		new GWHandler,
		new GEHandler,
		new GNHandler,
		new FRHandler,
		new EXHandler,
		new PTHandler,
		new RPHandler,
		new ENHandler
	};
}


void removeHandlers(int count, StringHandler **handlers) {
	for (int i = 0; i < count; i++) {
		delete handlers[i];
	}
	delete handlers;
}

void NecInParser::readFile(ifstream *file) {
	int count;
	StringHandler **handlers = createKeywordsHandlers(count);
	this->searchContentByKeywordsHandlers(file, count, handlers);
	removeHandlers(count, handlers);
}

NecInParser::~NecInParser() {
}

void NecInParser::searchContentByKeywordsHandlers(ifstream *file, int handlersCount, StringHandler **handlers) {
	string buffer;
	while (!file->eof()) {
		getline(*file, buffer);
		for (int i = 0; i < handlersCount; i++) {
			if (handlers[i]->checkString(buffer)) {
				handlers[i]->readContent(buffer, this->in);
			}
		}
	}
}


