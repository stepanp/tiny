//----------------------------
//tiny 2.5
//tinylistview.cpp - Листвью
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinylistview.h"

using namespace tiny;

//Прикрепить колонки в режиме LVS_REPORT
bool TINYListView::_AttachHeader()
{
	DWORD style=GetWindowLong(_hwnd,GWL_STYLE);
	DWORD nstyle=style&~LVS_NOCOLUMNHEADER;
	//Если есть стиль LVS_REPORT и нет стиля LVS_NOCOLUMNHEADER
	if(style==(nstyle|LVS_REPORT))
	{
		//Прикрепить хидер к классу TINYHeaderCtrl
		if(!_header.Attach(ListView_GetHeader(_hwnd))) return false;
	}
	return true;
}

bool TINYListView::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	if(!TINYControlEx::Create(parent,ICC_LISTVIEW_CLASSES,
		WC_LISTVIEW,0,exstyle,style,x,y,w,h)) return false;
	return _AttachHeader();
}
bool TINYListView::Attach(HWND hwnd)
{
	if(!TINYControlEx::Attach(hwnd)) return false;
	return _AttachHeader();
}
//Получить хидер(колонки)
TINYHeaderCtrl* TINYListView::GetHeader() {return &_header;}
//Установить расширенный стиль
bool TINYListView::SetExtendedStyle(DWORD style)
{
	if(!ListView_SetExtendedListViewStyle(_hwnd,style)) return false;
	return true;
}
//Вставить колонку
int TINYListView::InsertColumn(int index,LPCWSTR text,int w,int fmt/*Формат*/)
{
	int nindex;
	//Получение индеса
	if(index==-1) nindex=_header.GetItemCount();
	else nindex=index;	
	LVCOLUMN col;
	col.mask=LVCF_FMT|LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
	col.iSubItem=nindex;
	col.pszText=LPWSTR(text);
	col.cx=w;
	col.fmt=fmt;
	return ListView_InsertColumn(_hwnd,nindex,&col);
}
//Добавить колонку
int TINYListView::AddColumn(LPCWSTR text,int w,int fmt/*Формат*/)
{
	return InsertColumn(-1,text,w,fmt);
}
//Удалить колонку
bool TINYListView::DeleteColumn(int index)
{
	if(!ListView_DeleteColumn(_hwnd,index)) return false;
	return true;
}
//Установить ширину колонки
bool TINYListView::SetColumnW(int index,int w)
{
	if(!ListView_SetColumnWidth(_hwnd,index,w)) return false;
	return true;
}
//Вставить итем
int TINYListView::InsertItem(int index,LPCWSTR text,int image)
{
	int nindex;
	//Получение индекса
	if(index==-1) nindex=GetItemCount();
	else nindex=index;
	LVITEM lvi;
	lvi.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	lvi.iItem=nindex;
	lvi.pszText=LPWSTR(text);
	lvi.iImage=image;
	lvi.iSubItem=0;
	return ListView_InsertItem(_hwnd,&lvi);
}
//Добавить итем
int TINYListView::AddItem(LPCWSTR text,int image)
{
	return InsertItem(-1,text,image);
}
//Удалить итем
bool TINYListView::DeleteItem(int index)
{
	if(!ListView_DeleteItem(_hwnd,index)) return false;
	return true;
}
//Установить субитем
//Впринципе тоже самое что и SetItemText :)
bool TINYListView::SetSubItem(int index,int subitem,LPCWSTR text)
{
	return SetItemText(index,subitem,text);
}
//Установить текст итема
bool TINYListView::SetItemText(int index,int subitem,LPCWSTR text)
{
	LVITEM lvi;
	lvi.mask=LVIF_TEXT;
	lvi.iItem=index;
	lvi.iSubItem=subitem;
	lvi.pszText=LPWSTR(text);
	if(ListView_SetItem(_hwnd,&lvi)==-1) return false;
	return true;
}
//Установить индекс картинки
bool TINYListView::SetItemImage(int index,int subitem,int image)
{
	LVITEM lvi;
	lvi.mask=LVIF_IMAGE;
	lvi.iItem=index;
	lvi.iSubItem=subitem;
	lvi.iImage=image;
	if(ListView_SetItem(_hwnd,&lvi)==-1) return false;
	return true;
}
//Установить значение итема
bool TINYListView::SetItemData(int index,int subitem,LPARAM data)
{
	LVITEM lvi;
	lvi.mask=LVIF_PARAM;
	lvi.iItem=index;
	lvi.iSubItem=subitem;
	lvi.lParam=data;
	if(ListView_SetItem(_hwnd,&lvi)==-1) return false;
	return true;
}
//Установить состояние итема
bool TINYListView::SetItemState(int index,UINT state)
{
	LVITEM lvi;
	lvi.mask=LVIF_STATE;
	lvi.iItem=index;
	lvi.iSubItem=0;
	lvi.state=state;
	lvi.stateMask=LVIS_CUT|LVIS_DROPHILITED|LVIS_FOCUSED|LVIS_SELECTED;
	if(ListView_SetItem(_hwnd,&lvi)==-1) return false;
	return true;
}
//Получить текст итема
TINYStr TINYListView::GetItemText(int index,int subitem)
{	
	wchar_t *text=new wchar_t[MAX_PATH];
	LVITEM lvi;
	lvi.mask=LVIF_TEXT;
	lvi.iItem=index;
	lvi.iSubItem=subitem;
	lvi.pszText=text;
	lvi.cchTextMax=MAX_PATH;
	SendMessage(_hwnd,LVM_GETITEMTEXT,index,LPARAM(&lvi));
	TINYStr str=text;
	delete[] text;
	return str;
}
//Получить индекс картинки
int TINYListView::GetItemImage(int index,int subitem)
{
	LVITEM lvi;
	lvi.mask=LVIF_IMAGE;
	lvi.iItem=index;
	lvi.iSubItem=subitem;
	ListView_GetItem(_hwnd,&lvi);
	return lvi.iImage;
}
//Получить значение итема
LPARAM TINYListView::GetItemData(int index,int subitem)
{
	LVITEM lvi;
	lvi.mask=LVIF_PARAM;
	lvi.iItem=index;
	lvi.iSubItem=subitem;
	ListView_GetItem(_hwnd,&lvi);
	return lvi.lParam;
}
//Получить состояние итема
UINT TINYListView::GetItemState(int index)
{
	return ListView_GetItemState(_hwnd,index,
		LVIS_CUT|LVIS_DROPHILITED|LVIS_FOCUSED|LVIS_SELECTED);
}
//Получить кол-во итемов
int TINYListView::GetItemCount()
{
	return ListView_GetItemCount(_hwnd);
}
//Установить имаджлист
bool TINYListView::SetImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!ListView_SetImageList(_hwnd,hlist,LVSIL_NORMAL)) return false;
	return true;
}
//Установить имаджлист для маленьких иконок
bool TINYListView::SetSmallImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!ListView_SetImageList(_hwnd,hlist,LVSIL_SMALL)) return false;
	return true;
}