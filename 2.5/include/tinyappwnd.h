//----------------------------
//tiny 2.5
//tinyappwnd.h - Обычное окно
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYAppWnd: public TINYBaseWnd
{
public:
	TINYAppWnd();
public:
	//Свойства
	int propmaxw,//Максимальная ширина
		propmaxh,//Максимальная высота
		propminw,//Минимальная ширина
		propminh;//Минимальная высота
	//Стили
	TINYStyleProperty propcaption,//Заголовок
		propsysmenu,//Системное меню на заголовке
		propresize,//Можно ресайзить окно
		propminbox,//Кнопка "свернуть" в заголовке
		propmaxbox,//Кнопка "развернуть" в заголовке
		proptoolwnd,//Плавающая панель
		prophelp,//Кнопка "?" в заголовке
		proptopmost;//Поверх всех окон
public:
	bool Create(TINYBaseWnd* parent);
	LRESULT _OnCustomMsg(TINYBaseWnd* wnd,TINYParams params);//Кастомная обработка сообщений
};

};