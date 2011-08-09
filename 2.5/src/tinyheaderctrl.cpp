//-------------------------------
//tiny 2.5
//tinybuttons.cpp - Хидер контрол
//© 2009-2010 Stepan Prokofjev
//-------------------------------

#include "tinyheaderctrl.h"

using namespace tiny;

bool TINYHeaderCtrl::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	return TINYControlEx::Create(parent,ICC_LISTVIEW_CLASSES,WC_HEADER,
		0,exstyle,
		HDS_FULLDRAG|//Плавное перетаскивание
		style,x,y,w,h);

}
//Вставить итем
int TINYHeaderCtrl::InsertItem(int index,LPCWSTR text,int w,int fmt)
{
	int nindex;
	//Определение индекса
	if(index==-1) nindex=GetItemCount();
	else nindex=index;
	HDITEM hdi;
	hdi.mask=HDI_TEXT|HDI_WIDTH|HDI_FORMAT;
	hdi.pszText=LPWSTR(text);
	hdi.cxy=w;
	hdi.fmt=fmt;
	return Header_InsertItem(_hwnd,nindex,&hdi);
}
//Добавить итем
int TINYHeaderCtrl::AddItem(LPCWSTR text,int w,int fmt)
{
	return InsertItem(-1,text,w,fmt);
}
//Установить текст
bool TINYHeaderCtrl::SetItemText(int index,LPCWSTR text)
{
	HDITEM hdi;
	hdi.mask=HDI_TEXT;
	hdi.pszText=LPWSTR(text);
	if(!Header_SetItem(_hwnd,index,&hdi)) return false;
	return true;
}
//Установить индекс картинки
bool TINYHeaderCtrl::SetItemImage(int index,int image)
{
	HDITEM hdi;
	hdi.mask=HDI_IMAGE;
	hdi.iImage=image;
	if(!Header_SetItem(_hwnd,index,&hdi)) return false;
	return true;
}
//Установить значение итема
bool TINYHeaderCtrl::SetItemData(int index,LPARAM data)
{
	HDITEM hdi;
	hdi.mask=HDI_LPARAM;
	hdi.lParam=data;
	if(!Header_SetItem(_hwnd,index,&hdi)) return false;
	return true;

}
//Установить формат итема
bool TINYHeaderCtrl::SetItemFormat(int index,int fmt)
{
	HDITEM hdi;
	hdi.mask=HDI_FORMAT;
	hdi.fmt=fmt;
	if(!Header_SetItem(_hwnd,index,&hdi)) return false;
	return true;

}
//Получить текст итема
TINYStr TINYHeaderCtrl::GetItemText(int index)
{
	wchar_t *text=new wchar_t[MAX_PATH];
	HDITEM hdi;
	hdi.mask=HDI_TEXT;
	hdi.pszText=text;
	hdi.cchTextMax=MAX_PATH;
	Header_GetItem(_hwnd,index,&hdi);
	TINYStr str=text;
	delete[] text;
	return str;

}
//Получить индекс картинки
int TINYHeaderCtrl::GetItemImage(int index)
{
	HDITEM hdi;
	hdi.mask=HDI_IMAGE;
	if(!Header_GetItem(_hwnd,index,&hdi)) return false;
	return hdi.iImage;
}
//Получить значение итема
LPARAM TINYHeaderCtrl::GetItemData(int index)
{
	HDITEM hdi;
	hdi.mask=HDI_LPARAM;
	if(!Header_GetItem(_hwnd,index,&hdi)) return false;
	return hdi.lParam;
}
//Получить формат итема
int TINYHeaderCtrl::GetItemFormat(int index)
{
	HDITEM hdi;
	hdi.mask=HDI_FORMAT;
	if(!Header_GetItem(_hwnd,index,&hdi)) return false;
	return hdi.fmt;
}
//Получить кол-во итемов
int TINYHeaderCtrl::GetItemCount()
{
	return Header_GetItemCount(_hwnd);
}
//Установить имаджлист
bool TINYHeaderCtrl::SetImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!Header_SetImageList(_hwnd,hlist)) return false;
	return true;
}