//------------------------------------------
//tiny 2.5
//tinycontrol.cpp - Базовые классы контролов
//© 2009-2010 Stepan Prokofjev
//------------------------------------------

#include "tinycontrol.h"

using namespace tiny;

//--------------
//Класс контрола
//--------------

TINYControl::TINYControl() 
{
	_isctrl=true;//Это контрол
}

bool TINYControl::Attach(HWND hwnd)
{
	if(TINYBaseWnd::Attach(hwnd)) return false;
	_SubClass();
	return true;
}

bool TINYControl::Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h)
{
	//Получение HWND родительского окна
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();

	//Создание контрола
	_hwnd=CreateWindowEx(exstyle,classname,text,
		WS_CHILD|WS_VISIBLE|style,
		x,y,w,h,hparent,0,GetModuleHandle(0),0);	
	if(!_hwnd) return false;

	TinySetDefaultFont(_hwnd);//Установка стандартного шрифта
	_SubClass();//Сабклассинг

	//Запуск обработчика oncreate
	oncreate(this,0);
	return true;
}
//Сабклассинг
void TINYControl::_SubClass()
{
	//Сохранение указателя на экземпляр класса в GWL_USERDATA
	SetWindowLong(_hwnd,GWL_USERDATA,LONG(this)/*Указатель на экземпляр класса*/);
	//Сабклассинг окна
	_PrevProc=WNDPROC(SetWindowLong(_hwnd,GWL_WNDPROC,LONG(_WndProc)));	
}

LRESULT CALLBACK TINYControl::_WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	//Получение указателя на экземпляр класса
	TINYControl *ctrl=0;	
	ctrl=(TINYControl*)TinyGetPointer(hwnd);
	if(ctrl)//Проверка указателя
	{
		//Запуск функции обработки сообщений		
		LRESULT result=ctrl->_OnMessage(ctrl,message,wparam,lparam);
		//Если result не равен 0, то вернуть result
		if(result) return result;
	}
	return CallWindowProc(ctrl->_PrevProc,hwnd,message,wparam,lparam);
}


//--------------------------------------
//Класс расширенного контрола (commctrl)
//--------------------------------------

bool TINYControlEx::Create(TINYBaseWnd *parent,DWORD icc,LPCWSTR classname,LPCWSTR text,
		DWORD exstyle,DWORD style,int x,int y,int w,int h)
{
	//Инитиализация commctrl
	INITCOMMONCONTROLSEX init;
	init.dwSize=sizeof(INITCOMMONCONTROLSEX);
	init.dwICC=icc;
	InitCommonControlsEx(&init);
	return TINYControl::Create(parent,classname,text,exstyle,style,x,y,w,h);
}

//Установка стандартного шрифта для контрола
bool tiny::TinySetDefaultFont(HWND hwnd)
{
	if(!SendMessage(hwnd,WM_SETFONT,
		WPARAM(HFONT(GetStockObject(DEFAULT_GUI_FONT))),LPARAM(TRUE))) return false;
	return true;
}