#include "stdafx.h"
#include "GWHandler.h"
#include "NecIn.h"
#include "TableValueParser.h"

using namespace std;

GWHandler::GWHandler() {
	this->setKeywords("GW");
}


GWHandler::~GWHandler()
{
}


void GWHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	str.erase(0, str.find("GW") + 2);
	TableValueParser p = TableValueParser(str);
	int tag = p.getInt();
	int seg = p.getInt();
	double x1 = p.getDouble();
	double y1 = p.getDouble();
	double z1 = p.getDouble();
	double x2 = p.getDouble();
	double y2 = p.getDouble();
	double z2 = p.getDouble();
	double radius = p.getDouble();
	GW gw(tag, seg, x1, y1, z1, x2, y2, z2, radius);
	in->pushGW(gw);
}