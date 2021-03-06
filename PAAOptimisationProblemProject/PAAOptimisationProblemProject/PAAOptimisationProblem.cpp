// OptimisationProblemProject.cpp : Определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "PAAOptimisationProblem.h"

using namespace std;
using namespace PAA;

OptimisationProblem::OptimisationProblem(Math::Matrix<Math::Complex> *A, std::vector<Math::Matrix<Math::Complex> *> *B)
{
	this->A = fillA(A);
	this->B = fillB(B);
	this->sourcesCount = B->size();
	int size = this->sourcesCount * 2;
	this->lastCheckedSolution = new double[size];
	this->uBus = new std::vector<double>;
	this->Bu = new double[size];
	this->Au = new double[size];
}

OptimisationProblem::OptimisationProblem(Math::Matrix<double> *A, std::vector<Math::Matrix<double> *> *B) {
	this->sourcesCount = B->size();
	this->A = fillA(A);
	this->B = fillB(B);
	int size = this->sourcesCount * 2;
	this->lastCheckedSolution = new double[this->sourcesCount * 2];
	this->uBus = new std::vector<double>;
	this->Bu = new double[size];
	this->Au = new double[size];
}

Math::Matrix<double> *OptimisationProblem::fillA(Math::Matrix<double> *A) {
	int size = 2 * sourcesCount;
	this->A = new Math::Matrix<double>(*A);
	return this->A;
}

std::vector<Math::Matrix<double>*> *OptimisationProblem::fillB(std::vector<Math::Matrix<double>*> *B) {
	int size = 2 * sourcesCount;
	this->B = new std::vector<Math::Matrix<double> *>;
	for (int k = 0; k < sourcesCount; k++) {
		this->B->push_back(new Math::Matrix<double>(*(*B)[k]));
	}
	return this->B;
}


OptimisationProblem::~OptimisationProblem()
{
	delete A;
	for (int i = 0; i < B->size(); i++) {
		delete (*B)[i];
	}
	delete B;
	delete uBus;
	delete[] Au;
	delete[] Bu;
}

Math::Matrix<double> *OptimisationProblem::fillA(Math::Matrix<Math::Complex> *A) {
	return Math::Utils::convert(A);
}

std::vector<Math::Matrix<double>*> *OptimisationProblem::fillB(std::vector<Math::Matrix<Math::Complex> *> *B) {
	int count = B->size();
	std::vector<Math::Matrix<double> *> *_B = new std::vector<Math::Matrix<double> *>;
	for (int i = 0; i < count; i++) {
		_B->push_back(Math::Utils::convert((*B)[i]));
	}
	return _B;
}


double OptimisationProblem::calculate_uAu(int size, double *v) {
	for (int i = 0; i < size; i++) {
		Au[i] = 0;
		for (int j = 0; j < size; j++) {
			Au[i] += (*A)[i][j] * v[j];
		}
	}
	double uAu = 0;
	for (int i = 0; i < size; i++) {
		uAu += v[i] * Au[i];
	}
	return uAu;
}

vector<double> * OptimisationProblem::calculate_uBu(int size, double *v) {
	bool sameSolution = true;
	for (int i = 0; i < size; i++) {
		if (v[i] != lastCheckedSolution[i]) {
			sameSolution = false;
			break;
		}
	}
	if (sameSolution) {
		return uBus;
	}
	for (int i = 0; i < sourcesCount; i++) {
		lastCheckedSolution[i] = v[i];
	}
	int N = sourcesCount;
	if (uBus->size() > 0) {
		uBus->clear();
	}
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < size; i++) {
			Bu[i] = 0;
			for (int j = 0; j < size; j++) {
				double b = (*(*B)[k])[i][j];
				Bu[i] += (*(*B)[k])[i][j] * v[j];
			}
		}
		double uBu = 0;
		for (int i = 0; i < size; i++) {
			uBu += v[i] * Bu[i];
		}
		uBus->push_back(uBu);
	}
	return uBus;
}