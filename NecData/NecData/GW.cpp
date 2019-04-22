#include "stdafx.h"
#include "GW.h"
#include <sstream>
#include <string>


GW::GW(int tag, int seg, double x1, double y1, double z1, double x2, double y2, double z2, double radius) {
	this->tag = tag;
	this->seg = seg;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->z1 = z1;
	this->z2 = z2;
	this->radius = radius;
}

GW::GW(GW &gw) {
	this->tag = gw.tag;
	this->seg = gw.seg;
	this->x1 = gw.x1;
	this->x2 = gw.x2;
	this->y1 = gw.y1;
	this->y2 = gw.y2;
	this->z1 = gw.z1;
	this->z2 = gw.z2;
	this->radius = gw.radius;
}


void GW::translate(double x, double y, double z) {
	this->x1 += x;
	this->x2 += x;
	this->y1 += y;
	this->y2 += y;
	this->z1 += z;
	this->z2 += z;
}

void GW::rotateX(double a) {
	double y, z;
	y = this->y1*cos(a) - this->z1*sin(a);
	z = this->y1*sin(a) + this->z1*cos(a);
	this->y1 = y;
	this->z1 = z;
	y = this->y2*cos(a) - this->z2*sin(a);
	z = this->y2*sin(a) + this->z2*cos(a);
	this->y2 = y;
	this->z2 = z;
}


void GW::rotateY(double a) {
	double x, z;
	x = this->x1*cos(a) + this->z1*sin(a);
	z = -this->z1*sin(a) + this->z1*cos(a);
	this->x1 = x;
	this->z1 = z;
	x = this->x2*cos(a) + this->z2*sin(a);
	z = -this->z2*sin(a) + this->z2*cos(a);
	this->x2 = x;
	this->z2 = z;
}


void GW::rotateZ(double a) {
	double x, y;
	x = this->x1*cos(a) - this->y1*sin(a);
	y = this->x1*sin(a) + this->y1*cos(a);
	this->x1 = round(x * 100)/100;
	this->y1 = round(y * 100) / 100;
	x = this->x2*cos(a) - this->y2*sin(a);
	y = this->x2*sin(a) + this->y2*cos(a);
	this->x2 = round(x * 100) / 100;
	this->y2 = round(y * 100) / 100;
}


void GW::setTag(int tag) {
	this->tag = tag;
}

int GW::getTag() {
	return this->tag;
}


GW::~GW(){
}

std::string GW::toString() {
	std::stringstream stream;
	stream << "GW"
		<< ((NecCommand *)this)->toString(this->tag, 5) 
		<< ((NecCommand *)this)->toString(this->seg, 5)
		<< ((NecCommand *)this)->toString(this->x1, 9, false) 
		<< ((NecCommand *)this)->toString(this->y1, 9, false)
		<< ((NecCommand *)this)->toString(this->z1, 9, false) 
		<< ((NecCommand *)this)->toString(this->x2, 9, false)
		<< ((NecCommand *)this)->toString(this->y2, 9, false) 
		<< ((NecCommand *)this)->toString(this->z2, 9, false)
		<< ((NecCommand *)this)->toString(this->radius, 9, false);
	return stream.str();
}

