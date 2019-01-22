#include "stdafx.h"
#include "Utils.h"
#include <math.h>


using namespace Math;

Utils::Utils()
{
}


void Utils::push(double **stack, double *newVector, int stackSize, int vectorSize) {
	for (int i = 0; i < stackSize - 1; i++) {
		for (int j = 0; j < vectorSize; j++) {
			stack[i][j] = stack[i + 1][j];
		}
	}
	for (int j = 0; j < vectorSize; j++) {
		stack[stackSize - 1][j] = newVector[j];
	}
}

void Utils::push(Vector<double> **stack, Vector<double> &newVector, int stackSize) {
	int vectorSize = newVector.size();
	for (int i = 0; i < stackSize - 1; i++) {
		for (int j = 0; j < vectorSize; j++) {
			(*stack[i])[j] = (*stack[i + 1])[j];
		}
	}
	for (int j = 0; j < vectorSize; j++) {
		(*stack[stackSize - 1])[j] = newVector[j];
	}
}

void Utils::inverse(int size, double **matrix, double **result) {
	double **augmentedmatrix = new double*[size];
	for (int i = 0; i < size; i++) {
		augmentedmatrix[i] = new double[2 * size];
		for (int j = 0; j < size; j++) {
			if (i == j) {
				augmentedmatrix[i][j + size] = 1;
			}
			else {
				augmentedmatrix[i][j + size] = 0;
			}
			augmentedmatrix[i][j] = matrix[i][j];
		}
	}

	for (int j = 0; j < size; j++) {
		int tmp = j;
		for (int i = j + 1; i < size; i++) {
			if (fabs(augmentedmatrix[i][j]) > fabs(augmentedmatrix[tmp][j])) {
				tmp = i;
			}
		}
		if (tmp != j) {
			for (int k = 0; k < 2 * size; k++) {
				double buf = augmentedmatrix[j][k];
				augmentedmatrix[j][k] = augmentedmatrix[tmp][k];
				augmentedmatrix[tmp][k] = buf;
			}
		}


		for (int i = 0; i < size; i++) {
			if (i != j)
			{
				double r = augmentedmatrix[i][j];
				for (int k = 0; k < 2 * size; k++) {
					augmentedmatrix[i][k] -= (augmentedmatrix[j][k] / augmentedmatrix[j][j])*r;
				}
			}
			else {
				double r = augmentedmatrix[i][j];
				for (int k = 0; k < 2 * size; k++) {
					augmentedmatrix[i][k] /= r;
				}
			}
		}



	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result[i][j] = augmentedmatrix[i][j + size];
		}
	}

	for (int i = 0; i < size; i++) {
		delete[] augmentedmatrix[i];
	}

	delete[] augmentedmatrix;

}


void Utils::transpose(int size, double **matrix, double **result) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result[j][i] = matrix[i][j];
		}
	}
}

void Utils::transpose(Matrix<double> &matrix, Matrix<double> &result) {
	int size = matrix.height();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result[j][i] = matrix[i][j];
		}
	}
}


void Utils::summ(int size, double **matrix1, double **matrix2, double **result) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
}


void Utils::summ(Matrix<double> &matrix1, Matrix<double> &matrix2, Matrix<double> &result) {
	int size = matrix1.height();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
}

