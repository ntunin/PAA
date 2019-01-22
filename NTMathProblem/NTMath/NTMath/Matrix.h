#pragma once
#include "Vector.h"
#include "VectorT.h"
#include <math.h>

#ifdef NTMATH_EXPORTS  
#define NTMATH_API __declspec(dllexport)   
#else  
#define NTMATH_API __declspec(dllimport)   
#endif 

namespace Math {
	template <class T>
	class Matrix
	{
	private:
		int _width;
		int _height;
		T **_values;
	public:
		Matrix(int width);
		Matrix(int width, int height);
		Matrix(int width, T* values);
		Matrix(int width, int height, T* values);
		Matrix(int width, T** values);
		Matrix(int width, int height, T** values);
		Matrix(Matrix<T> &m);
		//NTMATH_API ComplexMatrix& inverse();
		Matrix<T> operator-(Matrix<T> &m);
		Matrix<T> &operator+(Matrix<T> &m);
		Matrix<T> &operator*(Matrix<T> &m);
		Matrix<T> operator*(Vector<T> &v);
		Matrix<T> operator*(T &c);
		T* operator[](int i);
		int width();
		int height();
		T **toArray();
		~Matrix();

	};

	template <class T> Matrix<T>::Matrix(int width)
	{
		_width = width;
		_height = width;
		_values = new T*[width];
		for (int i = 0; i < width; i++) {
			_values[i] = new T[width];
		}
	}

	template <class T> Matrix<T>::Matrix(int width, int height)
	{
		_width = width;
		_height = height;
		_values = new T*[height];
		for (int i = 0; i < height; i++) {
			_values[i] = new T[width];
		}
	}

	template <class T> Matrix<T>::Matrix(int width, T* values)
	{
		_width = width;
		_height = width;
		_values = new T*[width];
		int counter = 0;
		for (int i = 0; i < width; i++) {
			_values[i] = new T[width];
			for (int j = 0; j < _width; j++) {
				_values[i][j] = values[counter++];
			}
		}
	}

	template <class T> Matrix<T>::Matrix(int width, int height, T* values)
	{
		_width = width;
		_height = height;
		_values = new T*[height];
		int counter = 0;
		for (int i = 0; i < height; i++) {
			_values[i] = new T[width];
			for (int j = 0; j < _width; j++) {
				_values[i][j] = values[counter++];
			}
		}
	}

	template <class T> Matrix<T>::Matrix(int width, T** values)
	{
		_width = width;
		_height = width;
		_values = new T*[width];
		for (int i = 0; i < width; i++) {
			_values[i] = new T[width];
			for (int j = 0; j < _width; j++) {
				_values[i][j] = values[i][j];
			}
		}
	}

	template <class T> Matrix<T>::Matrix(int width, int height, T** values)
	{
		_width = width;
		_height = height;
		_values = new T*[height];
		for (int i = 0; i < height; i++) {
			_values[i] = new T[width];
			for (int j = 0; j < _width; j++) {
				_values[i][j] = values[i][j];
			}
		}
	}

	template <class T> Matrix<T>::Matrix(Matrix<T> &m) {
		this->_width = m._width;
		this->_height = m._height;
		this->_values = new T*[_height];
		for (int i = 0; i < _height; i++) {
			_values[i] = new T[_width];
			for (int j = 0; j < _width; j++) {
				_values[i][j] = m._values[i][j];
			}
		}
	}

	//NTMATH_API ComplexMatrix& inverse();
	template <class T> Matrix<T> Matrix<T>::operator-(Matrix<T> &m) {
		int height = (int)fmin(_height, m.height());
		int widthh = (int)fmin(_width, m.width());
		Matrix<T> r = Matrix<T>(height, width);
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				m[j][i] = _values[j][i] - m[j][i];
			}
		}
		return r;

	}

	template <class T> Matrix<T> &Matrix<T>::operator+(Matrix<T> &m) {
		int height = (int)fmin(_height, m.height());
		int width = (int)fmin(_width, m.width());
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				this->_values[j][i] = _values[j][i] + m[j][i];
			}
		}
		return *this;
	}

	template <class T> Matrix<T> &Matrix<T>::operator*(Matrix<T> &m) {
		int height = (int)fmin(_height, m.height());
		int width = (int)fmin(_width, m.width());
		int minSize = min(height, width);
		Matrix<T> result(width, height);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				T c = (T)0;
				for (int k = 0; k < minSize; k++) {
					c += _values[i][k] * m[k][j];
				}
				result._values[i][j] = c;
			}
		}
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				this->_values[i][j] = result[i][j];
			}
		}
		return *this;
	}

	template <class T> Matrix<T> Matrix<T>::operator*(Vector<T> &v) {
		int height = (int)fmin(_height, v.length());
		int width = (int)fmin(_width, v.length());
		Vector<T> r = Vector<T>(height);
		for (int j = 0; j < height; j++) {
			T a = (T)0;
			for (int i = 0; i < width; i++) {
				a += this->_values[j][i] * v[i];
			}
			r[j] = a;
		}
		return r;
	}

	template <class T> Matrix<T> Matrix<T>::operator*(T &c) {
		Matrix<T> r = Matrix<T>(_width, _height);
		for (int j = 0; j < _height; j++) {
			for (int i = 0; i < _width; i++) {
				r[j][i] = _values[j][i] * c;
			}
		}
		return r;
	}

	template <class T> T* Matrix<T>::operator[](int i) {
		return _values[i];
	}

	template <class T> int Matrix<T>::width() {
		return _width;
	}

	template <class T> int Matrix<T>::height() {
		return _height;
	}

	template <class T> Matrix<T>::~Matrix()
	{
		for (int i = 0; i < _height; i++) {
			delete[] _values[i];
		}
		delete[] _values;
	}


	template <class T>  T **Matrix<T>::toArray() {
		return _values;
	}
}

