//----------------------------
//tiny 2.5
//tinylistbox.h - Листбокс
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYListBox: public TINYControl
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	int InsertItem(int index,LPCWSTR text);//Вставить итем
	int AddItem(LPCWSTR text);//Добавить итем
	bool DeleteItem(int index);//Удалить итем
	int GetCount();//Получить кол-во итемов
	bool SetSel(int index);//Выделить итем
	int GetSel();//Получить текущий выделенный итем
	bool SetItemData(int index,LPARAM data);//Установить дополнительное значение
	LPARAM GetItemData(int index);//Получить дополнительное значение
	bool Clear();//Очистить
	bool SetItemText(int index,LPCWSTR text);//Установить текст итема
	TINYStr GetItemText(int index);//Получить текст итема
	int GetItemTextLen(int index);//Получить длину текста итема
	int GetItemFromPoint(int x,int y);//Получить индекс итема по координатам

	//Функции выделения нескольких итемов (LBS_MULTIPLESEL)
	int GetMultiSelCount();//Получить кол-во выделенных итемов 
	bool SetMultiSel(int index,bool sel/*Выделить/Снять выдление*/);//Выделить итем
	bool CheckMultiSel(int index);//Проверить выделен ли итем
	TINYArr<int> GetMultiSel();//Получить массив индексов выделенных итемов
	bool ClearMultiSel();//Снять выделение
};

};