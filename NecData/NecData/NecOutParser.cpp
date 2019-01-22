#include "stdafx.h"
#include "NecOutParser.h"
#include <sstream>
#include <stdlib.h>
#include "AntenaInputsKeywordsHandler.h"
#include "RadiationKeywordsHandler.h"

using namespace std;

NecOutParser::NecOutParser(std::string &fileName, NecOut *out) {
	this->out = out;
	this->parse(fileName);
}


FileStreamHandler **createHandlers(int &count) {
	count = 2;
	FileStreamHandler **handlers = new FileStreamHandler*[count] {
		(FileStreamHandler *)(new AntenaInputsKeywordsHandler()),
			(FileStreamHandler *)(new RadiationKeywordsHandler())
	};
	return handlers;
}

void removeHandlers(int count, FileStreamHandler **handlers) {
	for (int i = 0; i < count; i++) {
		delete handlers[i];
	}
	delete handlers;
}

void NecOutParser::readFile(ifstream *file) {
	int count;
	FileStreamHandler **handlers = createHandlers(count);
	this->searchContentByKeywordsHandlers(file, 2, handlers);
	removeHandlers(count, handlers);
}



NecOutParser::~NecOutParser() {
}


void NecOutParser::searchContentByKeywordsHandlers(ifstream *file, int handlersCount, FileStreamHandler **handlers) {
	string buffer;
	while (!file->eof()) {
		getline(*file, buffer);
		for (int i = 0; i < handlersCount; i++) {
			if (handlers[i]->checkString(buffer)) {
				handlers[i]->readContent(file, this->out);
			}
		}
	}
}