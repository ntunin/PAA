#pragma once
#include "Vector.h"

#ifdef NTMATH_EXPORTS  
#define NTMATH_API __declspec(dllexport)   
#else  
#define NTMATH_API __declspec(dllimport)   
#endif 
namespace Math {

	template <class T>
	class Matrix;

	template <class T>
	class VectorT: public Vector<T>
	{
	public:
		VectorT(int size);
		VectorT(int size, T *values);
		~VectorT();
		VectorT<T> &operator*(Vector<T> &v);
		T &operator*(Matrix<T> &m);
	};

	template <class T> VectorT<T>::VectorT(int size) : Vector(size)
	{
	}
	template <class T> VectorT<T>::VectorT(int size, T *values) : Vector(size, values)
	{
	}
	template <class T> VectorT<T>::~VectorT()
	{
	}
	template <class T> T &VectorT<T>::operator*(Matrix<T> &m) {	
		int size = size();
		int height = (int)fmin(m.height(), size);
		int width = (int)fmin(m.width(), size);
		VectorT<T> r = VectorT<T>(size);
		for (int j = 0; j < height; j++) {
			T a = T(0);
			for (int i = 0; i < width; i++) {
				//a += (this*)[i] * m[i][j];
			}
			r[j] = a;
		}
		return r;
	}
	template <class T> VectorT<T> &VectorT<T>::operator*(Vector<T> &v) {
		int length = (int)fmin(this->size(), v.size());
		T a = (T)0;
		for (int i = 0; i < length; i++) {
			a += (*this)[i] * v[i];
		};
		return a;
	}
}


