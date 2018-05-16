#include "FactorioCalculator.h"
#include <iostream>

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
	//get element information (struct)
	FactorioCalculations::Element el = jsonInterface.getValue(element);

	//some prototypes need to be broken down more, some don't
	switch (el.prototype)
	{
	case FactorioCalculations::Prototypes::RESOURCE:
		break;
	}



	//if this element is already in the list, just add to the requirements
	if (FactorioCalculator::FactorySetup* elementSetup = contains(factorySetup, el));

}
