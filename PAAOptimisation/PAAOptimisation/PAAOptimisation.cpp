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
#include "DefaultRandomGenerator.h"
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
#include "NTCGSAAlgorithm.h"
#include "NTGSAAlgorithm.h"
#include "WindowsUtils.h"
#include "SAAlgorithm.h"
#include "GamsWritter.h"
#include <string>
#include "AllSourceNecInWritter.h"
#include <sstream>

void printMatrix(Math::Matrix<double> *matrix);

std::string filename;
std::string outfilename;
bool useCache = true;
int Pi = 1;

Math::Vector<double> *findBest(std::vector<Math::Vector<double> *> *solutions, PAA::PenaltyOptimisationProblem *problem);

PAA::ProblemStatement *getNecStatement(int theta, int phi) {	
	//Log::getSharedLog()->print("Enter NEC file name: > ");
	//std::string filename = "2x2WWE.nec";// Scanner::getSharedScanner()->readString();
	//Log::getSharedLog()->print("Use cached results if exist? > ");
	//bool useCache = true;//Scanner::getSharedScanner()->readBool();
	PAA::PhysicalSystem *system = PAA::NECPhysicalSystemBuilder(filename).buildSystem(useCache);
	//Log::getSharedLog()->print("Enter theta: > ");
	//int theta = 70;// Scanner::getSharedScanner()->readDouble();
	//Log::getSharedLog()->print("Enter phi: > ");
	//int phi = 45;// Scanner::getSharedScanner()->readDouble();
	std::vector<double> constraints;
	int sourceCount = system->getSourceCount();
	////Log::getSharedLog()->print("Please enter restrictions:\n");
	for (int i = 0; i < sourceCount; i++) {
		Log::getSharedLog()->print(" "); 
		//Log::getSharedLog()->print(i); 
		//Log::getSharedLog()->print(": > ");
		double value = Pi;// Scanner::getSharedScanner()->readDouble()
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

	RandomGenerator *randomGenerator = new DefaultRandomGenerator();
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
	_->print("iAi:\t"); _->print(uAu); _->print("\t"); 
	_->print("iBi:\t");
	for (int i = 0; i < size/2; i++) {
		_->print((*uBiu)[i]); _->print("\t");
	}
	_->print("\ni:\n");
	for (int i = 0; i < size / 2; i++) {
		_->print((*v)[i]); _->print("\t"); _->print((*v)[i + size / 2]); _->print("\t");
	}
	_->print("\n");
	delete[] x;

}

void printResultTable(PAA::PenaltyOptimisationProblem *problem, Math::Vector<double> *v) {
	int size = v->size();
	double *x = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*v)[i];
	}
	double r = problem->targetFunction(size, x);
	double uAu = problem->calculate_uAu(size, x);
	std::vector<double> *uBiu = problem->calculate_uBu(size, x);
	Log *_ = Log::getSharedLog();
	_->print("iAi:\t"); _->print(uAu); _->print("\t");
	_->print("iBi:\t");
	for (int i = 0; i < size / 2; i++) {
		_->print((*uBiu)[i]); _->print("\t");
	}
	_->print("\ni:\n");
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
			_->print((*matrix)[i][j]); _->print("\t\t");
			if (j == matrix->width() / 2) {
				_->print("|");
			}
		}
		_->print("\n");
		if (i == matrix->height() / 2) {
			_->print("_");
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
	RandomGenerator *r = RandomGenerator::getSharedGenerator();
	int size = problem->size;
	Math::Vector<double> *result = new Math::Vector<double>(size);
	int radius = 5000;
	for (int i = 0; i < size; i++) {
		int value = r->next() % (2*radius) - radius;
		(*result)[i] = value;
	}
	return result;
}

Math::Vector<Math::Complex> *toComplex(Math::Vector<double> *vector) {
	int size = vector->size() / 2;
	Math::Vector<Math::Complex> *result = new Math::Vector<Math::Complex>(size);
	for (int i = 0; i < size; i++) {
		double re = (*vector)[i];
		double im = (*vector)[i + size];
		Math::Complex c(re, im);
		(*result)[i] = c;
	}
	return result;
}

