//----------------------------
//tiny 2.5
//tinydialog.cpp - Диалог
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinydialog.h"

using namespace tiny;

bool TINYDialog::Create(TINYBaseWnd *parent,UINT dialog)
{
	//Проверка указателя на класс родительского окна
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();
	//Создание диалога
	if(!DialogBoxParam(GetModuleHandle(0),MAKEINTRESOURCE(dialog),hparent,_WndProc,
		LPARAM(this)/*Указатель на экземпляр класса*/)) return false;
	return true;
}
//Получить HWND контрола
HWND TINYDialog::GetItemHWND(UINT id)
{
	return GetDlgItem(_hwnd,id);
}
//Закрыть диалог
void TINYDialog::End()
{
	EndDialog(_hwnd,TRUE);
}
//Получить текст контрола
TINYStr TINYDialog::GetItemText(UINT id)
{
	wchar_t *text=new wchar_t[GetItemTextLen(id)+1];
	GetDlgItemText(_hwnd,id,text,GetItemTextLen(id)+1);
	TINYStr str=text;
	delete[] text;
	return str;
}
//Установить текст контрола
bool TINYDialog::SetItemText(LPCWSTR text,UINT id)
{
	if(!SetDlgItemText(_hwnd,id,text)) return false;
	return true;
}
//Получить длину текста контрола
int TINYDialog::GetItemTextLen(UINT id)
{
	return GetWindowTextLength(GetDlgItem(_hwnd,id));
}
//Проверить стоит ли галочка
int TINYDialog::GetItemCheck(UINT id)
{
	return IsDlgButtonChecked(_hwnd,id);
}
//Установить галочку
bool TINYDialog::SetItemCheck(UINT id,int check)
{
	if(!CheckDlgButton(_hwnd,id,check)) return false;
	return true;
}
//Получить значение контрола
int TINYDialog::GetItemInt(UINT id)
{
	return GetDlgItemInt(_hwnd,id,0,0);
}
//Установить значение контрола
bool TINYDialog::SetItemInt(int value,UINT id)
{
	if(!SetDlgItemInt(_hwnd,id,value,0)) return false;
	return true;
}

//Оконная функция
INT_PTR CALLBACK TINYDialog::_WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	TINYDialog *dlg=0;
	if(message==WM_INITDIALOG)
	{
		//Получение указателя на экземпляр класса
		dlg=(TINYDialog*)(lparam);
		dlg->_hwnd=hwnd;//Сохранение HWND
		//Сохранение указателя на экземпляр класса в GWL_USERDATA окна
		SetWindowLong(hwnd,GWL_USERDATA,LONG(dlg));
		//Запуск функции обработки сообщений
		dlg->_OnMessage(dlg,message,wparam,lparam);
		return TRUE;
	}
	//Получение указателя на экземпляр класса из GWL_USERDATA
	dlg=(TINYDialog*)TinyGetPointer(hwnd);
	if(dlg)//Проверка указателя
	{
		//Запуск функции обработки сообщений
		dlg->_OnMessage(dlg,message,wparam,lparam);
	}
	return FALSE;
}