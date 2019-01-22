#include "stdafx.h"
#include "RadiationKeywordsHandler.h"
#include "NecOut.h"
#include "TableValueParser.h"

using namespace std;

RadiationKeywordsHandler::RadiationKeywordsHandler() {
	this->setKeywords("RADIATION PATTERNS");
}

RadiationKeywordsHandler::~RadiationKeywordsHandler() {

}


void RadiationKeywordsHandler::readContent(ifstream *file, FileStructure *structure) {
	NecOut *out = (NecOut *)structure;
	skip(file, 4); // Skip empty lines and legend
	string buffer = "error";
	TableValueParser p = TableValueParser(buffer);
	while (buffer != "") {
		getline(*file, buffer);
 		p.setInput(buffer);
		double theta = p.getDouble();
		double phi = p.getDouble();
		double verticalGain = p.getDouble();
		double horisontalGain = p.getDouble();
		double totalGain = p.getDouble();
		double axialPolarisation = p.getDouble();
		double polarisationTilt = p.getDouble();
		string polarisationSense = p.getString(false);
		double eThetaMagnitude = p.getDouble();
		double eThetaPhase = p.getDouble();
		double ePhiMagnitude = p.getDouble();
		double ePhiPhase = p.getDouble();
		out->addRadiationPattern(theta, phi, verticalGain, horisontalGain, totalGain, axialPolarisation, polarisationTilt, polarisationSense, eThetaMagnitude, eThetaPhase, ePhiMagnitude, ePhiPhase);
	}
}
