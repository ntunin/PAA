#pragma once
#include <string>

class TableValueParser {
public:
	TableValueParser(std::string str);
	~TableValueParser();
	int getInt();
	double getDouble();
	double getDouble(bool allowComma);
	std::string getString();
	std::string getString(bool alowBeginFromDigit);
	void setInput(std::string str);
	bool isEmpty();
private:
	int index;
	int state;
	int sign;
	std::string input;
	std::string buffer;
	double mantissa;
	double exponenta;
	void parseSign(char c);
	void parseMantissa(char c, bool allowComma);
	void parseExponenta(char c);
	void skipSpaces(char c);
	void parseString(char c, bool alowBeginFromDigit);
	void parseInput(bool allowComma);
};

