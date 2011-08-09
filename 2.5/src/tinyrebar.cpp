//----------------------------
//tiny 2.5
//tinyrebar.cpp - Ребар
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinyrebar.h"

using namespace tiny;


bool TINYReBar::Create(TINYBaseWnd *parent)
{
	return TINYControlEx::Create(parent,ICC_COOL_CLASSES,REBARCLASSNAME,0,0,
		CCS_NOPARENTALIGN|//Не растягивать
		CCS_NODIVIDER|//Без полоски сверху
		WS_CLIPCHILDREN|//Чтобы не мерцало
		RBS_BANDBORDERS,//Сепараторы между бандами
		0,0,0,0);
}
//Вcтавить банд
bool TINYReBar::InsertBand(int index,TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h)
{
	//Создание банда
	REBARBANDINFO band;
	band.cbSize=80;//Для работы ребара под ХР
	band.fMask=
		RBBIM_STYLE|
		RBBIM_TEXT|
		RBBIM_CHILD|
		RBBIM_CHILDSIZE|
		RBBIM_SIZE;
	band.fStyle=
		RBBS_CHILDEDGE|//Рамка вокруг контрола
		style;
	band.lpText=LPWSTR(text);
	band.cyMinChild=h;//Минимальная высота
	band.cxMinChild=w;//Минимальная ширина
	band.cx=w;//Ширина
	HWND hchild=child->GetHWND();
	if(!hchild) return false;
	band.hwndChild=hchild;//Контрол в банде
	//Добавление банда в ребар
	if(!SendMessage(_hwnd,RB_INSERTBAND,WPARAM(index),LPARAM(&band))) return false;
	return true;
}
//Добавить банд
bool TINYReBar::AddBand(TINYBaseWnd *child,DWORD style,LPCWSTR text,int w,int h)
{
	return InsertBand(-1,child,style,text,w,h);
}
//Удалить банд
bool TINYReBar::DeleteBand(int index)
{
	if(!SendMessage(_hwnd,RB_DELETEBAND,WPARAM(index),0)) return false;
	return true;
}
//Передвинуть банд
bool TINYReBar::MoveBand(int index,int nindex)
{
	if(!SendMessage(_hwnd,RB_MOVEBAND,WPARAM(index),LPARAM(nindex))) return false;
	return true;
}
//Скрыть/Показать банд
bool TINYReBar::ShowBand(int index,bool show)
{
	if(!SendMessage(_hwnd,RB_SHOWBAND,WPARAM(index),LPARAM(show))) return false;
	return true;
}
//Получить кол-во бандов
int TINYReBar::GetBandCount()
{
	return SendMessage(_hwnd,RB_GETBANDCOUNT,0,0);
}