void Utils::summ(Matrix<Complex> &matrix1, Matrix<Complex> &matrix2, Matrix<Complex> &result) {
	int size = matrix1.height();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			result[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
}


void Utils::mul(int size, double **matrix, double *vector, double *result) {
	for (int i = 0; i < size; i++) {
		double s = 0;
		for (int j = 0; j < size; j++) {
			s += matrix[i][j] * vector[j];
		}
		result[i] = s;
	}
}

void Utils::mul(Matrix<double> &matrix, Vector<double> &vector, Vector<double> &result) {
	int size = matrix.height();
	for (int i = 0; i < size; i++) {
		double s = 0;
		for (int j = 0; j < size; j++) {
			s += matrix[i][j] * vector[j];
		}
		result[i] = s;
	}
}
void Utils::gradient(int size, double **matrix, double *vector, double *result) {
	double **matrixT = new double*[size];
	double **mTplusM = new double*[size];
	for (int i = 0; i < size; i++) {
		matrixT[i] = new double[size];
		mTplusM[i] = new double[size];
	}
	transpose(size, matrix, matrixT);
	summ(size, matrixT, matrix, mTplusM);
	mul(size, mTplusM, vector, result);
	for (int i = 0; i < size; i++) {
		delete[] matrixT[i];
		delete[] mTplusM[i];
	}
	delete[] matrixT;
	delete[] mTplusM;
}


void Utils::gradient(Matrix<double> &matrix, Vector<double> &vector, Vector<double> &result) {
	int size = result.size();
	Matrix<double> matrixT(size);
	Matrix<double> mTplusM(size);
	Utils::transpose(matrix, matrixT);
	Utils::summ(matrixT, matrix, mTplusM);
	Utils::mul(mTplusM, vector, result);
}

void Utils::fill(int size, double value, double *result) {
	for (int i = 0; i < size; i++) {
		result[i] = value;
	}
}

void Utils::fill(double value, Math::Vector<double> &v) {
	int size = v.size();
	for (int i = 0; i < size; i++) {
		v[i] = value;
	}
}

void Utils::mul(int size, double *vector, double value, double *result) {
	for (int i = 0; i < size; i++) {
		result[i] = vector[i] * value;
	}
}

void Utils::mul(Vector<double> &vector, double value, Vector<double> &result) {
	int size = vector.size();
	for (int i = 0; i < size; i++) {
		result[i] = vector[i] * value;
	}
}


void Utils::mul(Matrix<Complex> &matrix1, Matrix<Complex> &matrix2, Matrix<Complex> &result) {
	int height = (int)fmin(matrix1.height(), matrix2.height());
	int width = (int)fmin(matrix1.width(), matrix2.width());
	int minSize = min(height, width);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Complex c(0);
			for (int k = 0; k < minSize; k++) {
				c += matrix1[i][k] * matrix2[k][j];
			}
			result[i][j] = c;
		}
	}
}

void Utils::summ(int size, double *vector1, double *vector2, double *result) {
	for (int i = 0; i < size; i++) {
		result[i] = vector1[i] + vector2[i];
	}
}


void Utils::summ(Vector<double> &vector1, Vector<double> &vector2, Vector<double> &result) {
	int size = vector1.size();
	for (int i = 0; i < size; i++) {
		result[i] = vector1[i] + vector2[i];
	}
}

void Utils::normalize(Vector<Complex> *cv, double *result) {
	Vector<Complex> v = *cv;
	int size = v.size();
	double rPhi = v[0].arg();
	for (int i = 0; i < size; i++) {
		result[2 * i] = v[i].abs();
		result[2 * i + 1] = v[i].arg() - rPhi;
	}

}

bool Utils::equals(double *array1, double *array2, int size, double epsilon) {
	for (int k = 0; k < size; k++) {
		if (fabs(array1[k] - array2[k]) > epsilon) {
			return false;
		}
	}
	return true;
}

Utils::~Utils()
{
}

Matrix<double> *Utils::convert(Matrix<Complex> *m) {
	int height = m->height();
	int width = m->width();
	int _height = m->height() * 2;
	int _width = m->width() * 2;
	Matrix<double> *_A = new Matrix<double>(_width, _height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			double re = (*m)[i][j].Re();
			double im = (*m)[i][j].Im();
			(*_A)[i + height][j + width] = (*_A)[i][j] = re;
			(*_A)[i + height][j] = im;
			(*_A)[i][j + width] = -im;
		}
	}
	return _A;
}

Matrix<double> *Utils::convert(Matrix<Complex> &m) {
	return convert(&m);
}
double *Utils::expand(Vector<Complex> *v) {
	int size = v->size();
	int _size = 2 * size;
	double *_v = new double[_size];
	for (int i = 0; i < size; i++) {
		_v[i] = (*v)[i].Re();
		_v[i + size] = (*v)[i].Im();
	}
	return _v;

}


Matrix<Complex> *Utils::econj(Matrix<Complex> *m) {
	int width = m->width();
	int height = m->height();
	Matrix<Complex> *result = new Matrix<Complex>(height, width);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			(*result)[j][i] = (*m)[i][j].conj();
		}
	}
	return result;
}

double Utils::abs(int size, double *v) {
	double s = 0;
	for (int i = 0; i < size; i++) {
		s += v[i]*v[i];
	}
	return sqrt(s);
}


void Utils::normalize(int size, double *v) {
	double length = Utils::abs(size, v);
	for (int i = 0; i < size; i++) {
		v[i] /= length;
	}
}