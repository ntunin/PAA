#include "stdafx.h"
#include "FileStreamHandler.h"


FileStreamHandler::FileStreamHandler()
{
}


FileStreamHandler::~FileStreamHandler()
{
}

bool FileStreamHandler::checkString(std::string str) {
	if (str[0] != ' ') {
		return false;
	}
	if (str.find("- -") == std::string::npos) {
		return false;
	}
	return ((KeywordsHandler *)this)->checkString(str);
}
