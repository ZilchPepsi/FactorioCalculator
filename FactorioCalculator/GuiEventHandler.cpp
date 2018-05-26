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

std::wstring GuiEventHandler::btn_click_calculate(int i, char * rate)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string item = converter.to_bytes(output_items[i]);
	calc.calculateFactorySetup(item.c_str(), std::stod(rate), factory);
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
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::LOGISTICS);
	
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	output_items.clear();

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{
		std::wstring retval = L"";
		const char*  x = pair.first;
		retval += converter.from_bytes(x);

		output_items.push_back(retval);
	}
	
	return L"rbtn_click_log success";
	//return L"rbtn_click_log";
}

std::wstring GuiEventHandler::rbtn_click_prd()
{
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::PRODUCTION);
	output_items.clear();

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{
		std::wstring retval = L"";
		const char*  x = pair.first;
		retval += converter.from_bytes(x);

		output_items.push_back(retval);
	}

	return L"rbtn_click_prd success";
	//return L"rbtn_click_prd";
}

std::wstring GuiEventHandler::rbtn_click_int()
{
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::INTERMEDIATEPRODUCTS);

	output_items.clear();

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{
		std::wstring retval = L"";
		const char*  x = pair.first;
		retval += converter.from_bytes(x);

		output_items.push_back(retval);
	}

	return L"rbtn_click_int success";
	//return L"rbtn_click_int";
}

std::wstring GuiEventHandler::rbtn_click_cbt()
{
	const std::vector<std::pair<const char*, FactorioCalculations::Prototypes>> vec = calc.getTab(FactorioCalculations::Tabs::COMBAT);

	output_items.clear();

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	for (std::pair<const char*, FactorioCalculations::Prototypes> pair : vec)
	{
		std::wstring retval = L"";
		const char*  x = pair.first;
		retval += converter.from_bytes(x);

		output_items.push_back(retval);
	}

	return L"rbtn_click_cbt success";
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
