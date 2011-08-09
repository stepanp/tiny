//----------------------------
//tiny 2.5
//tinylistbox.cpp - Листбокс
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinylistbox.h"

using namespace tiny;

bool TINYListBox::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
					 int x,int y,int w,int h)
{
	return TINYControl::Create(parent,L"LISTBOX",0,
		exstyle,LBS_HASSTRINGS|LBS_NOTIFY|LBS_NOINTEGRALHEIGHT|style,
		x,y,w,h);
}
//Вставить итем
int TINYListBox::InsertItem(int index,LPCWSTR text)
{
	if(!SendMessage(_hwnd,LB_INSERTSTRING,WPARAM(index),LPARAM(text))) return false;
	return true;
}
//Добавить итем
int TINYListBox::AddItem(LPCWSTR text)
{
	return InsertItem(-1,text);
}
//Удалить итем
bool TINYListBox::DeleteItem(int index)
{
	if(!SendMessage(_hwnd,LB_DELETESTRING,WPARAM(index),0)) return false;
	return true;
}
//Получить кол-во итемов
int TINYListBox::GetCount()
{
	return SendMessage(_hwnd,LB_GETCOUNT,0,0);
}
//Выделить итем
bool TINYListBox::SetSel(int index)
{
	if(!SendMessage(_hwnd,LB_SETCURSEL,WPARAM(index),0)) return false;
	return true;
}
//Получить текущий выделенный итем
int TINYListBox::GetSel()
{
	return SendMessage(_hwnd,LB_GETCURSEL,0,0);
}
//Установить дополнительное значение
bool TINYListBox::SetItemData(int index,LPARAM data)
{
	if(!SendMessage(_hwnd,LB_SETITEMDATA,WPARAM(index),data)) return false;
	return true;
}
//Получить дополнительное значение
LPARAM TINYListBox::GetItemData(int index)
{
	return SendMessage(_hwnd,LB_GETITEMDATA,WPARAM(index),0);
}
//Очистить
bool TINYListBox::Clear()
{
	if(!SendMessage(_hwnd,LB_RESETCONTENT,0,0)) return false;
	return true;
}
//Установить текст итема
bool TINYListBox::SetItemText(int index,LPCWSTR text)
{
	LPARAM data=GetItemData(index);//Сохранить дополнительное значение итема
	if(!DeleteItem(index)) return false;//Удалить итем
	if(!InsertItem(index,text)) return false;//Вставить новый итем
	//Установить дополнительное значение итема
	return SetItemData(index,data);
}
//Получить текст итема
TINYStr TINYListBox::GetItemText(int index)
{
	wchar_t *text=new wchar_t[GetItemTextLen(index)];
	SendMessage(_hwnd,LB_GETTEXT,WPARAM(index),LPARAM(text));
	TINYStr str=text;
	delete[] text;
	return str;
}
//Получить длину текста итема
int TINYListBox::GetItemTextLen(int index)
{
	return SendMessage(_hwnd,LB_GETTEXTLEN,WPARAM(index),0);
}
//Получить индекс итема по координатам
int TINYListBox::GetItemFromPoint(int x,int y)
{
	return SendMessage(_hwnd,LB_ITEMFROMPOINT,0,MAKELPARAM(x,y));
}

//Функции выделения нескольких итемов (LBS_MULTIPLESEL)
//Получить кол-во выделенных итемов 
int TINYListBox::GetMultiSelCount()
{
	return SendMessage(_hwnd,LB_GETSELCOUNT,0,0);
}
//Выделить итем
bool TINYListBox::SetMultiSel(int index,bool sel/*Выделить/Снять выдление*/)
{
	if(!SendMessage(_hwnd,LB_SETSEL,WPARAM(sel),LPARAM(index))) return false;
	return true;
}
//Проверить выделен ли итем
bool TINYListBox::CheckMultiSel(int index)
{
	if(!SendMessage(_hwnd,LB_GETSEL,WPARAM(index),0)) return false;	
	return true;
}
//Получить массив индексов выделенных итемов
TINYArr<int> TINYListBox::GetMultiSel()
{
	int count=GetMultiSelCount();//Кол-во выделенных итемов
	//Создание массива размером по кол-ву итемов
	TINYArr<int> items(count);
	//Заполнить массив индексами выделенных итемов
	SendMessage(_hwnd,LB_GETSELITEMS,
		WPARAM(count),LPARAM(items.GetPointer()));
	return items;
}
//Снять выделение
bool TINYListBox::ClearMultiSel()
{
	return SetMultiSel(-1,false);
}