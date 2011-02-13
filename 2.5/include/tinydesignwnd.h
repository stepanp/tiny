//------------------------------------
//tiny 2.5
//tinydesignwnd.h - Окно для дизайнера
//© 2009-2010 Stepan Prokofjev
//------------------------------------

#pragma once

#include "tinyappwnd.h"

//Макросы для генераатора
#define TINY_GEN_CTRLS(TINYDesignWnd)//Начало объявления контролов
#define TINY_GEN_CTRLS_END//Конец объявления контролов
#define TINY_GEN_CREATE(TINYDesignWnd)//Начало создания контролов
#define TINY_GEN_CREATE_END//Конец создания контролов

namespace tiny{

class TINYDesignWnd: public TINYAppWnd
{
public:
	//Установить параметры окна
	void SetDesignParams(LPCWSTR text,UINT icon,
		DWORD exstyle,DWORD style,int x,int y,int w,int h);
};

};