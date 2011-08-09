//---------------------------------
//tiny 2.5
//tinymisc.h - Разные мелкие классы
//© 2009-2010 Stepan Prokofjev
//---------------------------------

#pragma once

#include "tinyobject.h"

namespace tiny
{

//------
//Иконка
//------
class TINYIcon: public TINYObject
{
public:
	TINYIcon();
	TINYIcon(UINT icon);
	TINYIcon(UINT icon,int w,int h);
protected:
	HICON _hicon;
public:
	HICON GetHICON();//Получить HICON
	void Attach(HICON icon);//Связать HICON
	bool LoadIcon(UINT icon);//Загрузить иконку
	bool LoadIconEx(UINT icon,int w,int h);//Загрузить иконку по размеру
	bool Destroy();//Уничтожить иконку
	operator HICON();
};

//----
//Рект
//----
class TINYRect: public TINYObject
{
public:
	TINYRect();
	TINYRect(TINYRect& rect);
	TINYRect(RECT& rect);
	TINYRect(int x,int y,int w,int h);
public:
	int x,y,w,h;
public:
	//Операторы копирования
	TINYRect& operator=(TINYRect& rect);
	TINYRect& operator=(RECT& rect);
	operator RECT();
};

};

