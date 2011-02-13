//----------------------------
//tiny 2.5
//tinysyslink.h - Ссылка
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinystatic.h"
#include "tinygdi.h"

namespace tiny{

class TINYSysLink: public TINYControl
{
public:
	TINYSysLink();
protected:
	bool _visited,//Посещена ли сслыка
		_enablevis;//Включить посещение ссылки
public:
	bool Create(TINYBaseWnd *parent,LPCWSTR text,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool EnableVisiting(bool enable);//Включить посещение ссылки
	bool GetEnableVisiting();//Узнать включено ли посещение ссылки
	bool SetVisited(bool visited);//Установить посещена ли ссылка
	bool GetVisited();//Узнать посещена ли ссылка
	//Обработчики сообщений
	LRESULT OnColor(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);//WM_CTLCOLORSTATIC
	LRESULT OnMouseUp(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);//WM_LBUTTONUP
};

};