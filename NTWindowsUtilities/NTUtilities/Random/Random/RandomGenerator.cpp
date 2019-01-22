#include "stdafx.h"
#include "RandomGenerator.h"

RandomGenerator *RandomGenerator::shared = NULL;

RandomGenerator::RandomGenerator()
{
}


RandomGenerator::~RandomGenerator()
{
}

void RandomGenerator::setSharedGenerator(RandomGenerator *generator) {
	shared = generator;
}

RandomGenerator *RandomGenerator::getSharedGenerator() {
	return shared;
}