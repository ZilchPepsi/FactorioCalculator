#include "stdafx.h"
#include "GuiEventHandler.h"

using namespace std;

GuiEventHandler::GuiEventHandler(){}
GuiEventHandler::~GuiEventHandler(){}

std::string GuiEventHandler::init() 
{
	/*
	TODO
	*/
	return "handler init";
}

std::string GuiEventHandler::destroy()
{
	/*
	TODO
	*/
	return "handler destroy";
}

std::string GuiEventHandler::btn_click_calculate()
{
	/* 
		TODO
	*/
	return "btn_click_calculate";
}
std::string GuiEventHandler::btn_click_reset()
{
	/*
	TODO
	*/
	return "btn_click_reset";
}

std::string GuiEventHandler::rbtn_click_log()
{
	/*
	TODO
	*/
	return "rbtn_click_log";
}

std::string GuiEventHandler::rbtn_click_prd()
{
	/*
	TODO
	*/
	return "rbtn_click_prd";
}

std::string GuiEventHandler::rbtn_click_int()
{
	/*
	TODO
	*/
	return "rbtn_click_int";
}

std::string GuiEventHandler::rbtn_click_cbt()
{
	/*
	TODO
	*/
	return "rbtn_click_cbt";
}

std::string GuiEventHandler::cbn_ichange_output(int i)
{
	/*
	TODO
	*/
	return "cbn_ichange_ouput" + std::to_string(i);
}

std::string GuiEventHandler::cbn_ichange_per(int i)
{
	/*
	TODO
	*/
	return "cbn_ichange_per" + std::to_string(i);
}

vector<std::wstring> * GuiEventHandler::get_per_items()
{
	return &per_items;
}

vector<std::wstring> * GuiEventHandler::get_output_items()
{
	return &output_items;
}
