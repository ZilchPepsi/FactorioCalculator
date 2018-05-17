#include "FactorioCalculator.h"
#include <iostream>
#include <cmath>

FactorioCalculator::FactorioCalculator(const char* fileName) : jsonInterface(fileName)
{
}


FactorioCalculator::~FactorioCalculator()
{
}

/*
	tests the vector for an instance of the element, returns the element
*/
struct FactorioCalculator::FactorySetup* FactorioCalculator::contains(std::vector<struct FactorySetup>& factory, struct FactorioCalculations::Element& element)
{
	for (std::vector<struct FactorySetup>::iterator el = factory.begin(); el != factory.end(); el++)
	{
		if (!strcmp((*el).element->name, element.name))
			return &*el;
	}
	return NULL;
}


void FactorioCalculator::calculateFactorySetup(const char* element, double rate, std::vector <struct FactorySetup>& factorySetup)
{
	using namespace FactorioCalculations;


	//get element information (struct)
	const Element* el = jsonInterface.getValue(element);

	//some prototypes need to be broken down more, some don't
	switch (el->prototype)
	{
	case Prototypes::RESOURCE:
		Resource* r = (Resource*)el;
		Miner* miner = (Miner*)jsonInterface.getValueWithHint("Electric Mining Drill", Prototype_strings[Prototypes::MINING_DRILL]);

		double miningSpeed = getMiningSpeed(miner, r);
		std::cout << "mining speed: " << miningSpeed<< std::endl;
		std::cout << "desired speed: " << rate << std::endl;


		std::cout << std::ceil(rate / miningSpeed) << std::endl;

		delete miner;
		break;
	}
	//if this element is already in the list, just add to the requirements
	//if (FactorioCalculator::FactorySetup* elementSetup = contains(factorySetup, el));


	delete el;
}
