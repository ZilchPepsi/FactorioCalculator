#ifndef FACTCALC
#define FACTCALC


#include "JSONInterface.h"

/*
	this is the main file that will be called upon for use by user
*/
class FactorioCalculator
{
	json::JSONInterface jsonInterface;


public:
	FactorioCalculator(const char*);
	~FactorioCalculator();

	/*
		will calculate the build requirements for producing an element at a certain rate
		@param char* the item to make
		@param double the rate at which to make the item
	*/
	const char* calculateFactorySetup(const char*, double);

};
#endif
