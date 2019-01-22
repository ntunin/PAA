#include "stdafx.h"
#include "RPHandler.h"
#include "NecIn.h"
#include "TableValueParser.h"
#include "RP.h"

using namespace std;

RPHandler::RPHandler() {
	this->setKeywords("RP");
}


RPHandler::~RPHandler()
{
}


void RPHandler::readContent(string str, FileStructure *structure) {
	NecIn *in = (NecIn *)structure;
	str.erase(0, str.find("RP") + 2);
	TableValueParser p = TableValueParser(str);
	
	int mode = p.getInt();
	int thetaNumber = p.getInt();
	int phiNumner = p.getInt();
	string XNDA = p.getString(true);
	double theta0 = p.getDouble();
	double phi0 = p.getDouble();
	double thetaInc = p.getDouble();
	double phiInc = p.getDouble();
	RP rp(mode, thetaNumber, phiNumner, XNDA, theta0, phi0, thetaInc, phiInc);
	in->setRP(rp);
}
