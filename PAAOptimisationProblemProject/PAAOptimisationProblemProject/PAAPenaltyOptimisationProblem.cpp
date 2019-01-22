#include "stdafx.h"
#include "PAAPenaltyOptimisationProblem.h"
#include "NTMath.h"
#include <vector>
#include "RandomGenerator.h"

using namespace std;
using namespace Math;
using namespace PAA;

PenaltyOptimisationProblem::PenaltyOptimisationProblem(Math::Matrix<Math::Complex> *A, std::vector<Math::Matrix<Math::Complex> *> *B, double factor, double degree): OptimisationProblem(A, B)
{
	this->factor = factor;
	this->degree = degree;
	int size = 2 * B->size();
}

PenaltyOptimisationProblem::PenaltyOptimisationProblem(Math::Matrix<double> *A, std::vector<Math::Matrix<double> *> *B, double factor, double degree): OptimisationProblem(A, B)
{
	this->factor = factor;
	this->degree = degree;
	int size = 2 * B->size();
}


double PenaltyOptimisationProblem::targetFunction(int size, double *v) {
	double uAu = this->calculate_uAu(size, v);
	vector<double> *uBu = this->calculate_uBu(size, v);
	int M = uBu->size();
	double s = 0;

	for (int i = 0; i < M; i++) {
		double uBiu = (*uBu)[i];
		s += -pow(abs(min(uBiu, 0) + max(uBiu, 1) - 1), degree);
	}
	return -(uAu + factor * s);
}

void PenaltyOptimisationProblem::getGradient(int size, double *v, double *d) {
	Math::Utils::fill(size, 0, d);
	Math::Utils::gradient(size, A->toArray(), v, d);
	vector<double> *uBus = this->calculate_uBu(size, v);
	for (int i = 0; i < uBus->size(); i++) {
		double *duBu = new double[size];
		double uBu = (*uBus)[i];
		if (uBu >= 0 && uBu <= 1) {
			Utils::fill(size, 0, duBu);
		}
		else {
			int uno = (uBu > 1) ? -1 : 0;
			double m = factor * degree * pow(uBu + uno, degree - 1);
			Matrix<double> B = *(*this->B)[i];
			Utils::gradient(size, B.toArray(), v, duBu);
			Utils::mul(size, duBu, m, duBu);
		}
		Utils::mul(size, duBu, -1, duBu);
		Utils::summ(size, d, duBu, d);
	}
}

PenaltyOptimisationProblem::~PenaltyOptimisationProblem()
{
}
