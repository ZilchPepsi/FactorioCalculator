#pragma once

#include "stdafx.h"

//#define FILENAME_ITEM "Items.json"

using namespace std;

class GuiEventHandler
{
	public:

		GuiEventHandler();
		~GuiEventHandler();


		// User Input Events
		std::string init();
		std::string destroy();

		std::string btn_click_calculate();
		std::string btn_click_reset();
		
		std::string rbtn_click_log();
		std::string rbtn_click_prd();
		std::string rbtn_click_int();
		std::string rbtn_click_cbt();

		std::string cbn_ichange_output(int i);
		std::string cbn_ichange_per(int i);
		
		// GUI dynamic populaiton
		vector<std::wstring> * get_per_items();
		vector<std::wstring> * get_output_items();

	private:

		vector<std::wstring> per_items = { L"sec", L"min", L"hour", L"galactic year" };
		vector<std::wstring> output_items = { L"init item 0", L"init item 1" };

		std::vector<struct FactorioCalculator::FactorySetup*> factory;
		//FactorioCalculator calc("Items.json");
};

