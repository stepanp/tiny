//-----------------------------------
//tiny 2.5
//tinymisc.cpp - Разные мелкие классы
//© 2009-2010 Stepan Prokofjev
//-----------------------------------

#include "tinymisc.h"

using namespace tiny;

//------
//Иконка
//------

TINYIcon::TINYIcon() {_hicon=0;}
TINYIcon::TINYIcon(UINT icon) {LoadIcon(icon);}
TINYIcon::TINYIcon(UINT icon,int w,int h) {LoadIconEx(icon,w,h);}
//Получить HICON
HICON TINYIcon::GetHICON() {return _hicon;}
//Связать HICON
void TINYIcon::Attach(HICON icon) {_hicon=icon;}
//Загрузить иконку
bool TINYIcon::LoadIcon(UINT icon)
{
	HICON hicon=::LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(icon));
	if(!hicon) return false;
	_hicon=hicon;
	return true;
}
//Загрузить иконку по размеру
bool TINYIcon::LoadIconEx(UINT icon,int w,int h)
{
	HICON hicon=HICON(LoadImage(GetModuleHandle(0),MAKEINTRESOURCE(icon),
		IMAGE_ICON,w,h,0));
	if(!hicon) return false;
	_hicon=hicon;
	return true;
}
//Уничтожить иконку
bool TINYIcon::Destroy()
{
	if(!DestroyIcon(_hicon)) return false;
	return true;
}
TINYIcon::operator HICON() {return _hicon;}

//----
//Рект
//----

TINYRect::TINYRect()
{
	x=y=w=h=0;
}
TINYRect::TINYRect(TINYRect& rect) 
{
	x=rect.x;
	y=rect.y;
	w=rect.w;
	h=rect.h;
}
TINYRect::TINYRect(RECT& rect) 
{
	x=rect.left;
	y=rect.top;
	w=rect.right-rect.left;//Ширина
	h=rect.bottom-rect.top;//Высота
}
TINYRect::TINYRect(int x,int y,int w,int h)
{
	TINYRect::x=x;
	TINYRect::y=y;
	TINYRect::w=w;
	TINYRect::h=h;
}
//Операторы копирования
TINYRect& TINYRect::operator=(TINYRect& rect)
{
	x=rect.x;
	y=rect.y;
	w=rect.w;
	h=rect.h;
	return *this;
}
TINYRect& TINYRect::operator=(RECT& rect)
{
	x=rect.left;
	y=rect.top;
	w=rect.right-rect.left;//Ширина
	h=rect.bottom-rect.top;//Высота
	return *this;
}
TINYRect::operator RECT()
{
	RECT rect;
	rect.left=x;
	rect.top=y;
	rect.right=x+w;
	rect.bottom=y+h;
	return rect;
}