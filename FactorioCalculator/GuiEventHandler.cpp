#include "stdafx.h"
#include "GuiEventHandler.h"
#include <string>
#include <codecvt>

using namespace std;

GuiEventHandler::GuiEventHandler(){}
GuiEventHandler::~GuiEventHandler(){}

std::wstring GuiEventHandler::init() 
{
	calc.init("Items.json");
	return L"handler init";
}

std::wstring GuiEventHandler::destroy()
{
	/*
	TODO
	*/
	for (int i = 0; i < factory.size(); i++)
	{
		delete factory[i];
	}
	return L"handler destroy";
}

std::wstring GuiEventHandler::btn_click_calculate()
{
	/* 
		TODO
	*/
	calc.calculateFactorySetup("Iron Plate", 5, factory);
	return parseCalcToString();
}
std::wstring GuiEventHandler::btn_click_reset()
{
	/*
	TODO
	*/
	return L"btn_click_reset";
}

std::wstring GuiEventHandler::rbtn_click_log()
{
	/*
	TODO
	*/
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::LOGISTICS);

	std::wstring retval = L"";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{

		const char*  x = pair.first;
		retval += converter.from_bytes(x);
		
		retval += WIN_RTN;
	}

	return retval;
	//return L"rbtn_click_log";
}

std::wstring GuiEventHandler::rbtn_click_prd()
{
	/*
	TODO
	*/
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::PRODUCTION);

	std::wstring retval = L"";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{

		const char*  x = pair.first;
		retval += converter.from_bytes(x);

		retval += WIN_RTN;
	}

	return retval;
	//return L"rbtn_click_prd";
}

std::wstring GuiEventHandler::rbtn_click_int()
{
	/*
	TODO
	*/

	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::INTERMEDIATEPRODUCTS);

	std::wstring retval = L"";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{

		const char*  x = pair.first;
		retval += converter.from_bytes(x);

		retval += WIN_RTN;
	}

	return retval;
	//return L"rbtn_click_int";
}

std::wstring GuiEventHandler::rbtn_click_cbt()
{
	/*
	TODO
	*/
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::COMBAT);

	std::wstring retval = L"";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{

		const char*  x = pair.first;
		retval += converter.from_bytes(x);

		retval += WIN_RTN;
	}

	return retval;
	//return L"rbtn_click_cbt";
}

std::wstring GuiEventHandler::cbn_ichange_output(int i)
{
	/*
	TODO
	*/
	return L"cbn_ichange_ouput" + std::to_wstring(i);
}

std::wstring GuiEventHandler::cbn_ichange_per(int i)
{
	/*
	TODO
	*/
	return L"cbn_ichange_per" + std::to_wstring(i);
}

vector<std::wstring> * GuiEventHandler::get_per_items()
{
	return &per_items;
}

vector<std::wstring> * GuiEventHandler::get_output_items()
{
	return &output_items;
}

std::wstring GuiEventHandler::parseCalcToString()
{
	std::wstring retval = L"";

	for (FactorioCalculator::FactorySetup * fs : factory)
	{
		retval += WIN_RTN;
		retval += calc.printToString(*fs);

		for (int i = 0; i < 10; i++)
		{
			retval += L"-";
		}
		retval += WIN_RTN;
		retval += WIN_RTN;
	}

	return retval;
}
