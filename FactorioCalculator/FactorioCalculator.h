#ifndef FACTCALC
#define FACTCALC

#include "JSONInterface.h"
#include <vector>
#include <string>
/*
	this is the main file that will be called upon for use by user
*/

const std::string WIN_RTN = "\r\n";

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

		FactorioCalculator();//(const char*);
		void init(const char*);
		~FactorioCalculator();

		/*
		will calculate the build requirements for producing an element at a certain rate
		@param char* the item to make
		@param double the rate at which to make the item
		@param vector<FactorySetup*>& the array that will contain the factory afterwards
		*/
		void calculateFactorySetup(const char*, double, std::vector<FactorySetup*>&);
		void printString(FactorySetup&);
		std::string printToString(FactorySetup&);

	private:
		struct FactorySetup* contains(std::vector<FactorySetup*>&, const FactorioCalculations::Element*);
		void calculateResource(const FactorioCalculations::Element*, double, std::vector<FactorySetup*>&);
		void calculateItem(const FactorioCalculations::Element*, double, std::vector<FactorySetup*>&);
		void calculateAssemblyMachine(const FactorioCalculations::Element*, double, std::vector<FactorySetup*>&);
};
#endif
