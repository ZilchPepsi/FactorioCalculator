#pragma once

#include "stdafx.h"

using namespace std;

class GuiEventHandler
{
	public:

		GuiEventHandler();
		~GuiEventHandler();


		// User Input Events
		std::wstring init();
		std::wstring destroy();

		std::wstring btn_click_calculate(int i, char * rate);
		std::wstring btn_click_reset();
		
		std::wstring rbtn_click_log();
		std::wstring rbtn_click_prd();
		std::wstring rbtn_click_int();
		std::wstring rbtn_click_cbt();

		std::wstring cbn_ichange_output(int i);
		std::wstring cbn_ichange_per(int i);
		
		// GUI dynamic populaiton
		vector<std::wstring> * get_per_items();
		vector<std::wstring> * get_output_items();

		std::wstring parseCalcToString();

	private:

		vector<std::wstring> per_items = { L"sec", L"min", L"hour", L"galactic year" };
		vector<std::wstring> output_items = { L"init item 0", L"init item 1" };

		std::vector<struct FactorioCalculator::FactorySetup*> factory;
		FactorioCalculator calc;

};

