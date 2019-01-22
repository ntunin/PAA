#include "stdafx.h"
#include "PTHandler.h"
#include "NecIn.h"
#include "TableValueParser.h"

using namespace std;

PTHandler::PTHandler() {
	this->setKeywords("PT");
}


PTHandler::~PTHandler()
{
}

void PTHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	str.erase(0, str.find("PT") + 2);
	TableValueParser p = TableValueParser(str);
	int flag = p.getInt();
	PT pt(flag);
	in->setPT(pt);
}
