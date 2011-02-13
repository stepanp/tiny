//----------------------------
//tiny 2.5
//tinyedit.h - Едит
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYEdit: public TINYControl
{
public:
	TINYEdit();
public:
	//Свойства
	TINYStyleProperty propnumber,//Вводить только числа
		proppassword,//Скрывать символы звездочками
		propreadonly,//Только чтение
		propuppercase,//Все симолы в верхнем регистре
		proplowercase,//Все симолы в нижнем регистре
		propautovscroll,//Вертикальный автоскролл
		propautohscroll,//Горизонтальный автоскролл
		propnohidesel;//Не скрывать выделение
	//События
	TINYEvent onchange;//При изменении
public:
	bool Create(TINYBaseWnd *parent);
protected:
	LRESULT _OnCustomCmd(TINYBaseWnd* wnd,TINYParams params);//Кастомная обработка команд
};

};