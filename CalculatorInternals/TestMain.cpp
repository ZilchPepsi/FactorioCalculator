#include <iostream>

#include "FactorioCalculator.h"

int main()
{
	FactorioCalculator calc("Items.json");

	std::vector<struct FactorioCalculator::FactorySetup> factory;

	calc.calculateFactorySetup("Coal", 5, factory);

	return 0;
}