// PAAOptimisation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "ConsoleScanner.h"
#include "ConsoleLog.h"
#include "ProcessManager.h"
#include "RandomGenerator.h"
#include "TaskManager.h"
#include "WindowsRandomGenerator.h"
#include "WindowsProcessManager.h"
#include "WindowsTaskManager.h"
#include "NECPhysicalSystemBuilder.h"
#include "PAAPhysicalSystemDirectivityOptimisationProblemStatement.h"
#include "PAAPenaltyOptimisationProblem.h"
#include "NTHGAlgorithm.h"
#include "NTConjugateGradientAlgorithm.h"
#include "NTGradientAlgorithm.h"
#include "PAAFileProblemStatement.h"
#include "FileLog.h"

#include <string>

void printMatrix(Math::Matrix<double> *matrix);

PAA::ProblemStatement *getNecStatement(int theta, int phi) {	
	Log::getSharedLog()->print("Enter NEC file name: > ");
	std::string filename = "2x2WWE.nec";// Scanner::getSharedScanner()->readString();
	Log::getSharedLog()->print("Use cached results if exist? > ");
	bool useCache = true;//Scanner::getSharedScanner()->readBool();
	PAA::PhysicalSystem *system = PAA::NECPhysicalSystemBuilder(filename).buildSystem(useCache);
	Log::getSharedLog()->print("Enter theta: > ");
	//int theta = 70;// Scanner::getSharedScanner()->readDouble();
	Log::getSharedLog()->print("Enter phi: > ");
	//int phi = 45;// Scanner::getSharedScanner()->readDouble();
	std::vector<double> constraints;
	int sourceCount = system->getSourceCount();
	Log::getSharedLog()->print("Please enter restrictions:\n");
	for (int i = 0; i < sourceCount; i++) {
		Log::getSharedLog()->print(" "); 
		Log::getSharedLog()->print(i); 
		Log::getSharedLog()->print(": > ");
		double value = 1;// Scanner::getSharedScanner()->readDouble()
		constraints.push_back(value);
	}
	PAA::ProblemStatement *statement = new PAA::PhysicalSystemDirectivityOptimisationProblemStatement(system, constraints, theta, phi);
	return statement;
}

PAA::ProblemStatement *getFileStatement() {
	//Log::getSharedLog()->print("Enter statemnt file name: > ");
	std::string filename = "matrices.txt";// Scanner::getSharedScanner()->readString();
	return new PAA::FileProblemStatement(filename);
}

PAA::PenaltyOptimisationProblem *getPenaltyProblem(PAA::ProblemStatement *statement) {
	Math::Matrix<double> *A = statement->getA();
	std::vector<Math::Matrix<double> *> *B = statement->getB();

	//Log::getSharedLog()->print("Enter mulct factor: > ");
	double mulctFactor = 1000000;// Scanner::getSharedScanner()->readDouble();
	//Log::getSharedLog()->print("Enter mulct degree: > ");
	double mulctDegree = 4;// Scanner::getSharedScanner()->readDouble();
	PAA::PenaltyOptimisationProblem *problem = new PAA::PenaltyOptimisationProblem(A, B, mulctFactor, mulctDegree);
	return problem;
}

void init() {
	Scanner *scanner = new ConsoleScanner();
	Log *log = new FileLog("log.txt");
	TaskManager *taskManager = new WindowsTaskManager();
	ProcessManager *processManager = new WindowsProcessManager();

	Scanner::setSharedScanner(scanner);
	Log::setSharedLog(log);
	TaskManager::setSharedManager(taskManager);
	ProcessManager::setSharedManager(processManager);

	RandomGenerator *randomGenerator = new WindowsRandomGenerator();
	RandomGenerator::setSharedGenerator(randomGenerator);
}

void dispose() {
	delete Scanner::getSharedScanner();
	delete Log::getSharedLog();
	delete ProcessManager::getSharedManager();
	delete RandomGenerator::getSharedGenerator();
	delete TaskManager::getSharedManager();
}

double result(NTStandartMathProblem *problem, Math::Vector<double> *v) {
	int size = v->size();
	double *x = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*v)[i];
	}
	double r = problem->targetFunction(size, x);
	delete[] x;
	return r;
}

void printResult(PAA::PenaltyOptimisationProblem *problem, Math::Vector<double> *v) {
	int size = v->size();
	double *x = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*v)[i];
	}
	double r = problem->targetFunction(size, x);
	double uAu = problem->calculate_uAu(size, x);
	std::vector<double> *uBiu = problem->calculate_uBu(size, x);
	Log *_ = Log::getSharedLog();
	_->print(uAu); _->print("\t");
	for (int i = 0; i < size/2; i++) {
		_->print((*uBiu)[i]); _->print("\t");
	}
	for (int i = 0; i < size / 2; i++) {
		_->print((*v)[i]); _->print("\t"); _->print((*v)[i + size / 2]); _->print("\t");
	}
	_->print("\n");
	delete[] x;

}

void printMatrix(Math::Matrix<double> *matrix) {
	Log *_ = Log::getSharedLog();
	for (int i = 0; i < matrix->height(); i++) {
		for (int j = 0; j < matrix->width(); j++) {
			_->print((*matrix)[i][j]); _->print("\t");
		}
		_->print("\n");
	}
}

void printMatrices(std::vector<Math::Matrix<double> *> *matrices) {
	Log *_ = Log::getSharedLog();
	for (int i = 0; i < matrices->size(); i++) {
		printMatrix((*matrices)[i]);
		_->print("\n");
	}
}


void  printStatement(PAA::ProblemStatement *statement) {
	std::cout << "\n\n\n\A:\n";
	printMatrix(statement->getA());
	std::cout << "\n\n\n\B:\n";
	printMatrices(statement->getB());
	std::cout << "\n";
}

Math::Vector<double> *initialPoint(NTStandartMathProblem *problem) {
	int size = problem->size;
	Math::Vector<double> *result = new Math::Vector<double>(size);
	for (int i = 0; i < size; i++) {
		result[i] = rand() % 20 - 10;
	}
	return result;
}

int main()
{

	init();

	for (int theta = 0; theta <= 90; theta += 5) {

		Log::getSharedLog()->print("\n\n theta = ");
		Log::getSharedLog()->print(theta);
		Log::getSharedLog()->print("\n\n");

		for (int phi = 0; phi < 360; phi += 5) {
			Log::getSharedLog()->print("\n\n phi = ");
			Log::getSharedLog()->print(phi);
			Log::getSharedLog()->print("\n\n");

			PAA::ProblemStatement *statement = getNecStatement(theta, phi);
			//PAA::ProblemStatement *statement = getFileStatement();

			PAA::PenaltyOptimisationProblem *problem = getPenaltyProblem(statement);
			Math::Vector<double> *x = initialPoint(problem);
			//NTGradientAlgorithm algorithm;
			NTHGAlgorithm algorithm(x);
			//NTConjugateGradient algorithm;

			x = algorithm.solve(problem);

			printResult(problem, x);

			delete problem;
			delete statement;
		}

	}


	dispose();

}