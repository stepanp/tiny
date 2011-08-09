//----------------------------------------
//tiny 2.5
//tinycontrol.h - Базовые классы контролов
//© 2009-2010 Stepan Prokofjev
//----------------------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

//--------------
//Класс контрола
//--------------
class TINYControl: public TINYBaseWnd
{
public:
	TINYControl();
protected:
	WNDPROC _PrevProc;//Оконная функция для сабклассинга
public:
	bool Attach(HWND hwnd);
	bool Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h);
	void _SubClass();//Сабклассинг окна
protected:
	//Оконная функция
	static LRESULT CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
};


//--------------------------------------
//Класс расширенного контрола (commctrl)
//--------------------------------------
class TINYControlEx: public TINYControl
{
public:
	bool Create(TINYBaseWnd *parent,DWORD icc,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h);
};

//Установка стандартного шрифта для контрола
bool TinySetDefaultFont(HWND hwnd);

};