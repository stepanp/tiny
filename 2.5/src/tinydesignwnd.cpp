//------------------------------------
//tiny 2.5
//tinydesignwnd.h - Окно для дизайнера
//© 2009-2010 Stepan Prokofjev
//------------------------------------

#include "tinydesignwnd.h"

using namespace tiny;

//Установить параметры окна
void TINYDesignWnd::SetDesignParams(LPCWSTR text,UINT icon,
		DWORD exstyle,DWORD style,int x,int y,int w,int h)
{
	SetText(text);//Установить текст
	if(icon)
	{
		SetIcon(TINYIcon(icon));//Установить большую иконку
		SetSmallIcon(TINYIcon(icon,16,16));//Установить маленькую иконку
	}
	AddStyle(style);//Установить стиль
	AddExStyle(exstyle);//Установить расширенный стиль
	int _x,_y,_w,_h;
	//Если параметры по умолчанию(CW_USEDEFAULT) то оставить старые, 
	//иначе установить новые
	if(x==CW_USEDEFAULT) _x=GetX(); else _x=x;
	if(y==CW_USEDEFAULT) _y=GetY(); else _y=y;
	if(w==CW_USEDEFAULT) _w=GetW(); else _w=w;
	if(h==CW_USEDEFAULT) _h=GetH(); else _h=h;
	//Установить размер и положение
	MoveWindow(this->GetHWND(),_x,_y,_w,_h,TRUE);
	Update();//Обновить окно
}