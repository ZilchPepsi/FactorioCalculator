#include <iostream>

#include "FactorioCalculator.h"


int main()
{
	FactorioCalculator calc("Items.json");

	std::vector<struct FactorioCalculator::FactorySetup*> factory;

	calc.calculateFactorySetup("Assembling Machine 1", 5, factory);
	//calc.calculateFactorySetup("Iron Gear Wheel", 5, factory);
	//calc.calculateFactorySetup("Iron Plate", 5, factory);
	//calc.calculateFactorySetup("Electronic Circuit", 5, factory);

	for(FactorioCalculator::FactorySetup* fs : factory)
	{
		calc.printString(*fs);
		std::cout<< std::endl;
		for (int x = 0; x < 30; x++)
			std::cout << "-";
		std::cout << std::endl << std::endl;
		//delete  fs;

	}
	std::cout << "Done" << std::endl;
	return 0;
}
