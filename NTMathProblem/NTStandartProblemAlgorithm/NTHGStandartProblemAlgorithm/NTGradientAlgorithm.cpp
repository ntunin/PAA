#include "stdafx.h"
#include "NTGradientAlgorithm.h"
#include <math.h>
#include "Log.h"
#include <sstream>
#include "WindowsUtils.h"

using namespace Math;


int NTGradientAlgorithm::time;
int NTGradientAlgorithm::maxTime;

NTGradientAlgorithm::NTGradientAlgorithm(Math::Vector<double> *initial): NTInitialVectorAlgorithm(initial)
{
}


NTGradientAlgorithm::~NTGradientAlgorithm()
{
}

void randomize(int size, double *x) {
	for (int i = 0; i < size; i++) {
		x[i] = rand() % 1000 - 500;
	}
}

Math::Vector<double> *NTGradientAlgorithm::solve(NTGradientProblem *problem) {
	lastF = 0;
	f = 1e7;
	Vector<double> *solution = new Vector<double>(*initial);
	size = solution->size();
	x = new double[size];
	xTmp = new double[size];
	direction = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*solution)[i];
	}
	problem->normalize(size, x);
	step = 1;
	linearSearch = new NTLinearSearch(problem);
	Log *l = Log::getSharedLog();
	std::uint64_t start = WindowsUtils::time();
	std::uint64_t end;
	int count = 0;
	int threshold = maxTime / 10;
	while (fabs(lastF - f) > 1e-4) {
		end = WindowsUtils::time();
		std::uint64_t workingTime = end - start;
		start = end;
		time += workingTime;

		count++;

		if (time > maxTime) {
			break;
		}
		makeStep(problem);
		//std::string desc = problem->stepDescription(size, x);
		//l->print(desc);
	}

	for (int i = 0; i < size; i++) {
		(*solution)[i] = x[i];
	}
	delete[] xTmp;
	delete[] direction;
	delete[] x;
	delete linearSearch;

	return solution;
		
}

void NTGradientAlgorithm::makeStep(NTGradientProblem *problem) {
	bool haveValidDirection = false;
	lastF = f;
	f = problem->targetFunction(size, x);
	problem->getGradient(size, x, direction);
	Utils::normalize(size, direction);
	//Utils::mul(size, direction, -1.0, direction);

	for (int i = 0; i < size; i++) {
		xTmp[i] = x[i] + step * direction[i];
	}
	double fPlus = problem->targetFunction(size, xTmp);

	if (fPlus < f) {
		haveValidDirection = true;
	}

	if (!haveValidDirection) {
		step /= 2;
		lastF = -1e7;
		return;
	}

	linearSearch->dsk(size, x, direction);

	f = problem->targetFunction(size, x);
}