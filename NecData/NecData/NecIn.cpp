#include "stdafx.h"
#include "NecIn.h"


NecIn::NecIn() {
	this->gw = new std::vector<GW *>;
	this->ex = new std::vector<EX *>;
}


NecIn::~NecIn() {
	delete this->cm;
	delete this->ce;
	delete this->ge;
	delete this->gn;
	delete this->fr;
	delete this->pt;
	delete this->rp;
	delete this->en;
	for (int i = 0; i < this->gw->size(); i++) {
		delete (*this->gw)[i];
	}
	delete this->gw;
	for (int i = 0; i < this->ex->size(); i++) {
		delete (*this->ex)[i];
	}
	delete this->ex;
}


void NecIn::setGW(std::vector<GW *> *gw) {
	delete this->gw;
	this->gw = gw;
}

void NecIn::setEX(std::vector<EX *> *ex) {
	delete this->ex;
	this->ex = ex;
}

void NecIn::setCM(CM &cm) {
	this->cm = new CM;
}

void NecIn::setCE(CE &ce) {
	this->ce = new CE;
}

void NecIn::pushGW(GW &gw) {
	this->gw->push_back(new GW(gw));
}

void NecIn::setGE(GE &ge) {
	this->ge = new GE(ge);
}

void NecIn::setGN(GN &gn) {
	this->gn = new GN(gn);
}

void NecIn::setFR(FR &fr) {
	this->fr = new FR(fr);
}

void NecIn::pushEX(EX &ex) {
	this->ex->push_back(new EX(ex));
}

void NecIn::setPT(PT &pt) {
	this->pt = new PT(pt);
}

void NecIn::setRP(RP &rp) {
	this->rp = new RP(rp);
}

void NecIn::setEN(EN &en) {
	this->en = new EN;
}

std::vector<GW *>  *NecIn::getGW() {
	return this->gw;
}

CM *NecIn::getCM() {
	return this->cm;
}

CE *NecIn::getCE() {
	return this->ce;
}

GE *NecIn::getGE() {
	return this->ge;
}

GN * NecIn::getGN() {
	return this->gn;
}

FR * NecIn::getFR() {
	return this->fr;
}

EN * NecIn::getEN() {
	return this->en;
}

std::vector<EX *> *NecIn::getEX() {
	return this->ex;
}

PT *NecIn::getPT() {
	return this->pt;
}


RP *NecIn::getRP() {
	return this->rp;
}
