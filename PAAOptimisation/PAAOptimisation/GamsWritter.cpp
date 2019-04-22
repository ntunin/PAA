#include "pch.h"
#include "GamsWritter.h"
#include "FileLog.h"

using namespace Math;


GamsWritter::GamsWritter()
{
}


GamsWritter::~GamsWritter()
{
}

std::string dbl2str(double d)
{
	size_t len = std::snprintf(0, 0, "%.10f", d);
	std::string s(len + 1, 0);
	// technically non-portable, see below
	std::snprintf(&s[0], len + 1, "%.10f", d);
	// remove nul terminator
	s.pop_back();
	// remove trailing zeros
	s.erase(s.find_last_not_of('0') + 1, std::string::npos);
	// remove trailing point
	if (s.back() == '.') {
		s.pop_back();
	}
	return s;
}

void GamsWritter::write(std::string fileName, PAA::ProblemStatement *statement) {
	FileLog l(fileName);
	Matrix<double> *A = statement->getA();
	std::vector<Matrix<double> *> *B = statement->getB();
	int size = A->width();
	int count = B->size();
	l.print("set i /1 * "); l.print(size); l.print("/;\n");
	l.print("set k /1 * "); l.print(count); l.print("/;\n\n\n"); 
	l.print("alias(i, j);\n\n\n");
	l.print("parameters\n");
	l.print("     A(i, j) bandwidth,\n");
	l.print("     B(k, i, j) bandwidth;\n\n\n");

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::string str = dbl2str((*A)[i][j]);
			l.print("A('"); l.print(i+1); l.print("', '"); l.print(j+1); l.print("') = "); l.print(str); l.print(";\n");
		}
	} 
	l.print("\n\n\n");
	for (int k = 0; k < count; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Matrix<double> *b = (*B)[k];
				std::string str = dbl2str((*b)[i][j]);
				l.print("B('"); l.print(k+1); l.print("', '"); l.print(i+1); l.print("', '"); l.print(j+1); l.print("') = "); l.print(str); l.print(";\n");
			}
		}
		l.print("\n\n");
	}
	l.print("\n\n\n");
}