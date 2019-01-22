#include "stdafx.h"
#include "ENHandler.h"
#include "NecIn.h"

using namespace std;

ENHandler::ENHandler() {
	this->setKeywords("EN");
}


ENHandler::~ENHandler() {
}

void ENHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	EN en;
	in->setEN(en);
}