void directivityInvestigation(int theta, int phi) {
	PAA::ProblemStatement *statement = getNecStatement(theta, phi);
	//PAA::ProblemStatement *statement = getFileStatement();

	PAA::PenaltyOptimisationProblem *problem = getPenaltyProblem(statement);
	delete statement;
	Math::Vector<double> *x0 = initialPoint(problem);
	NTGradientAlgorithm algorithm(x0);
	NTGradientAlgorithm::time = 0;
	NTGradientAlgorithm::maxTime = 10000;

	//NTCGSAAlgorithm algorithm(x0, 100, 0.05, 4);
	//SAAlgorithm algorithm(x0, 100, 0.001, 4);
	//NTGSAAlgorithm algorithm(x0, 100, 0.001, 4);
	//NTGradientAlgorithm algorithm(x0);
	//NTHGAlgorithm algorithm(x);
	//NTConjugateGradientAlgorithm algorithm(x0);

	std::uint64_t start = WindowsUtils::time();
	Math::Vector<double> *x = algorithm.solve(problem);
	std::uint64_t end = WindowsUtils::time();
	std::uint64_t workingTime = end - start;

	printResult(problem, x);
	Log::getSharedLog()->print("\ntime = ");
	Log::getSharedLog()->print(workingTime);
	Log::getSharedLog()->print("\n\n");
	
	double *xs = new double[x->size()];
	for (int i = 0; i < x->size(); i++) {
		xs[i] = (*x)[i];
	}
	std::vector<double> *uBu = problem->calculate_uBu(x->size(), xs);
	double maxB = -1e6;
	for (int i = 0; i < uBu->size(); i++) {
		double b = (*uBu)[i];
		if (b > maxB) {
			maxB = b;
		}
	}
	double f = problem->targetFunction(x->size(), xs)/ maxB;
	Log::getSharedLog()->print("\n\n_________________________\n\nF = ");
	Log::getSharedLog()->print(f);
	Log::getSharedLog()->print("\n\n_________________________\n\n");


	PAA::NECPhysicalSystemBuilder builder(filename);
	Math::Vector<Math::Complex> *sources = toComplex(x);
	AllSourceNecInWritter(sources, builder.in, outfilename);
	delete sources;
}

void checkSolution(std::string in, std::string out, int theta, int phi, double* values) {
	filename = in;
	outfilename = out;
	PAA::ProblemStatement *statement = getNecStatement(theta, phi);
	//PAA::ProblemStatement *statement = getFileStatement();

	PAA::PenaltyOptimisationProblem *problem = getPenaltyProblem(statement);
	delete statement;
	Log::getSharedLog()->print(filename);
	Log::getSharedLog()->print("\n\n");
	Math::Vector<double> *x = new Math::Vector<double>(problem->size, values);
	std::uint64_t end = WindowsUtils::time();
	printResult(problem, x);

	std::vector<double> *uBu = problem->calculate_uBu(x->size(), values);
	double maxB = -1e6;
	for (int i = 0; i < uBu->size(); i++) {
		double b = (*uBu)[i];
		if (b > maxB) {
			maxB = b;
		}
	}
	double f = problem->targetFunction(x->size(), values) / maxB;
	Log::getSharedLog()->print("\n\n_________________________\n\nF = ");
	Log::getSharedLog()->print(f);
	Log::getSharedLog()->print("\n\n_________________________\n\n");


	PAA::NECPhysicalSystemBuilder builder(filename);
	Math::Vector<Math::Complex> *sources = toComplex(x);
	AllSourceNecInWritter(sources, builder.in, outfilename);
	delete sources;
}

double targetFunction(Math::Vector<double> *v, PAA::PenaltyOptimisationProblem *problem) {
	int size = v->size();
	double *x = new double[size];
	for (int i = 0; i < size; i++) {
		x[i] = (*v)[i];
	}

	std::vector<double> *uBu = problem->calculate_uBu(size, x);
	double maxB = -1e6;
	for (int i = 0; i < uBu->size(); i++) {
		double b = (*uBu)[i];
		if (b > maxB) {
			maxB = b;
		}
	}
	double f = problem->targetFunction(size, x) / maxB;
	delete[] x;
	return f;
}

std::vector<Math::Vector<double> *> *castPhases(std::vector<Math::Vector<double> *> *vectors) {
	std::vector<Math::Vector<double> *> *result = new std::vector<Math::Vector<double> *>;
	for (int i = 0; i < vectors->size(); i++) {
		Math::Vector<double> *v = (*vectors)[i];
		Math::Vector<double> *p = new Math::Vector<double>(v->size());
		int size = v->size() / 2;
		double phase = 0;
		for (int i = 0; i < size; i++) {
			double re = (*v)[i];
			double im = (*v)[i + size];
			double abs = sqrt(re*re + im * im);
			double arg = atan(im / re);
			if (i == 0) {
				phase = arg;
			}
			(*p)[2 * i] = abs;
			(*p)[2 * i + 1] = arg - phase;
		}
		result->push_back(p);
	}
	return result;
}

bool areEquals(Math::Vector<double> *a, Math::Vector<double> *b) {
	for (int i = 0; i < a->size(); i++) {
		if (abs((*a)[i] - (*b)[i]) > 1e-2) {
			return false;
		}
	}
	return true;
}

