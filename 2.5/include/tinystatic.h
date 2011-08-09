//----------------------------
//tiny 2.5
//tinystatic.h - Статик
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYStatic: public TINYControl
{
public:
	bool Create(TINYBaseWnd *parent,LPCWSTR text,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool SetIcon(HICON icon);//Установить иконку
	HICON GetIcon();//Получить иконку
	bool SetBitmap(HBITMAP bmp);//Установить битмап
	HBITMAP GetBitmap();//Получить битмап
	bool SetCursor(HCURSOR cursor);//Установить курсор
	HCURSOR GetCursor();//Получить курсор
};

};