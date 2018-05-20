#include <iostream>

#include "FactorioCalculator.h"

int main()
{
	FactorioCalculator calc("Items.json");

	std::vector<struct FactorioCalculator::FactorySetup*> factory;

	calc.calculateFactorySetup("Iron Plate", 5, factory);

	//TODO each element in these factories needs to be deleted
	for (FactorioCalculator::FactorySetup* fs : factory)
	{
		calc.printString(*fs);
		std::cout<< std::endl;
		for (int x = 0; x < 30; x++)
			std::cout << "-";
		std::cout << std::endl << std::endl;;
		delete fs;
	}

	return 0;
}