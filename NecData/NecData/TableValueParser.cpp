#include "stdafx.h"
#include "TableValueParser.h"
#include <math.h>
#include <string>

using namespace std;

TableValueParser::TableValueParser(std::string buffer) {
	this->input = buffer;
}


TableValueParser::~TableValueParser()
{
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool isSign(char c) {
	return c == '+' || c == '-';
}

bool isDot(char &c, bool allowComma) {
	if (allowComma && c == ',') {
		c = '.';
	}
	return c == '.';
}

void TableValueParser::parseSign(char c) {
	if (isDigit(c)) {
		this->sign = (buffer == "-") ? -1 : 1;
		this->state = 1;
		this->buffer = "";
		return;
	}
	if (isSign(c)) {
		buffer += c;
	}
	this->index++;
}

void TableValueParser::parseMantissa(char c, bool allowComma) {
	this->index++;	
	if (isDigit(c) || isDot(c, allowComma)) {
		this->buffer += c;
	} else {
		this->mantissa = atof(this->buffer.c_str());
		this->buffer = "";
		this->state = (c == 'E')? 2 : 3;
	}
}

void TableValueParser::parseExponenta(char c) {
	if (isDigit(c)) {
		buffer += c;
	} else if (isSign(c)) {
		if (buffer != "") {
			this->state = 3;
			this->exponenta = atoi(this->buffer.c_str());
			return;
		}
		buffer += c;
	} else {
		this->state = 3;
		this->exponenta = atoi(this->buffer.c_str());
		return;
	}
	this->index++;
}

int  TableValueParser::getInt() {
	this->parseInput(false);
	return (int)(this->sign*this->mantissa*pow(10, this->exponenta));
}
;
double  TableValueParser::getDouble() {
	return getDouble(false);
}
double TableValueParser::getDouble(bool allowComma) {
	this->parseInput(allowComma);
	return this->sign*this->mantissa*pow(10, this->exponenta);
}

bool TableValueParser::isEmpty() {
	return this->input.length() == 0;
}

void TableValueParser::parseInput(bool allowComma) {
	this->input.append(" ");
	int length = (int)this->input.length();
	this->state = 0;
	this->index = 0;
	this->exponenta = 0;
	this->mantissa = 0;
	this->buffer = "";
	while (this->state < 3 && this->index < length) {
		char c = this->input[this->index];
		switch (this->state) {
			case 0: {
				this->parseSign(c);
				break;
			}
			case 1: {
				this->parseMantissa(c, allowComma);
				break;
			}
			case 2: {
				this->parseExponenta(c);
				break;
			}
		}
	}
	this->input.erase(0, this->index);
	input.erase(input.find_last_not_of(" \n\r\t") + 1);
}

string  TableValueParser::getString() {
	int length = (int)this->input.length();
	this->state = 0;
	this->index = 0;
	this->buffer = "";
	while (this->state < 3 && this->index < length) {
		char c = this->input[this->index];
		switch (this->state) {
			case 0: {
				this->skipSpaces(c);
				break;
			}
			case 1: {
				this->parseString(c, true);
				break;
			}
		}
	}
	this->input.erase(0, this->index);
	return this->buffer;
}


std::string TableValueParser::getString(bool alowBeginFromDigit) {
	int length = (int)this->input.length();
	this->state = 0;
	this->index = 0;
	this->buffer = "";
	while (this->state < 3 && this->index < length) {
		char c = this->input[this->index];
		switch (this->state) {
		case 0: {
			this->skipSpaces(c);
			break;
		}
		case 1: {
			this->parseString(c, alowBeginFromDigit);
			break;
		}
		}
	}
	this->input.erase(0, this->index);
	return this->buffer;
}

void TableValueParser::skipSpaces(char c) {
	if (c == ' ' || c == '\t') {
		this->index++;
	}
	else {
		this->state = 1;
	}
}

void TableValueParser::parseString(char c, bool alowBeginFromDigit) {
	if (c == ' ' || c == '\t' || (!alowBeginFromDigit && c >= '0' && c <= '9' && !this->buffer.length())) {
		this->state = 3;
	}
	else {
		this->buffer += c;
		this->index++;
	}
}

void TableValueParser::setInput(string input) {
	this->input = input;
}
