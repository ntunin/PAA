#include "stdafx.h"
#include "LinearSearch.h"

using namespace Math;
using namespace MathProblems;

NTLinearSearch::NTLinearSearch(NTStandartMathProblem *problem)
{
	this->problem = problem;
	this->size = problem->size;
	this->xNext = new Vector<double>(size);
	this->xTmp = new Vector<double>*[4];
	for (int i = 0; i < 4; i++) {
		this->xTmp[i] = new Vector<double>(size);
	}
}

void translate(int size, double *x, double *x0, double *direction, double a) {
	for (int i = 0; i < size; i++) {
		x[i] = x0[i] + a * direction[i];
	}
}


void NTLinearSearch::dsk(int size, double *x, double *direction) {
	// 1 step
	double Dx0 = 1;
	double Dx = Dx0;
	int steps = 0;
	double *xi = new double[size];
	double path = 0;
	double fi = problem->targetFunction(size, x);
	double fi_1 = fi;
	double fi_2 = fi;

	while (true) {
		path += Dx;
		translate(size, xi, x, direction, path);
		fi = problem->targetFunction(size, xi);
		if (fi > fi_1) {
			if (steps > 2 || Dx0 < 1e-5) {
				break;
			}
			Dx0 /= 2;
			Dx = Dx0;
			path = 0;
			fi = problem->targetFunction(size, x);
			fi_1 = fi;
			fi_2 = fi;
			continue;
		}
		fi_2 = fi_1;
		fi_1 = fi;
		Dx *= 2;
		steps++;
	}
	


	double *xa = new double[size];
	double *xb = new double[size];
	double *xc = new double[size];

	Dx /= 2;

	path -= Dx * 3;
	translate(size, xa, x, direction, path);
	translate(size, xb, x, direction, path + Dx);
	translate(size, xc, x, direction, path + 2*Dx);

	double fa = problem->targetFunction(size, xa);
	double fb = problem->targetFunction(size, xb);
	double fc = problem->targetFunction(size, xc);

	path += (fc > fb)? ( Dx * (1 + (fa - fc) / (2 * (fa - 2 * fb + fc)))) : 2*Dx;

	translate(size, x, x, direction, path);


	double f = problem->targetFunction(size, x);

	delete[] xi;
	delete[] xa;
	delete[] xb;
	delete[] xc;
}



NTLinearSearch::~NTLinearSearch()
{
	for (int i = 0; i < 4; i++) {
		delete xTmp[i];
	}
	delete[] xTmp;
	delete xNext;
}
