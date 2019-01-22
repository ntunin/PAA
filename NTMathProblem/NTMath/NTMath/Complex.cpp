#include "stdafx.h"
#include "Complex.h"
#include <math.h>

using namespace Math;

Complex::Complex() {
	this->_re = 0;
	this->_im = 0;
}

Complex::Complex(double re, double im) {
	this->_re = re;
	this->_im = im;
}

Complex::Complex(double re) {
	this->_re = re;
	this->_im = 0;
}

Complex Complex::operator+(const Complex a) {
	return *(new Complex(this->_re + a._re, this->_im + a._im));
}

Complex Complex::operator-(const Complex a) {
	return Complex(this->_re - a._re, this->_im - a._im);
}

Complex Complex::operator-() {
	return Complex(-this->_re, -this->_im);
}

Complex Complex::operator*(const double a) {
	Complex *c = new Complex(this->_re * a, this->_im * a);
	return *c;
}

Complex Complex::operator*(const Complex a) {
	return Complex(this->_re * a._re - this->_im * a._im, this->_re * a._im + this->_im* a._re);
}

Complex Complex::operator/(const double a) {
	return Complex(this->_re / a, this->_im / a);
}

Complex Complex::operator/(const Complex a) {
	return Complex((this->_re * a._re + this->_im * a._im) / (a._re * a._re + a._im * a._im),
		(a._re * this->_im - this->_re * a._im) / (a._re * a._re + a._im * a._im));
}

Complex Complex::conj() {
	return Complex(this->_re, -this->_im);
}

double Complex::abs() {
	return sqrt(this->_re * this->_re + this->_im * this->_im);
}

double Complex::arg() {
	return atan(this->_im / this->_re);
}

double Complex::cosArg() {
	return this->_re / sqrt(this->_re * this->_re + this->_im * this->_im);
}

double Complex::sinArg() {
	return this->_im / sqrt(this->_re * this->_re + this->_im * this->_im);
}

double Complex::tgArg() {
	return this->_im / this->_re;
}

double Complex::Re() {
	return this->_re;
}

double Complex::Im() {
	return this->_im;
}

Complex Complex::operator+=(const Complex c) {
	this->_re += c._re;
	this->_im += c._im;
	return *this;
}


Complex Complex::inverse() {
	double d = this->_im * this->_im + this->_re *this->_re;
	return Complex(this->_re / d, this->_im / d);
}


void Complex::copy(Complex &c) {
	this->_re = c._re;
	this->_im = c._im;
}


Complex::~Complex() {
}
