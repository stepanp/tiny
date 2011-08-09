//----------------------------
//tiny 2.5
//tinycombobox.cpp - Комбобокс
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinycombobox.h"

using namespace tiny;

TINYComboBox::TINYComboBox()
{
	_oncustomcmd.Connect(this,&TINYComboBox::_OnCustomCmd);//Кастомная обработка команд
}

bool TINYComboBox::Create(TINYBaseWnd *parent)
{
	return TINYControl::Create(parent,L"COMBOBOX",0,0,CBS_HASSTRINGS,0,0,100,21);
}
//Вставить итем
bool TINYComboBox::InsertItem(int index,LPCWSTR text)
{
	if(!SendMessage(_hwnd,CB_INSERTSTRING,WPARAM(index),LPARAM(text))) return false;
	return true;
}
//Добавить итем
bool TINYComboBox::AddItem(LPCWSTR text)
{
	return InsertItem(-1,text);
}
//Удалить итем
bool TINYComboBox::DeleteItem(int index)
{
	if(!SendMessage(_hwnd,CB_DELETESTRING,WPARAM(index),0)) return false;
	return true;
}
//Получить кол-во итемов
int TINYComboBox::GetCount()
{
	return SendMessage(_hwnd,CB_GETCOUNT,0,0);
}
//Выделить итем
bool TINYComboBox::SetSel(int index)
{
	if(!SendMessage(_hwnd,CB_SETCURSEL,WPARAM(index),0)) return false;
	return true;
}
//Получить текущий выделенный итем
int TINYComboBox::GetSel()
{
	return SendMessage(_hwnd,CB_GETCURSEL,0,0);
}
//Установить дополнительное значение
bool TINYComboBox::SetItemData(int index,LPARAM data)
{
	if(!SendMessage(_hwnd,CB_SETITEMDATA,WPARAM(index),data)) return false;
	return true;
}
//Получить дополнительное значение
LPARAM TINYComboBox::GetItemData(int index)
{
	return SendMessage(_hwnd,CB_GETITEMDATA,WPARAM(index),0);
}
//Очистить
bool TINYComboBox::Clear()
{
	if(!SendMessage(_hwnd,CB_RESETCONTENT,0,0)) return false;
	return true;
}
//Получить текст итема
TINYStr TINYComboBox::GetItemText(int index)
{
	wchar_t *text=new wchar_t[GetItemTextLength(index)];
	SendMessage(_hwnd,CB_GETLBTEXT,WPARAM(index),LPARAM(text));
	TINYStr str=text;
	delete[] text;
	return str;
}
//Получить длину текста итема
int TINYComboBox::GetItemTextLength(int index)
{
	return SendMessage(_hwnd,CB_GETLBTEXTLEN,WPARAM(index),0);
}
//Кастомная обработка команд
LRESULT TINYComboBox::_OnCustomCmd(TINYBaseWnd* wnd,TINYParams params)
{
	//Параметры команды
	TINYMSGPARAMS* cmd=(TINYMSGPARAMS*)(params);

	//Вызов обработчиков событий
	switch(cmd->code)
	{
	case CBN_CLOSEUP:
		oncloseup(wnd,0);
		break;
	case CBN_DROPDOWN:
		ondropdown(wnd,0);
		break;
	case CBN_EDITCHANGE:
		oneditchange(wnd,0);
		break;
	case CBN_SELCHANGE:
		onselchange(wnd,0);
		break;
	case CBN_SELENDOK:
		onselect(wnd,0);
		break;
	}
	return 0;
}