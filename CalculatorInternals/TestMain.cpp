#include <iostream>

#include "FactorioCalculator.h"

int main()
{
	FactorioCalculator calc("Items.json");


	std::cout << calc.calculateFactorySetup("Coal", 5) << std::endl;

	return 0;
}