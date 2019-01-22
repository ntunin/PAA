#pragma once
#include "NecCommand.h"

class GW: public NecCommand {
public:
	GW(int tag, int seg, double x1, double y1, double z1, double x2, double y2, double z2, double radius);
	std::string toString();
	GW(GW &GW);
	~GW();
	void translate(double x, double y, double z);
	void rotateX(double a);
	void rotateY(double a);
	void rotateZ(double a);
	void setTag(int tag);
	int getTag();
private:
	int tag;
	int seg;
	double x1;
	double y1;
	double z1;
	double x2;
	double y2;
	double z2;
	double radius;
};

