//--------------------------------
//tiny 2.5
//tinytrayicon.cpp - Иконка в трее
//© 2009-2010 Stepan Prokofjev
//--------------------------------

#include "tinytrayicon.h"

using namespace tiny;

bool TINYTrayIcon::Create(TINYBaseWnd *parent,HICON icon,LPCWSTR tip,UINT id)
{
	_data.cbSize=sizeof(NOTIFYICONDATA);
	_data.uFlags=NIF_ICON|NIF_TIP|NIF_MESSAGE;
	lstrcpyn(_data.szTip,tip,128);//Копируем подсказку иконки
	_data.hIcon=icon;
	_data.uCallbackMessage=TINY_TRAYICON;//Сообщение от иконки
	_data.uID=id;
	if(!parent) return false;
	_data.hWnd=parent->GetHWND();
	if(!Shell_NotifyIcon(NIM_ADD,&_data)) return false;
	return true;
}
//Убрать иконку из трея
bool TINYTrayIcon::Delete()
{
	if(!Shell_NotifyIcon(NIM_DELETE,&_data)) return false;
	return true;
}
//Изменить иконку иконку
bool TINYTrayIcon::Modify(HICON icon,LPCWSTR tip)
{
	_data.hIcon=icon;
	lstrcpyn(_data.szTip,tip,128);
	if(!Shell_NotifyIcon(NIM_MODIFY,&_data)) return false;
	return true;
}