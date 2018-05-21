#include "stdafx.h"
#include "GuiEventHandler.h"

using namespace std;

GuiEventHandler::GuiEventHandler(){}
GuiEventHandler::~GuiEventHandler(){}

std::wstring GuiEventHandler::init() 
{
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
	calc.init("Items.json");
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
	return L"rbtn_click_log";
}

std::wstring GuiEventHandler::rbtn_click_prd()
{
	/*
	TODO
	*/
	return L"rbtn_click_prd";
}

std::wstring GuiEventHandler::rbtn_click_int()
{
	/*
	TODO
	*/
	return L"rbtn_click_int";
}

std::wstring GuiEventHandler::rbtn_click_cbt()
{
	/*
	TODO
	*/
	return L"rbtn_click_cbt";
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
