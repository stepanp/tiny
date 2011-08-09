//----------------------------------------
//tiny 2.5
//tinybuttons.cpp - Кнопка, чекбокс и т.п.
//© 2009-2010 Stepan Prokofjev
//----------------------------------------

#include "tinybuttons.h"

using namespace tiny;


//------
//Кнопка
//------
TINYButton::TINYButton()
{
	_oncustomcmd.Connect(this,&TINYButton::_OnCustomCmd);//Кастомная обработка команд
}
bool TINYButton::Create(TINYBaseWnd *parent)
{
	return TINYControl::Create(parent,L"BUTTON",0,0,0,0,0,100,25);
}
//Кастомная обработка команд
LRESULT TINYButton::_OnCustomCmd(TINYBaseWnd* wnd,TINYParams params)
{
	//Параметры команды
	TINYMSGPARAMS* cmd=(TINYMSGPARAMS*)(params);

	if(cmd->code==BN_CLICKED) onclick(wnd,0);
	return 0;
}

//-------
//Чекбокс
//-------
TINYCheckBox::TINYCheckBox()
{
	propcheck.Init(this,&TINYCheckBox::SetCheck,&TINYCheckBox::GetCheck);
}

bool TINYCheckBox::Create(TINYBaseWnd *parent)
{
	if(!TINYButton::Create(parent)) return false;
	return AddStyle(BS_AUTOCHECKBOX);
}
//Установить галочку
bool TINYCheckBox::SetCheck(bool check)
{
	int value=0;
	if(check) value=1;
	if(!SendMessage(_hwnd,BM_SETCHECK,value,0)) return false;
	return true;
}
//Проверить галочку
bool TINYCheckBox::GetCheck()
{
	if(SendMessage(_hwnd,BM_GETCHECK,0,0)==1) return true;
	return false;
}

//-----------
//Радиокнопка
//-----------

bool TINYRadioButton::Create(TINYBaseWnd *parent)
{
	if(!TINYButton::Create(parent)) return false;
	return AddStyle(BS_AUTORADIOBUTTON);
}

//--------
//Групбокс
//--------

bool TINYGroupBox::Create(TINYBaseWnd *parent)
{
	if(!TINYButton::Create(parent)) return false;
	return AddStyle(BS_GROUPBOX);
}
