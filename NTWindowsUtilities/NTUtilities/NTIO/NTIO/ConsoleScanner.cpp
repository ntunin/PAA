#include "stdafx.h"
#include "ConsoleScanner.h"
#include <iostream>

using namespace std;

ConsoleScanner::ConsoleScanner()
{
}


ConsoleScanner::~ConsoleScanner()
{
}

int ConsoleScanner::readInt(std::string message) {
	int result;
	cout << message;
	cin >> result;
	return result;
}

int ConsoleScanner::readInt() {
	int result;
	cin >> result;
	return result;
}

double ConsoleScanner::readDouble(std::string message) {
	double result;
	cout << message;
	cin >> result;
	return result;
}

double ConsoleScanner::readDouble() {
	double result;
	cin >> result;
	return result;
}


string ConsoleScanner::readString(std::string message) {
	string result;
	cout << message;
	cin >> result;
	return result;
}

string ConsoleScanner::readString() {
	string result;
	cin >> result;
	return result;
}


bool ConsoleScanner::readBool() {
	std::string answer;
	cin >> answer;
	while (true) {
		switch (answer[0])	{
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			break;
		}
		cin >> answer;
	}
}

bool ConsoleScanner::readBool(string message) {
	std::string answer;
	cout << message << " (y / n): >";
	cin >> answer;
	while (true) {
		switch (answer[0]) {
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			break;
		}
		cout << "Sorry, entered invalid case. Required 'y' or 'n': >";
		cin >> answer;
	}
}
