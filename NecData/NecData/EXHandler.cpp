#include "stdafx.h"
#include "EXHandler.h"
#include "NecIn.h"
#include "TableValueParser.h"

using namespace std;

EXHandler::EXHandler() {
	this->setKeywords("EX");
}


EXHandler::~EXHandler()
{
}

void EXHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	str.erase(0, str.find("EX") + 2);
	TableValueParser p = TableValueParser(str);
	int type = p.getInt();
	int tag = p.getInt();
	int seg = p.getInt();
	int admittance = p.getInt();
	double valueRe = p.getDouble();
	double valueIm = p.getDouble();
	EX ex(type, tag, seg, admittance, valueRe, valueIm);
	in->pushEX(ex);
}
