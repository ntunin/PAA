#pragma once
#ifdef NTMATH_EXPORTS  
#define NTMATH_API __declspec(dllexport)   
#else  
#define NTMATH_API __declspec(dllimport)   
#endif 

namespace Math {
	class Complex {
	public:
		NTMATH_API Complex();
		NTMATH_API ~Complex();
		NTMATH_API Complex(double re);
		NTMATH_API Complex(double re, double im);
		NTMATH_API Complex operator+(const Complex);
		NTMATH_API Complex operator+=(const Complex);
		NTMATH_API Complex operator-(const Complex);
		NTMATH_API Complex operator-();
		NTMATH_API Complex operator*(const double);
		NTMATH_API Complex operator*(const Complex);
		NTMATH_API Complex operator/(const double);
		NTMATH_API Complex operator/(const Complex);
		NTMATH_API Complex conj();
		NTMATH_API Complex inverse();
		NTMATH_API double abs();
		NTMATH_API double tgArg();
		NTMATH_API double cosArg();
		NTMATH_API double sinArg();
		NTMATH_API double arg();
		NTMATH_API double Re();
		NTMATH_API double Im();
		NTMATH_API void copy(Complex &c);

	private:
		double _re;
		double _im;
	};
}


