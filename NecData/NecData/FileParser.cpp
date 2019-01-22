#include "stdafx.h"
#include "FileParser.h"
#include <sstream>
#include <stdlib.h>
#include "FileException.h"

using namespace std;

FileParser::FileParser() {
}

ifstream FileParser::openFile(string &fileName) {
	ifstream file;
	file.open(fileName, std::ifstream::in);
	if (!file) {
		onOpenFileError(fileName);
	}
	return file;
}

void FileParser::onOpenFileError(string &fileName) {
	stringstream message;
	message << "Could not open the file: " << getAbsolutePath(fileName);
	throw FileException(message.str());
}

string FileParser::getAbsolutePath(string &fileName) {
	string path = __FILE__;
	path = path.substr(0, 1 + path.find_last_of('\\'));
	return path.append(fileName);
}

FileParser::~FileParser()
{
}

void FileParser::parse(string &fileName) {
	ifstream file = openFile(fileName);
	readFile(&file);
	file.close();
}

