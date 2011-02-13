//----------------------------
//tiny 2.5
//tinycombobox.h - Комбобокс
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYComboBox: public TINYControl
{
public:
	TINYComboBox();
	//События
	TINYEvent oncloseup,//При закрытии списка
		ondropdown,//При выпадении списка
		oneditchange,//При изменении едита
		onselchange,//При изменении выделения
		onselect;//При выборе пункта
public:
	bool Create(TINYBaseWnd *parent);
	bool InsertItem(int index,LPCWSTR text);//Вставить итем
	bool AddItem(LPCWSTR text);//Добавить итем
	bool DeleteItem(int index);//Удалить итем
	int GetCount();//Получить кол-во итемов
	bool SetSel(int index);//Выделить итем
	int GetSel();//Получить текущий выделенный итем
	bool SetItemData(int index,LPARAM data);//Установить дополнительное значение
	LPARAM GetItemData(int index);//Получить дополнительное значение
	bool Clear();//Очистить
	TINYStr GetItemText(int index);//Получить текст итема
	int GetItemTextLength(int index);//Получить длину текста итема
protected:
	LRESULT _OnCustomCmd(TINYBaseWnd* wnd,TINYParams params);//Кастомная обработка команд

};

};