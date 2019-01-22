#include "stdafx.h"
#include "CMHandler.h"
#include "NecIn.h"

using namespace std;

CMHandler::CMHandler() {
	this->setKeywords("CM");
}


CMHandler::~CMHandler() {
}

void CMHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	CM cm;
	in->setCM(cm);
}
