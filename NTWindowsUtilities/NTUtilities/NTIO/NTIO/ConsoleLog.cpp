#include "stdafx.h"
#include "ConsoleLog.h"
#include <mutex> 
#include <iostream>
#include <sstream>

using namespace std;

mutex consoleMtx;

ConsoleLog::ConsoleLog()
{
}

void ConsoleLog::print(double d) {
	unique_lock<mutex> lck(consoleMtx, defer_lock);
	lck.lock();
	std::cout << d;
	lck.unlock();
}


void ConsoleLog::print(double d, int size) {
	unique_lock<mutex> lck(consoleMtx, defer_lock);
	lck.lock();
	std::stringstream s;
	s << d;
	std::string str = s.str();
	if ((int)d == d && str.length() < size) {
		str.append(".");
	}
	for (int i = 0; i < size && i < str.length(); i++) {
		std::cout << str[i];
	}
	for (int i = str.length(); i < size; i++) {
		std::cout << "0";
	}
	lck.unlock();
}

void ConsoleLog::print(string &m) {
	unique_lock<mutex> lck(consoleMtx, defer_lock);
	lck.lock();
	std::cout << m;
	lck.unlock();
}

void ConsoleLog::print(const char *m) {
	unique_lock<mutex> lck(consoleMtx, defer_lock);
	lck.lock();
	std::cout << m;
	lck.unlock();
}

void ConsoleLog::print(double **m, int size) {
	unique_lock<mutex> lck(consoleMtx, defer_lock);
	lck.lock();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << m[i][j];
			if (j != size - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}
	lck.unlock();
}

void ConsoleLog::print(double *v, int size) {
	unique_lock<mutex> lck(consoleMtx, defer_lock);
	lck.lock();
	for (int i = 0; i < size; i++) {
		cout << v[i];
		if (i != size - 1) {
			cout << ", ";
		}
	}
	lck.unlock();
}

void ConsoleLog::reset() {
	system("cls");
}

ConsoleLog::~ConsoleLog()
{
}
