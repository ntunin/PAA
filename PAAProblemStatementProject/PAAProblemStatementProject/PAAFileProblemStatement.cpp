#include "stdafx.h"
#include "PAAFileProblemStatement.h"
#include <fstream>

using namespace PAA;

FileProblemStatement::FileProblemStatement(std::string filename)
{
	this->filename = filename;
	this->state = 0;
	readFile();
	parseMatrices();
}

void FileProblemStatement::parseMatrices() {
	A = parseMatrix(_A);
	B = new std::vector<Math::Matrix<double> *>;
	for (int i = 0; i < _B.size(); i++) {
		std::vector< std::vector<double> *> *_b = _B[i];
		Math::Matrix<double> *b = parseMatrix(_b);
		B->push_back(b);
		freeMatrix(_b);
	}
	freeMatrix(_A);
}

void FileProblemStatement::freeMatrix(std::vector< std::vector<double> * > *b) {
	for (int i = 0; i < b->size(); i++) {
		std::vector<double> *row = (*b)[i];
		delete row;
	}
	delete b;
}

Math::Matrix<double> *FileProblemStatement::parseMatrix(std::vector< std::vector<double> *> *_A) {
	int size = _A->size();
	Math::Matrix<double> *A = new Math::Matrix<double>(size);
	for (int i = 0; i < size; i++) {
		std::vector<double> *row = (*_A)[i];
		for (int j = 0; j < size; j++) {
			double value = (*row)[j];
			(*A)[i][j] = value;
		}
	}
	return A;
}

FileProblemStatement::~FileProblemStatement()
{
}

void FileProblemStatement::readFile() {
	std::ifstream file;
	std::string line;
	file.open(filename);
	_A = new std::vector< std::vector<double> * >;
	while (!file.eof()) {
		std::getline(file, line);
		switch (state)
		{
		case 0: {
			handleA(line);
			break;
		}
		case 1: {
			handleB(line);
			break;
		}
		default:
			break;
		}
	}
	file.close();
}


void FileProblemStatement::handleA(std::string line) {
	if (line == "") {
		state = 1;
	}
	else {
		std::vector<double> *row = parseLine(line);
		_A->push_back(row);
	}

}

void FileProblemStatement::handleB(std::string line) {
	if (line == "") {
		currentB = NULL;
	}
	else {
		if (!currentB) {
			currentB = new std::vector<std::vector<double> *>;
			_B.push_back(currentB);
		}
		std::vector<double> *row = parseLine(line);
		currentB->push_back(row);
	}

}

std::vector<double> *FileProblemStatement::parseLine(std::string line) {
	std::vector<double> *result = new std::vector<double>;
	while (line.length()) {
		int pos = line.find('\t');
		int offset = 1;
		if (pos == std::string::npos) {
			pos = line.length();
			offset = 0;
		}
		std::string strValue = line.substr(0, pos);
		std::string::iterator begin = line.begin();
		std::string::iterator end = line.begin();
		end += pos + offset;
		line.erase(begin, end);
		double value = std::stod(strValue);
		result->push_back(value);
	}
	return result;
}

Math::Matrix<double> *FileProblemStatement::getA() {
	return A;
}

std::vector<Math::Matrix<double> *> *FileProblemStatement::getB() {
	return B;
}