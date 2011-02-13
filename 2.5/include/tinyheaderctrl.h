//-----------------------------
//tiny 2.5
//tinybuttons.h - Хидер контрол
//© 2009-2010 Stepan Prokofjev
//-----------------------------

#pragma once

#include "tinybase.h"
#include "tinyimagelist.h"

namespace tiny{

class TINYHeaderCtrl: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	int InsertItem(int index,LPCWSTR text,int w,int fmt);//Вставить итем
	int AddItem(LPCWSTR text,int w,int fmt);//Добавить итем
	bool SetItemText(int index,LPCWSTR text);//Установить текст
	bool SetItemImage(int index,int image);//Установить индекс картинки
	bool SetItemData(int index,LPARAM data);//Установить значение итема
	bool SetItemFormat(int index,int fmt);//Установить формат итема
	TINYStr GetItemText(int index);//Получить текст итема
	int GetItemImage(int index);//Получить индекс картинки
	LPARAM GetItemData(int index);//Получить значение итема
	int GetItemFormat(int index);//Получить формат итема
	int GetItemCount();//Получить кол-во итемов
	bool SetImageList(TINYImageList *list);//Установить имаджлист
	
};


};