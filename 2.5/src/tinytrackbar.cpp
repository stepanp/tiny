//----------------------------
//tiny 2.5
//tinytrackbar.cpp - Трекбар
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinytrackbar.h"

using namespace tiny;

bool TINYTrackBar::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	if(!TINYControlEx::Create(parent,0,TRACKBAR_CLASS,0,exstyle,style,x,y,w,h)) return false;
	//Удалить стиль TBS_BOTH, если он не указан при создании
	if(style!=(style|TBS_BOTH)) DelStyle(TBS_BOTH);
	return true;
}
//Установить позицию
bool TINYTrackBar::SetPos(int pos)
{
	if(!SendMessage(_hwnd,TBM_SETPOS,WPARAM(TRUE),LPARAM(pos))) return false;
	return true;
}
//Получить позицию
int TINYTrackBar::GetPos()
{
	return SendMessage(_hwnd,TBM_GETPOS,0,0);
}
//Установить минимальную и максимальную позиции
void TINYTrackBar::SetRange(int min,int max)
{
	SendMessage(_hwnd,TBM_SETRANGE,WPARAM(TRUE),MAKELPARAM(min,max));
}
//Получить минимальную позицию
int TINYTrackBar::GetMinRange()
{
	return SendMessage(_hwnd,TBM_GETRANGEMIN,0,0);
}
//Получить максимальную позицию
int TINYTrackBar::GetMaxRange()
{
	return SendMessage(_hwnd,TBM_GETRANGEMAX,0,0);
}
//Установить риску
bool TINYTrackBar::SetTick(int pos)
{
	if(!SendMessage(_hwnd,TBM_SETTIC,0,LPARAM(pos))) return false;
	return true;
}
//Получить позицию риски
int TINYTrackBar::GetTick(int index)
{
	return SendMessage(_hwnd,TBM_GETTIC,WPARAM(index),0);
}
//Установить частоту рисок на трекбаре
bool TINYTrackBar::SetTickFrequency(int freq)
{
	if(!SendMessage(_hwnd,TBM_SETTICFREQ,WPARAM(freq),0)) return false;
	return true;
}
//Установить боковые контролы
bool TINYTrackBar::SetBuddies(TINYBaseWnd *left,TINYBaseWnd *right)
{
	if((!left)||(!right)) return false;
	//Установить левый контрол
	SendMessage(_hwnd,TBM_SETBUDDY,WPARAM(TRUE),LPARAM(left->GetHWND()));
	//Установить правый контрол
	SendMessage(_hwnd,TBM_SETBUDDY,WPARAM(FALSE),LPARAM(right->GetHWND()));
	return true;
}
//Получить левый контрол
TINYBaseWnd* TINYTrackBar::GetLeftBuddy()
{
	HWND hwnd=HWND(SendMessage(_hwnd,TBM_GETBUDDY,WPARAM(TRUE),0));
	if(!hwnd) return 0;
	return TinyGetPointer(hwnd);
}
//Получить правый контрол
TINYBaseWnd* TINYTrackBar::GetRightBuddy()
{
	HWND hwnd=HWND(SendMessage(_hwnd,TBM_GETBUDDY,WPARAM(FALSE),0));
	if(!hwnd) return 0;
	return TinyGetPointer(hwnd);
}