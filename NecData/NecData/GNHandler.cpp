#include "stdafx.h"
#include "GNHandler.h"
#include "NecIn.h"
#include "TableValueParser.h"
#include "GN.h"

using namespace std;

GNHandler::GNHandler() {
	this->setKeywords("GN");
}


GNHandler::~GNHandler()
{
}

void GNHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	str.erase(0, str.find("GN") + 2);
	TableValueParser p = TableValueParser(str);
	int groundType = p.getInt();
	int radialWiresNumber = p.getInt();
	p.getInt();
	p.getInt();
	double dielectic = p.getDouble();
	double conductivity = p.getDouble();
	GN gn(groundType, radialWiresNumber, dielectic, conductivity);
	in->setGN(gn);
}
