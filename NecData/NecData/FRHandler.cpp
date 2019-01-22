#include "stdafx.h"
#include "FRHandler.h"
#include "NecIn.h"
#include "TableValueParser.h"
#include "FR.h"

using namespace std;

FRHandler::FRHandler() {
	this->setKeywords("FR");
}


FRHandler::~FRHandler()
{
}

void FRHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	str.erase(0, str.find("FR") + 2);
	TableValueParser p = TableValueParser(str);
	int stepsType = p.getInt();
	int stepsNumber = p.getInt();
	p.getInt();
	p.getInt();
	double frequency = p.getDouble();
	FR fr(stepsType, stepsNumber, frequency);
	in->setFR(fr);
}
