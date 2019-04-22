#include "stdafx.h"
#include "DefaultRandomGenerator.h"
#include <time.h>


DefaultRandomGenerator::DefaultRandomGenerator()
{
	srand(time(NULL));
}

int DefaultRandomGenerator::next() {
	return rand();
}

DefaultRandomGenerator::~DefaultRandomGenerator()
{
}
