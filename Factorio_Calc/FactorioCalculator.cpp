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
struct FactorioCalculator::FactorySetup* FactorioCalculator::contains(std::vector<struct FactorySetup*>& factory, const FactorioCalculations::Element* element)
{
	for (std::vector<struct FactorySetup*>::iterator el = factory.begin(); el != factory.end(); el++)
	{
		if (!strcmp((*el)->element->name, element->name))
			return *el;
	}
	return NULL;
}

/*
utility function for printing out FactorySetup struct
*/
void FactorioCalculator::printString(FactorioCalculator::FactorySetup& fs)
{
	std::cout << fs.element->name << std::endl << std::endl;

	std::cout << "asm1: " << fs.asm1 << std::endl;
	std::cout << "asm2: " << fs.asm2 << std::endl;
	std::cout << "asm3: " << fs.asm3 << std::endl << std::endl;

	std::cout << "stoneFurnace: " << fs.stoneFurnace << std::endl;
	std::cout << "steelFurnace: " << fs.steelFurnace << std::endl;
	std::cout << "electricFurnace: " << fs.electricFurnace << std::endl << std::endl;

	std::cout << "miners: " << fs.miners << std::endl;
	std::cout << "pumpjacks: " << fs.pumpjacks << std::endl;
	std::cout << "chemical plants: " << fs.chemicalPlants << std::endl;
	std::cout << "refineries: " << fs.refineries << std::endl;
}



void FactorioCalculator::calculateFactorySetup(const char* element, double rate, std::vector <struct FactorySetup*>& factorySetup)
{
	using namespace FactorioCalculations;


	//get element information (struct)
	const Element* el = jsonInterface.getValue(element);

	//some prototypes need to be broken down more, some don't
	switch (el->prototype)
	{
	case Prototypes::RESOURCE:
		calculateResource(el, rate, factorySetup);
		break;
	case Prototypes::ITEM:
		calculateItem(el, rate, factorySetup);
		break;
	}
}

/*
	given a resource, will calculate the factory
*/
void FactorioCalculator::calculateResource(const FactorioCalculations::Element* el, double rate, std::vector<FactorioCalculator::FactorySetup*>& factorySetup)
{
	using namespace FactorioCalculations;

	Resource* r = (Resource*)el;

	Miner* miner = (Miner*)jsonInterface.getValueWithHint("Electric Mining Drill", Prototype_strings[Prototypes::MINING_DRILL]);

	double miningSpeed = getMiningSpeed(miner, r);
	double miners = rate / miningSpeed;


	if (FactorySetup* fs = contains(factorySetup, el))
	{
		fs->miners += miners;
	}
	else
	{
		fs = new FactorySetup();

		fs->element = el;
		fs->miners = miners;
		factorySetup.push_back(fs);
	}

	delete miner;
}

void FactorioCalculator::calculateItem(const FactorioCalculations::Element* el, double rate, std::vector<FactorioCalculator::FactorySetup*>& factorySetup)
{
	using namespace FactorioCalculations;
	Item* i = (Item*)el;

	Furnace *stoneFurnace, *steelFurnace, *electricFurnace;

	switch (i->craftMethod)
	{
	case CraftMethods::cCRAFT:
		break;
	case CraftMethods::cFURNACE:
		stoneFurnace =		(Furnace*)jsonInterface.getValueWithHint("Stone Furnace", "FURNACE");
		steelFurnace =		(Furnace*)jsonInterface.getValueWithHint("Steel Furnace", "FURNACE");
		electricFurnace =	(Furnace*)jsonInterface.getValueWithHint("Electric Furnace", "FURNACE");

		double stoneFTime = getBuildSpeed(stoneFurnace, i);
		double steeFTime = getBuildSpeed(steelFurnace, i);
		double electricFTime = getBuildSpeed(electricFurnace, i);

		if (FactorySetup* fs = contains(factorySetup, el))
		{
			fs->stoneFurnace += rate / stoneFTime;
			fs->steelFurnace += rate / steeFTime;
			fs->electricFurnace += rate / electricFTime;
		}
		else
		{
			fs = new FactorySetup();

			fs->element = el;
			fs->stoneFurnace = rate / stoneFTime;
			fs->steelFurnace = rate / steeFTime;
			fs->electricFurnace = rate / electricFTime;

			factorySetup.push_back(fs);
		}

		break;
	}

	for (Ingredient* ing : i->ingredients)
	{
		calculateFactorySetup(ing->name, rate*ing->count, factorySetup);
	}

}