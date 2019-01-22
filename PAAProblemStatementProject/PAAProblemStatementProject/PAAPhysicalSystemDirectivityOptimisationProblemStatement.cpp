#include "stdafx.h"
#include "PAAPhysicalSystemDirectivityOptimisationProblemStatement.h"
#include "NTMath.h"

using namespace Math;
using namespace PAA;

PhysicalSystemDirectivityOptimisationProblemStatement::PhysicalSystemDirectivityOptimisationProblemStatement(PhysicalSystem *physicalSystem, std::vector<double> constraints, double theta, double phi): PhysicalSystemProblemStatement(physicalSystem, constraints, theta, phi)
{
}


PhysicalSystemDirectivityOptimisationProblemStatement::~PhysicalSystemDirectivityOptimisationProblemStatement()
{
}


std::vector<Math::Matrix<double> *> *PhysicalSystemDirectivityOptimisationProblemStatement::getB() {
	std::vector<Math::Matrix<double> *> *B = new std::vector<Math::Matrix<double> *>;
	int N = constraints.size();
	Matrix<Complex> *Y = this->physicalSystem->getY();
	Matrix<Complex> *_Y = Utils::econj(Y);
	Matrix<Complex> PkY(Y->width(), Y->height());
	Matrix<Complex> _YPk(Y->width(), Y->height());
	Matrix<Complex> _YPkPkY(Y->width(), Y->height());
	for (int k = 0; k < N; k++) {
		int dSize = 2 * N;
		Matrix<Complex> *Pk = buildProjector(k, N);
		Utils::mul(*_Y, *Pk, _YPk);
		Utils::mul(*Pk, *Y, PkY);
		Utils::summ(_YPk, PkY, _YPkPkY);
		Matrix<double> *Bk = Utils::convert(_YPkPkY);
		B->push_back(Bk);
		delete Pk;
	}
	delete _Y;
	return B;
}
