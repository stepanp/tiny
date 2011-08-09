//----------------------------
//tiny 2.5
//tinymenu.h - Меню
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

//----
//Меню
//----
class TINYMenu: public TINYObject
{
protected:
	HMENU _menu;
public:
	bool Create();
	bool Create(UINT menu);//Создать из ресурсов
	bool Attach(HMENU menu);//Создать из HMENU
	HMENU GetHMENU();//Получить HMENU
	bool SetToWindow(TINYBaseWnd *wnd);//Установить меню окну
	bool InsertItem(int index,LPCWSTR text,UINT id,TINYMenu* submenu);//Вставить пункт меню
	bool AddItem(LPCWSTR text,UINT id,TINYMenu* submenu);//Добавить пункт меню
	bool DeleteItem(int index);//Удалить пункт меню
	TINYMenu* GetSubMenu(int index);//Получить субменю
	bool SetSubMenu(int index,TINYMenu* submenu);//Установить субменю	
	DWORD GetItemState(int index);//Получить состояние
	bool SetItemState(int index,DWORD state);//Установить состояние
	bool SetItemData(int index,LPARAM data);//Установить дополнительное значение
	LPARAM GetItemData(int index);//Получить дополнительное значение
};

//----------------
//Всплывающее меню
//----------------
class TINYPopupMenu: public TINYMenu
{
public:
	bool Create();
	bool Create(UINT menu);//Создать из ресурсов
	bool InsertSeparator(int index);//Вставить сепаратор
	bool AddSeparator();//Добавить сепаратор
	bool EnableItem(int index,bool enable);//Задизейблить меню
	bool GetEnableItem(int index);//Проверить задизейблен ли пункт меню
	bool CheckItem(int index,bool check);//Поставить галочку
	bool GetCheckItem(int item);//Проверить галочку
	bool Track(TINYBaseWnd *parent,int x=-1,int y=-1);//Показать меню
};

};