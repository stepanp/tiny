//----------------------------
//tiny 2.5
//tinylistview.h - Листвью
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"
#include "tinyimagelist.h"
#include "tinyheaderctrl.h"

namespace tiny{

class TINYListView: public TINYControlEx
{
protected:
	TINYHeaderCtrl _header;//Колонки (для режима LVS_REPORT)
protected:
	bool _AttachHeader();//Прикрепить колонки в режиме LVS_REPORT
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool Attach(HWND hwnd);
	TINYHeaderCtrl* GetHeader();//Получить хидер(колонки)
	bool SetExtendedStyle(DWORD style);//Установить расширенный стиль
	int InsertColumn(int index,LPCWSTR text,int w,int fmt/*Формат*/);//Вставить колонку
	int AddColumn(LPCWSTR text,int w,int fmt/*Формат*/);//Добавить колонку
	bool DeleteColumn(int index);//Удалить колонку
	bool SetColumnW(int index,int w);//Установить ширину колонки
	int InsertItem(int index,LPCWSTR text,int image);//Вставить итем
	int AddItem(LPCWSTR text,int image);//Добавить итем
	bool DeleteItem(int index);//Удалить итем
	//Установить субитем
	//Впринципе тоже самое что и SetItemText :)
	bool SetSubItem(int index,int subitem,LPCWSTR text);
	bool SetItemText(int index,int subitem,LPCWSTR text);//Установить текст итема
	bool SetItemImage(int index,int subitem,int image);//Установить индекс картинки
	bool SetItemData(int index,int subitem,LPARAM data);//Установить значение итема
	bool SetItemState(int index,UINT state);//Установить состояние итема
	TINYStr GetItemText(int index,int subitem);//Получить текст итема
	int GetItemImage(int index,int subitem);//Получить индекс картинки
	LPARAM GetItemData(int index,int subitem);//Получить значение итема
	UINT GetItemState(int index);//Получить состояние итема
	int GetItemCount();//Получить кол-во итемов
	bool SetImageList(TINYImageList *list);//Установить имаджлист
	//Установить имаджлист для маленьких иконок
	bool SetSmallImageList(TINYImageList *list);
	
};

};