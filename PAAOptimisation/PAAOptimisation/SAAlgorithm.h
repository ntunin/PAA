#pragma once
#include "NTInitialVectorAlgorithm.h"
#include "RandomGenerator.h"
#include "NTStandartMathProblem.h"
#include "LinearSearch.h"

class SAAlgorithm: public NTInitialVectorAlgorithm
{
private:
	double TInitial;
	double T;
	double coolDownSpeed;
	RandomGenerator *r;
	double radius;
	void getRandomOffset(double *x, int size, double radius);
	void coppyValues(double *x, int size);
	double *xM;
protected:
	MathProblems::NTLinearSearch *linearSearch;
	double lastF;
	double f;
	int size;
	double *x;
	double *direction;
	double *xTmp;
	double step;
public:
	SAAlgorithm(Math::Vector<double> *initial, double T, double speed, double radius);
	Math::Vector<double> *solve(MathProblems::NTStandartMathProblem *problem);
	void makeStep(MathProblems::NTStandartMathProblem *problem);
	~SAAlgorithm();
};

