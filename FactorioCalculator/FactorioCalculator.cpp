#include "stdafx.h"
#include <iostream>
#include <cmath>

FactorioCalculator::FactorioCalculator()
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

/*
utility function for printing out FactorySetup struct to string
*/
std::wstring FactorioCalculator::printToString(FactorioCalculator::FactorySetup& fs)
{
	std::wstring retval = L"";
	//retval += (wchar_t)(fs.element->name) + WIN_RTN;// + WIN_RTN;
	for (int i = 0; i < strlen(fs.element->name); i++)
	{
		retval += (wchar_t)(fs.element->name[i]);
	}
	retval += WIN_RTN;
	retval += WIN_RTN;

	if(fs.asm1!=0)
		retval += L"asm1: " + std::to_wstring((int)std::ceil(fs.asm1)) + WIN_RTN;
	if (fs.asm2 != 0)
		retval += L"asm2: " + std::to_wstring((int)std::ceil(fs.asm2)) + WIN_RTN;
	if (fs.asm3 != 0)
		retval += L"asm3: " + std::to_wstring((int)std::ceil(fs.asm3)) + WIN_RTN + WIN_RTN;

	if(fs.stoneFurnace!=0)
		retval += L"stoneFurnace: " + std::to_wstring((int)std::ceil(fs.stoneFurnace)) + WIN_RTN;
	if (fs.steelFurnace != 0)
	retval += L"steelFurnace: " + std::to_wstring((int)std::ceil(fs.steelFurnace)) + WIN_RTN;
	if (fs.electricFurnace != 0)
	retval += L"electricFurnace: " + std::to_wstring((int)std::ceil(fs.electricFurnace)) + WIN_RTN + WIN_RTN;

	if(fs.miners!=0)
		retval += L"miners: " + std::to_wstring((int)std::ceil(fs.miners)) + WIN_RTN;
	if (fs.pumpjacks != 0)
		retval += L"pumpjacks: " + std::to_wstring((int)std::ceil(fs.pumpjacks)) + WIN_RTN;
	if (fs.chemicalPlants != 0)
		retval += L"chemical plants: " + std::to_wstring((int)std::ceil(fs.chemicalPlants)) + WIN_RTN;
	if (fs.refineries != 0)
		retval += L"refineries: " + std::to_wstring((int)std::ceil(fs.refineries)) + WIN_RTN;

	return retval;
}

const std::map<const char*, FactorioCalculations::Tabs>* FactorioCalculator::getTabs()
{
	return jsonInterface.getTabs();
}
const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> FactorioCalculator::getTab(FactorioCalculations::Tabs tab)
{
	return jsonInterface.getTab(tab);
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
	case Prototypes::RESOURCE:			calculateResource(el, rate, factorySetup);
		break;
	case Prototypes::ITEM:				calculateItem(el, rate, factorySetup);
		break;
	case Prototypes::ASSEMBLINGMACHINE:	calculateAssemblyMachine(el, rate, factorySetup);
		break;
	case Prototypes::TOOL:				calculateTool(el, rate, factorySetup);
		break;
	case Prototypes::FURNACE:			calculateFurnace(el, rate, factorySetup);

	}
}



void FactorioCalculator::calculateFurnace(const FactorioCalculations::Element* el, double rate, std::vector<FactorySetup*>& factorySetup)
{
	baseCalculateItem((FactorioCalculations::Item*)el, rate, factorySetup);
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
	if (el->craftMethod != FactorioCalculations::CraftMethods::cPROCESS)
		baseCalculateItem((FactorioCalculations::Item*)el, rate, factorySetup);
	else
		calculateProcess((FactorioCalculations::Item*) el, rate, factorySetup);
}

void FactorioCalculator::calculateAssemblyMachine(const FactorioCalculations::Element* el, double rate, std::vector<FactorySetup*>& factorySetup)
{
	baseCalculateItem((FactorioCalculations::Item*)el, rate, factorySetup);
}

void FactorioCalculator::calculateTool(const FactorioCalculations::Element* el, double rate, std::vector<FactorySetup*>& factorySetup)
{
	baseCalculateItem((FactorioCalculations::Item*)el, rate, factorySetup);
}

void FactorioCalculator::calculateProcess(const FactorioCalculations::Item* i, double rate, std::vector<FactorySetup*>& factorySetup)
{
	const std::vector<const FactorioCalculations::Process*> processes = jsonInterface.getProcessesThatMake(i);

	//for each process that outputs the given item
	for (const FactorioCalculations::Process* p : processes)
	{
		//for each assembler available to this process ***this will mess up if there are multiple processes that output the same thing ie: refineries***
		for (const FactorioCalculations::Assembler* asmProcess : p->assemberOptions)
		{
			//for each assembler that can make the 
			for (const FactorioCalculations::Assembler* asmItem : i->assemblerOptions)
			{
				if (!strcmp(asmItem->name, asmProcess->name))
				{
					//the rate that the item is produced in whatever assembler this is
					double buildTime = FactorioCalculations::getBuildSpeed(asmItem, i);

					//if this item is already in the factory, just modify the current setup
					if (FactorySetup* fs = contains(factorySetup, i))
					{
						fs->chemicalPlants += rate / buildTime;
					}
					else
					{
						fs = new FactorySetup();
						fs->element = i;
						fs->chemicalPlants = rate / buildTime;

						factorySetup.push_back(fs);
					}
				}
			}
		}
	}

}



/*
	given an item, calculate number of assemblers / furnaces required to produce it at rate
*/
void FactorioCalculator::baseCalculateItem(const FactorioCalculations::Item* i, double rate, std::vector<FactorySetup*>& factorySetup)
{
	using namespace FactorioCalculations;

	switch (i->craftMethod)
	{
	case CraftMethods::cCRAFT:

		asm1Time = getBuildSpeed(asm1, i);
		asm2Time = getBuildSpeed(asm2, i);
		asm3Time = getBuildSpeed(asm3, i);

		if (FactorySetup* fs = contains(factorySetup, i))
		{
			fs->asm1 += rate / asm1Time;
			fs->asm2 += rate / asm2Time;
			fs->asm3 += rate / asm3Time;
		}
		else
		{
			fs = new FactorySetup();
			fs->element = i;
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

		if (FactorySetup* fs = contains(factorySetup, i))
		{
			fs->stoneFurnace += rate / stoneFurnaceTime;
			fs->steelFurnace += rate / steelFurnaceTime;
			fs->electricFurnace += rate / electricFurnaceTime;
		}
		else
		{
			fs = new FactorySetup();

			fs->element = i;
			fs->stoneFurnace = rate / stoneFurnaceTime;
			fs->steelFurnace = rate / steelFurnaceTime;
			fs->electricFurnace = rate / electricFurnaceTime;

			factorySetup.push_back(fs);
		}

		break;
	}
	for (Ingredient* ing : i->ingredients)
	{
		calculateFactorySetup(ing->name, rate*ing->count, factorySetup);
	}
}