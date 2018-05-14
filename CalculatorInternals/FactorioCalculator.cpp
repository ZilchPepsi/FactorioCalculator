#include "FactorioCalculator.h"
#include <iostream>

FactorioCalculator::FactorioCalculator(const char* fileName) : jsonInterface(fileName)
{
}


FactorioCalculator::~FactorioCalculator()
{
}

const char* FactorioCalculator::calculateFactorySetup(const char* element, double rate)
{
	if (jsonInterface.hasValue(element))
		std::cout << "got it" << std::endl;
	FactorioCalculations::Element el = jsonInterface.getValue(element);
	return "";
}
