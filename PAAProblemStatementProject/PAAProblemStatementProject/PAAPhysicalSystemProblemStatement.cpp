#include "stdafx.h"
#include "PAAPhysicalSystemProblemStatement.h"

using namespace PAA;
using namespace Math;

PhysicalSystemProblemStatement::PhysicalSystemProblemStatement(PhysicalSystem *physicalSystem, std::vector<double> constraints, double theta, double phi)
{
	this->physicalSystem = physicalSystem;
	this->iDirect = (int)theta / physicalSystem->getIStep();
	this->jDirect = (int)phi / physicalSystem->getJStep();
	this->constraints = constraints;
}

Math::Matrix<double> *PhysicalSystemProblemStatement::getA() {
	int sourceCount = this->physicalSystem->getSourceCount();
	Complex ****beamPattern = this->physicalSystem->getBeamPattern();
	Math::Matrix<Math::Complex> *A = new Math::Matrix<Math::Complex>(sourceCount);
	for (int i = 0; i < sourceCount; i++) {
		for (int j = 0; j < sourceCount; j++) {
			(*A)[i][j] = beamPattern[i][j][iDirect][jDirect];
		}
	}
	Math::Matrix<double> *result = Math::Utils::convert(A);
	delete A;
	return result;
}

void PhysicalSystemProblemStatement::setDirection(double theta, double phi) {
	this->iDirect = (int)theta / 5;
	this->jDirect = (int)phi / 5;
}

void PhysicalSystemProblemStatement::setConstraints(std::vector<double> constraints) {
	this->constraints = constraints;
}

Matrix<Complex> *PhysicalSystemProblemStatement::buildProjector(int k, int N) {
	Matrix<Complex> *P = new Matrix<Complex>(N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			(*P)[i][j] = Complex((i == k && j == k) ? 1 : 0, 0);
		}
	}
	return P;
}

PhysicalSystemProblemStatement::~PhysicalSystemProblemStatement()
{
}
