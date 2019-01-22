#pragma once
#ifdef NTMATH_EXPORTS  
#define NTMATH_API __declspec(dllexport)   
#else  
#define NTMATH_API __declspec(dllimport)   
#endif 

namespace Math {
	template <class T>
	class Vector
	{
	protected:
		int _size;
		T *_values;
	public:
		Vector();
		Vector(int size);
		Vector(Vector &v);
		Vector(int size, T *values);
		~Vector();
		int size();
		T abs();
		Vector<T> &normalize();
		Vector<T> &operator -();
		Vector<T> &operator -(Vector<T> &);
		T& operator[](int i);
	};

	template <class T> Vector<T>::Vector()
	{
		_size = 1;
		_values = new T[1];
	}

	template <class T> Vector<T>::Vector(int size)
	{
		_size = size;
		_values = new T[size];
	}

	template <class T> Vector<T>::Vector(Vector &v)
	{
		_size = v._size;
		_values = new T[_size];
		for (int i = 0; i < _size; i++) {
			_values[i] = v._values[i];
		}
	}

	template <class T> Vector<T>::~Vector()
	{
		delete[] _values;
	}

	template <class T> Vector<T>::Vector(int size, T *values) {
		_size = size;
		_values = new T[size];
		for (int i = 0; i < size; i++) {
			_values[i] = values[i];
		}
	}

	template <class T> int Vector<T>::size() {
		return _size;
	}

	template <class T> T& Vector<T>::operator[](int i) {
		return _values[i];
	}

	template<class T> T Vector<T>::abs() {
		double result = 0;
		for (int i = 0; i < _size; i++) {
			result += pow(_values[i], 2);
		}
		return sqrt(result);
	}

	template<class T> Vector<T> &Vector<T>::normalize() {
		T length = abs();
		for (int i = 0; i < _size; i++) {
			_values[i] /= length;
		}
		return *this;
	}


	template<class T> Vector<T> &Vector<T>::operator -() {
		Vector<T> &result(*this);
		for (int i = 0; i < _size; i++) {
			result._values[i] = -_values[i];
		}
		return result;
	}

	template<class T> Vector<T> &Vector<T>::operator -(Vector<T> &v) {
		Vector<T> &result(*this);
		for (int i = 0; i < _size; i++) {
			result._values[i] = _values[i] - v._values[i];
		}
		return result;
	}

}