std::vector<Math::Vector<double> *> *getUnequvalent(std::vector<Math::Vector<double> *> *vectors) {
	std::vector<Math::Vector<double> *> *unequivalent = new std::vector<Math::Vector<double> *>;
	for (int i = 0; i < vectors->size(); i++) {
		Math::Vector<double> *v = (*vectors)[i];
		bool eq = false;
		for (int j = 0; j < unequivalent->size(); j++) {
			Math::Vector<double> *u = (*unequivalent)[j];
			if (areEquals(v, u)) {
				eq = true;
				break;
			}
		}
		if (!eq) {
			unequivalent->push_back(v);
		}
	}
	return unequivalent;
}

void printPhased(std::vector<Math::Vector<double> *> *phased, Log *l) {
	for (int i = 0; i < phased->size(); i++) {
		Math::Vector<double> *v = (*phased)[i];
		l->print("\t");
		int size = v->size() / 2;
		for (int i = 0; i < size; i++) {
			l->print("\t");
			l->print((*v)[2 * i]);
			l->print("\t");
			l->print((*v)[2 * i + 1]);
		}
		l->print("\n");
	}
}

void collectDirectivityInvestigation(int theta, int phi) {
	PAA::ProblemStatement *statement = getNecStatement(theta, phi);
	//PAA::ProblemStatement *statement = getFileStatement();

	PAA::PenaltyOptimisationProblem *problem = getPenaltyProblem(statement);
	delete statement;
	NTGradientAlgorithm::time = 0;
	NTGradientAlgorithm::maxTime = 1000000;
	std::vector<Math::Vector<double> *> *solutions = new std::vector<Math::Vector<double> *>;
	while (NTGradientAlgorithm::time < NTGradientAlgorithm::maxTime) {
		Math::Vector<double> *x0 = initialPoint(problem);
		NTGradientAlgorithm algorithm(x0);
		Math::Vector<double> *x = algorithm.solve(problem);
		solutions->push_back(x);
	}

	Log *l = Log::getSharedLog();
	l->print("PAA optimisation finish\n");
	l->print(filename); l->print("\n");
	l->print("Gradient\n");
	l->print("\n_____________________\n\n");
	l->print("Founded: "); l->print(solutions->size()); l->print(" solutions: \n");

	for (int i = 0; i < solutions->size(); i++) {
		Math::Vector<double> *v = (*solutions)[i];

		l->print("F = \t");
		l->print(targetFunction(v, problem));
		l->print("\t");
		for (int i = 0; i < v->size(); i++) {
			l->print("\t");
			l->print((*v)[i]);
		}
		l->print("\n");
	}
	l->print("\n\n");
	l->print("Time = "); l->print(NTGradientAlgorithm::time); l->print("\n\n");

	Math::Vector<double> *best = findBest(solutions, problem);

	l->print("The best: \t"); l->print(targetFunction(best, problem)); l->print("\t");

	for (int i = 0; i < best->size(); i++) {
		l->print("\t");
		l->print((*best)[i]);
	}
	l->print("\n\n");

	std::vector<Math::Vector<double> *> *phased = castPhases(solutions);

	l->print("\n\n\nCheck phases:\n");
	l->print("\n\n\nUnequvalent: "); 
	std::vector<Math::Vector<double> *> *uneq = getUnequvalent(phased);
	l->print(uneq->size());
	l->print("\n");
	printPhased(uneq, l);
	l->print("\n\n");
	l->print("All polar solutions:\n");
	printPhased(phased, l);
	l->print("\n\n");

	//printResult(problem, x);
	//Log::getSharedLog()->print("\ntime = ");
	//Log::getSharedLog()->print(workingTime);
	//Log::getSharedLog()->print("\n\n");


	PAA::NECPhysicalSystemBuilder builder(filename);
	Math::Vector<Math::Complex> *sources = toComplex(best);
	AllSourceNecInWritter(sources, builder.in, outfilename);
	delete sources;
}

Math::Vector<double> *findBest(std::vector<Math::Vector<double> *> *solutions, PAA::PenaltyOptimisationProblem *problem) {
	
	Math::Vector<double> *best = NULL;
	double bestF = 1e20;

	for (int i = 0; i < solutions->size(); i++) {
		Math::Vector<double> *v = (*solutions)[i];
		double f = targetFunction(v, problem);
		if (f < bestF) {
			bestF = f;
			best = v;
		}
	}

	return best;
}

void printGAMS(std::string fileName, int theta, int phi) {
	PAA::ProblemStatement *statement = getNecStatement(theta, phi);
	GamsWritter writter;
	writter.write(fileName, statement);
	delete statement;
}

