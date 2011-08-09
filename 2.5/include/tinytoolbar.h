//----------------------------
//tiny 2.5
//tinytoolbar.h - Тулбар
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"
#include "tinyimagelist.h"

namespace tiny{

class TINYToolBar: public TINYControlEx
{
public:
	TINYToolBar();
public:
	bool Create(TINYBaseWnd *parent);
	//Установить расширенный стиль
	bool SetExtendedStyle(DWORD style);
	//Вставить кнопку
	bool InsertButton(int index,DWORD style,DWORD state,int nimage,
							LPCWSTR text,LPCWSTR tip,UINT id);
	//Добавить кнопку
	bool AddButton(DWORD style,DWORD state,int nimage,LPCWSTR text,LPCWSTR tip,UINT id);
	bool InsertSeparator(int index);//Втавить сепаратор
	bool AddSeparator();//Добавить сепаратор
	bool DeleteButton(int index);//Удалить кнопку
	bool MoveButton(int index,int nindex/*Новый индекс кнопки*/);//Передвинуть кнопку
	bool SetButtonState(int id,DWORD state);//Установить состояние кнопки
	DWORD GetButtonState(int id);//Получить состояние кнопки
	bool EnableButton(int id,bool enable);//Включить/Выключить кнопку
	bool ShowButton(int id,bool show);//Показать/Скрыть кнопку
	bool SetImageList(TINYImageList *list);//Установить имаджлист
	//Установить имаджлист для подсвеченных кнопок
	bool SetHotImageList(TINYImageList *list);
	//Установить имаджлист для отключенных кнопок
	bool SetDisbaleImageList(TINYImageList *list);
	void AutoSize();//Установить размер автоматически
	int GetButtonCount();//Получить кол-во кнопок
	TBBUTTON GetButton(int index);//Получить кнопку

protected:
	//Обработчик для всплывающих подсказок
	LRESULT _OnToolTip(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);
};

};