#pragma once
#include "PAAProblemStatement.h"
#include <string>
#include "NTMath.h"


#ifdef PAAPROBLEMSTATEMENTPROJECT_EXPORTS  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllexport)   
#else  
#define PAAPROBLEMSTATEMENTPROJECT_API __declspec(dllimport)   
#endif 

namespace PAA {
	class FileProblemStatement: public ProblemStatement
	{
	private:
		std::string filename;
		Math::Matrix<double> *A;
		std::vector< std::vector<double> * > *_A;
		std::vector<std::vector<std::vector<double> *> *> _B;
		std::vector<Math::Matrix<double> *> *B;
		int state;
		void readFile();
		void parseMatrices();
		void freeMatrix(std::vector< std::vector<double> * > *);
		Math::Matrix<double> *parseMatrix(std::vector< std::vector<double> * > *_A);
		void handleA(std::string line);
		void handleB(std::string line);
		std::vector<double> *parseLine(std::string line);
		std::vector<std::vector<double> *> *currentB;
	public:
		PAAPROBLEMSTATEMENTPROJECT_API Math::Matrix<double> *getA();
		PAAPROBLEMSTATEMENTPROJECT_API std::vector<Math::Matrix<double> *> *getB();
		PAAPROBLEMSTATEMENTPROJECT_API FileProblemStatement(std::string filename);
		PAAPROBLEMSTATEMENTPROJECT_API ~FileProblemStatement();
	};
}

