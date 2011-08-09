//-----------------------------
//tiny 2.5
//tinyappwnd.cpp - Обычное окно
//© 2009-2010 Stepan Prokofjev
//-----------------------------

#pragma once

#include "tinyappwnd.h"

using namespace tiny;

TINYAppWnd::TINYAppWnd()
{
	_oncustommsg.Connect(this,&TINYAppWnd::_OnCustomMsg);//Кастомная обработка сообщений
	//Стили
	propcaption.Init(this,WS_CAPTION,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propsysmenu.Init(this,WS_SYSMENU,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propresize.Init(this,WS_THICKFRAME,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propminbox.Init(this,WS_MINIMIZEBOX,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propmaxbox.Init(this,WS_MAXIMIZEBOX,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	proptoolwnd.Init(this,WS_EX_TOOLWINDOW,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	prophelp.Init(this,WS_EX_CONTEXTHELP,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	proptopmost.Init(this,WS_EX_TOPMOST,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
}
//Создание окна
bool TINYAppWnd::Create(TINYBaseWnd* parent)
{
	return TINYBaseWnd::Create(parent,L"TINYAppWnd",0,0,
		LoadCursor(0,IDC_ARROW),//Стандартный курсор
		0,WS_OVERLAPPEDWINDOW,0,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT);//Размер по умолчанию
}
//Кастомная обработка сообщений
LRESULT TINYAppWnd::_OnCustomMsg(TINYBaseWnd* wnd,TINYParams params)
{
	//Параметры сообщения
	TINYMSGPARAMS* msg=(TINYMSGPARAMS*)(params);

	//Установка максимального и минимального размера окна
	if(msg->code==WM_GETMINMAXINFO)
	{
		//Получаем параметры
		MINMAXINFO* minmax=(MINMAXINFO*)(msg->lparam);
		//Если свойства >0
		//Устанавливаем максимальный размер
		if(propmaxw) minmax->ptMaxTrackSize.x=propmaxw;
		if(propmaxh) minmax->ptMaxTrackSize.y=propmaxh;
		//Устанавливаем минимальный размер
		if(propminw) minmax->ptMinTrackSize.x=propminw;
		if(propminh) minmax->ptMinTrackSize.y=propminh;
	}
	return 0;
}