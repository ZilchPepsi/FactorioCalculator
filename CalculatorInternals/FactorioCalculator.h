#ifndef FACTCALC
#define FACTCALC


#include "JSONInterface.h"
#include <vector>

/*
	this is the main file that will be called upon for use by user
*/
class FactorioCalculator
{
	json::JSONInterface jsonInterface;

public:
	/*
	represents an element and the building pieces that make it
	*/
	struct FactorySetup {

		struct FactorioCalculations::Element* element;

		double asm1, asm2, asm3;
		double stoneFurnace, steelFurnace, electricFurnace;
		double miners;
		double pumpjacks;
		double chemicalPlants;
		double refineries;
	};

private:
	struct FactorySetup* contains(std::vector<struct FactorySetup>&, struct FactorioCalculations::Element&);



public:
	FactorioCalculator(const char*);
	~FactorioCalculator();

	/*
		will calculate the build requirements for producing an element at a certain rate
		@param char* the item to make
		@param double the rate at which to make the item
	*/
	 void calculateFactorySetup (const char*, double, std::vector<struct FactorySetup>&);

};
#endif