void printMatrix(std::string fileName, std::string filename, int theta, int phi) {

	Log *l = new FileLog(fileName);
	PAA::PhysicalSystem *system = PAA::NECPhysicalSystemBuilder(filename).buildSystem(useCache);

	l->print("Y:\n\n");
	Math::Matrix<Math::Complex> *Y = system->getY();
	for (int i = 0; i < Y->height(); i++) {
		for (int j = 0; j < Y->width(); j++) {
			Math::Complex c = (*Y)[i][j];
			l->print(c.Re());
			l->print(" + ");
			l->print(c.Im());
			l->print("i\t");
		}
		l->print("\n");
	}
	l->print("\n\n\n");

	std::vector<double> constraints;
	int sourceCount = system->getSourceCount();
	for (int i = 0; i < sourceCount; i++) {
		double value = Pi;
		constraints.push_back(value);
	}
	PAA::ProblemStatement *statement = new PAA::PhysicalSystemDirectivityOptimisationProblemStatement(system, constraints, theta, phi);


	l->print("A:\n\n");
	Math::Matrix<double> *A = statement->getA();

	for (int i = 0; i < A->height(); i++) {
		for (int j = 0; j < A->width(); j++) {
			l->print((*A)[i][j]);
			l->print("\t");
		}
		l->print("\n");
	}
	l->print("\n\n\n");

	l->print("B:\n\n");
	std::vector<Math::Matrix<double> *> *B = statement->getB();


	Math::Matrix<double> *b = (*B)[0];

	Math::Matrix<double> *bSumm = new Math::Matrix<double>(b->width(), b->height());

	for (int i = 0; i < b->height(); i++) {
		for (int j = 0; j < b->width(); j++) {
			(*bSumm)[i][j] = 0;
		}
	}

	for (int k = 0; k < B->size(); k++) {
		Math::Matrix<double> *b = (*B)[k];
		l->print(k);
		l->print("\n\n");
		for (int i = 0; i < b->height(); i++) {
			for (int j = 0; j < b->width(); j++) {
				double value = (*b)[i][j];
				(*bSumm)[i][j] += value;
				l->print(value);
				l->print("\t");
			}
			l->print("\n");
		}
		l->print("\n\n");
	}

	l->print("\n\nBSumm:\n\n");

	for (int i = 0; i < b->height(); i++) {
		for (int j = 0; j < b->width(); j++) {
			double value = (*bSumm)[i][j];
			l->print(value);
			l->print("\t");
		}
		l->print("\n");
	}
	l->print("\n\n");

	delete l;
	delete statement;
}

void radialInvestigation() {
	for (int theta = 0; theta <= 90; theta += 5) {

		Log::getSharedLog()->print("\n\n theta = ");
		Log::getSharedLog()->print(theta);
		Log::getSharedLog()->print("\n\n");

		for (int phi = 0; phi < 360; phi += 5) {
			Log::getSharedLog()->print("\n\n phi = ");
			Log::getSharedLog()->print(phi);
			Log::getSharedLog()->print("\n\n");

			directivityInvestigation(theta, phi);
		}

	}
}

void generateTests() {


	Log *log = Log::getSharedLog();
	RandomGenerator *r = RandomGenerator::getSharedGenerator();

	log->print("\n\n   ========  test set  ======== \n\n");

	for (int i = 0; i < 100; i++) {
		log->print("test #"); log->print(i); log->print(";\n\n");
		int theta = (r->next() % 18) * 5;
		int phi = (r->next() % 18) * 5;
		log->print("theta: "); log->print(theta); log->print("; phi: "); log->print(phi); log->print("\n");
		PAA::ProblemStatement *statement = getNecStatement(theta, phi);
		PAA::PenaltyOptimisationProblem *problem = getPenaltyProblem(statement);

		for (int j = 0; j < 10; j++) {

			Math::Vector<double> *x = initialPoint(problem);
			NTGradientAlgorithm algorithm(x);
			//NTHGAlgorithm algorithm(x);
			//NTConjugateGradientAlgorithm algorithm(x);

			x = algorithm.solve(problem);

			printResult(problem, x);

		}
		delete problem;
		delete statement;


	}
}

std::string con(std::string first, std::string second) {
	std::stringstream s;
	s << first << second;
	return s.str();
}

void solveModel(std::string name, int teta, int phi) {
	Log *_l = Log::getSharedLog();
	Log *log = new FileLog(con(name, "_log.txt"));
	Log::setSharedLog(log);
	filename = con(name, ".nec");
	outfilename = con(name, "_result.nec"); 
	printGAMS(con(name, ".gms"), teta, phi);
	collectDirectivityInvestigation(teta, phi);
	Log::setSharedLog(_l);
	delete log;
}

int main()
{
	init();
	solveModel("29_03_19_3x3BVD", 70, 45);
	solveModel("05_04_19_2x2L5_20", 70, 45);
	solveModel("05_04_19_3x3L5_20", 70, 45);

	//solveModel("3x3WWD", 70, 45);

	//directivityInvestigation(70, 45);
	//generateTests();

	dispose();

}