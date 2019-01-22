#include "stdafx.h"
#include "StringHandler.h"

using namespace std;

StringHandler::StringHandler()
{
}


StringHandler::~StringHandler()
{
}

bool StringHandler::checkString(string str) {
	string substr = str.substr(0, 2);
	string keywords = this->getKeywords();
	return substr == keywords;
}
