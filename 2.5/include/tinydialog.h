//----------------------------
//tiny 2.5
//tinydialog.h - Диалог
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYDialog: public TINYBaseWnd
{
public:
	bool Create(TINYBaseWnd *parent,UINT dialog);
	HWND GetItemHWND(UINT id);//Получить HWND контрола
	void End();//Закрыть диалог
	TINYStr GetItemText(UINT id);//Получить текст контрола
	bool SetItemText(LPCWSTR text,UINT id);//Установить текст контрола
	int GetItemTextLen(UINT id);//Получить длину текста контрола
	int GetItemCheck(UINT id);//Проверить стоит ли галочка
	bool SetItemCheck(UINT id,int check);//Установить галочку
	int GetItemInt(UINT id);//Получить значение контрола
	bool SetItemInt(int value,UINT id);//Установить значение контрола
protected:
	//Оконная функция
	static INT_PTR CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
};

};