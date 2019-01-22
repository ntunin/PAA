#include "stdafx.h"
#include "NecCommand.h"
#include <math.h>
#include <sstream>

NecCommand::NecCommand()
{
}


NecCommand::~NecCommand()
{
}

std::string NecCommand::toString(int value, int stringSize) {
	char *tmp = new char[stringSize];
	_itoa_s(value, tmp, stringSize, 10);
	std::string str = tmp;
	int size = (int)str.size();
	if (size < stringSize) {
		std::stringstream stream;
		std::string first = (value < 0) ? "-" : " ";
		stream << first;
		stringSize--;
		value = abs(value);
		stream << value;
		int count = stringSize - (int)str.size();
		for (int i = 0; i < count; i++) {
			stream << " ";
		}
		return stream.str();
	}
	else {
		return this->toString(value, stringSize, true);
	}
}

std::string NecCommand::toString(double value, int stringSize) {
	return this->toString(value, stringSize, false);
}

std::string NecCommand::toString(double value, int stringSize, bool exp) {
	std::stringstream stream;
	std::string first = (value < 0) ? " -" : " ";
	stream << first;
	value = abs(value);
	stringSize--;
	char *tmp;
	std::stringstream tmpstream;
	tmpstream << value;
	std::string str = tmpstream.str();
	if (exp) {
		int degree = 0;
		if (value > 10) {
			while (value > 10) {
				value /= 10;
				degree++;
			}
		} else if (value < 1 && value > 0 ) {
			while (value < 1) {
				value *= 10;
				degree--;
			}
		}
		stream << this->toString(value, stringSize - 4, false) << "E";
		std::string sign = (degree < 0) ? "-" : "+";
		stream << sign;
		degree = abs(degree);
		tmp = new char[4];
		_itoa_s(degree, tmp, 4, 10);
		str = tmp;
		int count = 3 - (int)str.size();
		for (int i = 0; i < count; i++) {
			stream << "0";
		}
		stream << degree;
		return stream.str();
	} else {
		int size = (int)str.size();
		if (size < stringSize) {
			stream << str;
			int count = stringSize - (int)str.size();
			if (count >= 2) {
				if (value - (int)value == 0) {
					stream << ".0";
					count -= 2;
				}
				for (int i = 0; i < count; i++) {
					stream << "0";
				}
			}
			
			str = stream.str();
		}
		else {
			return str.substr(0, stringSize);
		}
	}
	
	return str;
}