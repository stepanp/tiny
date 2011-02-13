//----------------------------
//tiny 2.5
//tinyrebar.h - Ребар
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYReBar: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent);
	//Вcтавить банд
	bool InsertBand(int index,TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h);
	bool AddBand(TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h);//Добавить банд
	bool DeleteBand(int index);//Удалить банд
	bool MoveBand(int index,int nindex);//Передвинуть банд
	bool ShowBand(int index,bool show);//Скрыть/Показать банд
	int GetBandCount();//Получить кол-во бандов
};

};