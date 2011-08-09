//-----------------------------
//tiny 2.5
//tinyimagelist.cpp - Имаджлист
//© 2009-2010 Stepan Prokofjev
//-----------------------------

#include "tinyimagelist.h"

using namespace tiny;

//Получить HIMAGELSIT
HIMAGELIST TINYImageList::GetHIMAGELIST()
{
	return _hlist;
}
bool TINYImageList::Create(DWORD flags,int w,int h)
{
	_hlist=ImageList_Create(w,h,flags,0,0);
	if(_hlist) return false;
	return true;
}
//Добавить иконку
int TINYImageList::AddIcon(HICON icon)
{
	return ImageList_AddIcon(_hlist,icon);
}
//Добавить битмап
int TINYImageList::AddBitmap(HBITMAP bmp)
{
	return ImageList_Add(_hlist,bmp,0);
}
//Добавить битмап с маской
int TINYImageList::AddMasked(HBITMAP bmp,COLORREF mask)
{
	return ImageList_AddMasked(_hlist,bmp,mask);
}
//Удалить картинку
bool TINYImageList::Delete(int index)
{
	if(!ImageList_Remove(_hlist,index)) return false;
	return true;
}
//Получить кол-во картинок
int TINYImageList::GetCount()
{
	return ImageList_GetImageCount(_hlist);
}
//Очистить
bool TINYImageList::Clear()
{
	return Delete(-1);
}
//Получит иконку
HICON TINYImageList::GetIcon(int index)
{
	return ImageList_GetIcon(_hlist,index,ILD_NORMAL);
}