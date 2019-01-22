#include "stdafx.h"
#include "KeywordsHandler.h"
#include <string>

using namespace std;

KeywordsHandler::KeywordsHandler()
{
}


KeywordsHandler::~KeywordsHandler()
{
}


void KeywordsHandler::setKeywords(const char *keywords) {
	this->keywords = keywords;
}

bool KeywordsHandler::checkString(string str) {
	return str.find(this->keywords) != string::npos;
}



void KeywordsHandler::skip(ifstream *file, int count) {
	string buffer;
	for (int i = 0; i < count; i++) {
		getline(*file, buffer);
	}
}

string KeywordsHandler::getKeywords() {
	return string(this->keywords);
}