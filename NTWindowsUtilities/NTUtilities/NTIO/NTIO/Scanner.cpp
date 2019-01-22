#include "stdafx.h"
#include "Scanner.h"

Scanner *Scanner::shared = NULL;

Scanner::Scanner()
{
}


Scanner::~Scanner()
{
}


Scanner *Scanner::getSharedScanner() {
	return Scanner::shared;
}

void Scanner::setSharedScanner(Scanner *scanner) {
	Scanner::shared = scanner;
}
