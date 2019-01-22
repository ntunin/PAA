#pragma once
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"
#ifdef NTMATH_EXPORTS  
#define NTMATH_API __declspec(dllexport)   
#else  
#define NTMATH_API __declspec(dllimport)   
#endif 

namespace Math {

	class Utils
	{
	public:
		NTMATH_API static void inverse(int size, double **matrix, double **result);
		NTMATH_API static void gradient(int size, double **matrix, double *vector, double *result);
		NTMATH_API static void gradient(Matrix<double> &matrix, Vector<double> &vector, Vector<double> &result);
		NTMATH_API static void transpose(int size, double **matrix, double **result);
		NTMATH_API static void transpose(Matrix<double> &matrix, Matrix<double> &result);
		NTMATH_API static void summ(int size, double **matrix1, double **matrix2, double **result);
		NTMATH_API static void summ(int size, double *vector1, double *vector2, double *result);
		NTMATH_API static void summ(Vector<double> &vector1, Vector<double> &vector2, Vector<double> &result);
		NTMATH_API static void summ(Matrix<double> &matrix1, Matrix<double> &matrix2, Matrix<double> &result);
		NTMATH_API static void summ(Matrix<Complex> &matrix1, Matrix<Complex> &matrix2, Matrix<Complex> &result);
		NTMATH_API static void mul(int size, double **matrix, double *vector, double *result);
		NTMATH_API static void mul(Matrix<double> &matrix, Vector<double> &vector, Vector<double> &result);
		NTMATH_API static void mul(Matrix<Complex> &matrix1, Matrix<Complex> &matrix2, Matrix<Complex> &result);
		NTMATH_API static void mul(int size, double *vector, double value, double *result);
		NTMATH_API static void mul(Vector<double> &vector, double value, Vector<double> &result);
		NTMATH_API static void fill(int size, double value, double *result);
		NTMATH_API static void fill(double value, Math::Vector<double> &v);
		NTMATH_API static void push(double **stack, double *newVector, int stackSize, int vectorSize);
		NTMATH_API static void push(Vector<double> **stack, Vector<double> &newVector, int stackSize);
		NTMATH_API static void normalize(Vector<Complex> *v, double *result);
		NTMATH_API static void normalize(int size, double *v);
		NTMATH_API static double abs(int size, double *);
		NTMATH_API static bool equals(double *array1, double *array2, int size, double epsilon);
		NTMATH_API static Matrix<double> *convert(Matrix<Complex> &m);
		NTMATH_API static Matrix<double> *convert(Matrix<Complex> *m);
		NTMATH_API static double *expand(Vector<Complex> *);
		NTMATH_API static Matrix<Complex> *econj(Matrix<Complex> *m);
		Utils();
		~Utils();
	};

}

