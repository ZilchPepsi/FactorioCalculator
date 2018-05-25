#ifndef FACTCALC
#define FACTCALC

#include "JSONInterface.h"
#include <vector>
/*
	this is the main file that will be called upon for use by user
*/

//const std::wstring WIN_RTN = L"\r\n";

class FactorioCalculator
{
	json::JSONInterface jsonInterface;
	
	struct FactorioCalculations::Furnace *stoneFurnace,*steelFurnace, *electricFurnace;
	struct FactorioCalculations::Assembler *asm1, *asm2, *asm3;


	double asm1Time, asm2Time, asm3Time;
	double stoneFurnaceTime, steelFurnaceTime, electricFurnaceTime;


public:
	/*
	represents an element and the building pieces that make it
	*/
	struct FactorySetup {

		const FactorioCalculations::Element* element;

		double asm1, asm2, asm3;
		double stoneFurnace, steelFurnace, electricFurnace;
		double miners;
		double pumpjacks;
		double chemicalPlants;
		double refineries;

		~FactorySetup()
		{
			delete element;
		}
	};

	FactorioCalculator();
	~FactorioCalculator();

	/*
	will calculate the build requirements for producing an element at a certain rate
	@param char* the item to make
	@param double the rate at which to make the item
	@param vector<FactorySetup*>& the array that will contain the factory afterwards
	*/
	void calculateFactorySetup(const char*, double, std::vector<FactorySetup*>&);

	const std::map<const char*, FactorioCalculations::Tabs>* getTabs();
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> getTab(FactorioCalculations::Tabs);

	void printString(FactorySetup&);
	std::wstring printToString(FactorySetup& fs);
	void init(const char *);

private:
	struct FactorySetup* contains(std::vector<FactorySetup*>&, const FactorioCalculations::Element*);
	void calculateResource(const FactorioCalculations::Element*, double, std::vector<FactorySetup*>&);
	void calculateItem(const FactorioCalculations::Element*, double, std::vector<FactorySetup*>&);
	void calculateAssemblyMachine(const FactorioCalculations::Element*, double, std::vector<FactorySetup*>&);
	void calculateTool(const FactorioCalculations::Element*, double, std::vector<FactorySetup*>&);
};
#endif
