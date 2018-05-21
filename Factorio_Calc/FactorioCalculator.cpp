#include "FactorioCalculator.h"
#include <iostream>
#include <cmath>

FactorioCalculator::FactorioCalculator(const char* fileName)
{}

void FactorioCalculator::init(const char* fileName)
{

	jsonInterface.init(fileName);

	using namespace FactorioCalculations;
	stoneFurnace = (Furnace*)jsonInterface.getValueWithHint("Stone Furnace", "FURNACE");
	steelFurnace = (Furnace*)jsonInterface.getValueWithHint("Steel Furnace", "FURNACE");
	electricFurnace = (Furnace*)jsonInterface.getValueWithHint("Electric Furnace", "FURNACE");

	asm1 = (Assembler*)jsonInterface.getValueWithHint("Assembling Machine 1", "ASSEMBLINGMACHINE");
	asm2 = (Assembler*)jsonInterface.getValueWithHint("Assembling Machine 2", "ASSEMBLINGMACHINE");
	asm3 = (Assembler*)jsonInterface.getValueWithHint("Assembling Machine 3", "ASSEMBLINGMACHINE");
}

FactorioCalculator::~FactorioCalculator()
{
	delete stoneFurnace;
	delete steelFurnace;
	delete electricFurnace;
	delete asm1;
	delete asm2;
	delete asm3;
}

/*
	tests the vector for an instance of the element, returns the element, or null if not found
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
void FactorioCalculator::printString( FactorioCalculator::FactorySetup& fs)
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

const std::map<const char*, const char*>* FactorioCalculator::getTabs()
{
	return jsonInterface.getTabs();


}


void FactorioCalculator::calculateFactorySetup(const char* element, double rate, std::vector <struct FactorySetup*>& factorySetup)
{
	//std::cout << "starting " << element << std::endl;

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
	case Prototypes::ASSEMBLINGMACHINE:
		calculateAssemblyMachine(el, rate, factorySetup);
	case Prototypes::TOOL:
		calculateTool(el, rate, factorySetup);
		break;
	}
}

/*
	given a resource, will calculate the factory
*/
void FactorioCalculator::calculateResource(const FactorioCalculations::Element* el, double rate, std::vector<FactorioCalculator::FactorySetup*>& factorySetup)
{
	//std::cout << "in RESOURCE with " << el->name << std::endl;

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

	switch (i->craftMethod)
	{
	case CraftMethods::cCRAFT:

		asm1Time = getBuildSpeed(asm1, i);
		asm2Time = getBuildSpeed(asm2, i);
		asm3Time = getBuildSpeed(asm3, i);

		if (FactorySetup* fs = contains(factorySetup, el))
		{
			fs->asm1 += rate / asm1Time;
			fs->asm2 += rate / asm2Time;
			fs->asm3 += rate / asm3Time;
		}
		else
		{
			fs = new FactorySetup();
			fs->element = el;
			fs->asm1 = rate / asm1Time;
			fs->asm2 = rate / asm2Time;
			fs->asm3 = rate / asm3Time;

			factorySetup.push_back(fs);
		}
		break;
	case CraftMethods::cFURNACE:

		stoneFurnaceTime = getBuildSpeed(stoneFurnace, i);
		steelFurnaceTime = getBuildSpeed(steelFurnace, i);
		electricFurnaceTime = getBuildSpeed(electricFurnace, i);

		if (FactorySetup* fs = contains(factorySetup, el))
		{
			fs->stoneFurnace += rate / stoneFurnaceTime;
			fs->steelFurnace += rate / steelFurnaceTime;
			fs->electricFurnace += rate / electricFurnaceTime;
		}
		else
		{
			fs = new FactorySetup();

			fs->element = el;
			fs->stoneFurnace = rate / stoneFurnaceTime;
			fs->steelFurnace = rate / steelFurnaceTime;
			fs->electricFurnace = rate / electricFurnaceTime;

			factorySetup.push_back(fs);
		}

		break;
	}
	//std::cout << "finished " << i->name << "...working on " << i->ingredients.size() << " ingredients" << std::endl;
	for (Ingredient* ing : i->ingredients)
	{
		calculateFactorySetup(ing->name, rate*ing->count, factorySetup);
	}
	//std::cout << "finished " << i->name << " ingredients, now " << factorySetup.size() << " items in factorySetup" << std::endl;

}

void FactorioCalculator::calculateAssemblyMachine(const FactorioCalculations::Element* el, double rate, std::vector<FactorySetup*>& factorySetup)
{
	using namespace FactorioCalculations;
	Assembler* a = (Assembler*)el;

	asm1Time = getBuildSpeed(asm1, a);
	asm2Time = getBuildSpeed(asm2, a);
	asm3Time = getBuildSpeed(asm3, a);

	std::cout << "asm1 rate: " << asm1Time << std::endl;
	std::cout << "asm2 rate: " << asm2Time << std::endl;
	std::cout << "asm3 rate: " << asm3Time << std::endl;

	if (FactorySetup* fs = contains(factorySetup, el))
	{
		fs->asm1 += rate / asm1Time;
		fs->asm2 += rate / asm2Time;
		fs->asm3 += rate / asm3Time;
	}
	else
	{
		fs = new FactorySetup();
		fs->element = el;
		fs->asm1 = rate / asm1Time;
		fs->asm2 = rate / asm2Time;
		fs->asm3 = rate / asm3Time;

		factorySetup.push_back(fs);
	}

	for (Ingredient* ing : a->ingredients)
	{
		calculateFactorySetup(ing->name, rate*ing->count, factorySetup);
	}
}

void FactorioCalculator::calculateTool(const FactorioCalculations::Element* el, double rate, std::vector<FactorySetup*>& factorySetup)
{
	calculateItem(el, rate, factorySetup);
}