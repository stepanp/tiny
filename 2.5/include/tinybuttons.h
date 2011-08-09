//--------------------------------------
//tiny 2.5
//tinybuttons.h - Кнопка, чекбокс и т.п.
//© 2009-2010 Stepan Prokofjev
///--------------------------------------

#pragma once

#include "tinybase.h"

namespace tiny{


//------
//Кнопка
//------
class TINYButton: public TINYControl
{
public:
	TINYButton();
	//События
	TINYEvent onclick;//При клике
public:
	bool Create(TINYBaseWnd *parent);
protected:
	LRESULT _OnCustomCmd(TINYBaseWnd* wnd,TINYParams params);//Кастомная обработка команд

};

//-------
//Чекбокс
//-------
class TINYCheckBox: public TINYButton
{
public:
	TINYCheckBox();
	//Свойства
	TINYBoolProperty propcheck;//Стоит ли галочка
public:
	bool Create(TINYBaseWnd *parent);
	bool SetCheck(bool check);//Установить галочку
	bool GetCheck();//Проверить галочку

};

//-----------
//Радиокнопка
//-----------
class TINYRadioButton: public TINYCheckBox
{
public:
	bool Create(TINYBaseWnd *parent);
};

//--------
//Групбокс
//--------
class TINYGroupBox: public TINYButton
{
public:
	bool Create(TINYBaseWnd *parent);
};

};