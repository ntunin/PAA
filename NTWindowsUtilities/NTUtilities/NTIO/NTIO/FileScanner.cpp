#include "stdafx.h"
#include "FileScanner.h"
#include "Log.h"

using namespace std;

FileScanner::FileScanner(string path) {
	file = new ifstream();
	file->open(path, std::ifstream::in);
}


FileScanner::~FileScanner() {
	file->close();
}

int FileScanner::readInt(std::string message) {
	int result;
	Log::getSharedLog()->print(message);
	(*file) >> result;
	Log::getSharedLog()->print(result);
	Log::getSharedLog()->print("\n");
	return result;
}

int FileScanner::readInt() {
	int result;
	(*file) >> result;
	return result;
}

double FileScanner::readDouble(std::string message) {
	double result;
	Log::getSharedLog()->print(message);
	(*file) >> result;
	Log::getSharedLog()->print(result);
	Log::getSharedLog()->print("\n");
	return result;
}

double FileScanner::readDouble() {
	double result;
	(*file) >> result;
	return result;
}


string FileScanner::readString(std::string message) {
	string result;
	Log::getSharedLog()->print(message);
	(*file) >> result;
	Log::getSharedLog()->print(result);
	Log::getSharedLog()->print("\n");
	return result;
}

string FileScanner::readString() {
	string result;
	(*file) >> result;
	return result;
}


bool FileScanner::readBool() {
	std::string answer;
	(*file) >> answer;
	while (true) {
		switch (answer[0])	{
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			break;
		}
		(*file) >> answer;
	}
}

bool FileScanner::readBool(string message) {
	std::string answer;
	Log::getSharedLog()->print(message);
	Log::getSharedLog()->print(" (y / n): >");
	(*file) >> answer;
	Log::getSharedLog()->print(answer);
	Log::getSharedLog()->print("\n");
	while (true) {
		switch (answer[0]) {
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			break;
		}
		Log::getSharedLog()->print("Sorry, entered invalid case. Required 'y' or 'n': >");
		(*file) >> answer;
	}
}
