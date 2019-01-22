#include "stdafx.h"
#include "CEHandler.h"
#include "NecIn.h"

using namespace std;

CEHandler::CEHandler() {
	this->setKeywords("CE");
}


CEHandler::~CEHandler(){
}

void CEHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	CE ce;
	in->setCE(ce);
}
