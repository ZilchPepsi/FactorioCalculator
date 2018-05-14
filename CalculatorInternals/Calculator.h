#ifndef CALCULATOR
#define CALCULATOR

#include <map>

/*
	This namespace contains utility functions for Factorio calculations
*/
namespace FactorioCalculations {


	/////////////////////////////////////////////////////////
	////prototypes
	/////////////////////////////////////////////////////////
	const int ProtoTypeCount = 5;

	enum Prototypes {
		RESOURCE,
		FLUID,
		ASSEMBLINGMACHINE,
		ITEM,
		PROCESS
	};

	static const char* ProtoType_strings[] = {
		"RESOURCE",
		"FLUID",
		"ASSEMBLINGMACHINE",
		"ITEM",
		"PROCESS"
	};

	/////////////////////////////////////////////////////////
	////END prototypes
	/////////////////////////////////////////////////////////

	struct Element {

		const char* name;
		Prototypes prototype;
		std::map<const char*, const char*> extras;
	};


	struct Resource : Element {
		double miningHardness;
		double miningTime;
	};
	
	struct fluid : Element {

	};

	static double getMiningSpeed(double miningPower, double miningHardness,double miningSpeed, double miningTime)
	{
		return (miningPower - miningHardness)*(miningSpeed / miningTime);
	}

	static double getBuildSpeed(double craftingTime, double craftingSpeed)
	{
		return craftingTime / craftingSpeed;
	}
}

#endif