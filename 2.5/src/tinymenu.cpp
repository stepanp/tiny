//----------------------------
//tiny 2.5
//tinymenu.cpp - Меню
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinymenu.h"

using namespace tiny;

//----
//Меню
//----
bool TINYMenu::Create() {return Attach(CreateMenu());}
bool TINYMenu::Create(UINT menu)
{
	if(!menu) return false;
	return Attach(LoadMenu(GetModuleHandle(0),MAKEINTRESOURCE(menu)));	
}
//Создать из HMENU
bool TINYMenu::Attach(HMENU menu)
{
	if(!menu) return false;
	_menu=menu;
	MENUINFO mi;
	mi.cbSize=sizeof(MENUINFO);
	mi.fMask=MIM_MENUDATA;
	mi.dwMenuData=ULONG_PTR(this);//Сохранение указателя на объект класса
	if(!SetMenuInfo(_menu,&mi)) return false;
	return true;
}
//Получить HMENU
HMENU TINYMenu::GetHMENU() {return _menu;}
//Установить меню окну
bool TINYMenu::SetToWindow(TINYBaseWnd *wnd)
{
	if(!wnd) return false;
	if(!SetMenu(wnd->GetHWND(),_menu)) return false;
	return true;
}
//Вставить пункт меню
bool TINYMenu::InsertItem(int index,LPCWSTR text,UINT id,TINYMenu* submenu)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_STRING|MIIM_ID|MIIM_SUBMENU;
	mi.dwTypeData=LPWSTR(text);
	mi.wID=id;
	if(submenu) mi.hSubMenu=submenu->GetHMENU();//Получить HMENU для подменю
	else mi.hSubMenu=0;
	if(!InsertMenuItem(_menu,index,TRUE,&mi)) return false;
	return true;
}
//Добавить пункт меню
bool TINYMenu::AddItem(LPCWSTR text,UINT id,TINYMenu* submenu)
{
	return InsertItem(-1,text,id,submenu);
}
//Удалить пункт меню
bool TINYMenu::DeleteItem(int index)
{
	if(!DeleteMenu(_menu,index,MF_BYPOSITION)) return false;
	return true;
}
//Получить субменю
TINYMenu* TINYMenu::GetSubMenu(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_SUBMENU;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	HMENU menu=mi.hSubMenu;
	//Получение TINYMenu* из HMENU
	MENUINFO mni;
	mni.cbSize=sizeof(MENUINFO);
	mni.fMask=MIM_MENUDATA;
	GetMenuInfo(menu,&mni);
	return (TINYMenu*)(mni.dwMenuData);
}
//Установить субменю
bool TINYMenu::SetSubMenu(int index,TINYMenu* submenu)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_SUBMENU;
	if(submenu)	mi.hSubMenu=submenu->GetHMENU();//Получить HMENU для подменю
	else mi.hSubMenu=0;
	if(!SetMenuItemInfo(_menu,index,TRUE,&mi)) return false;
	return true;
}
//Получить состояние
DWORD TINYMenu::GetItemState(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_STATE;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	return mi.fState;
}
//Установить состояние
bool TINYMenu::SetItemState(int index,DWORD state)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_STATE;
	mi.fState=state;
	if(!SetMenuItemInfo(_menu,index,TRUE,&mi)) return false;
	return true;	
}
//Установить дополнительное значение
bool TINYMenu::SetItemData(int index,LPARAM data)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_DATA;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	mi.dwItemData=ULONG_PTR(data);
	if(!SetMenuItemInfo(_menu,index,TRUE,&mi)) return false;
	return true;
}
//Получить дополнительное значение
LPARAM TINYMenu::GetItemData(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_DATA;
	GetMenuItemInfo(_menu,index,TRUE,&mi);
	return mi.dwItemData;
}


//----------------
//Всплывающее меню
//----------------
bool TINYPopupMenu::Create() {return Attach(CreatePopupMenu());}
//Создать из ресурсов
bool TINYPopupMenu::Create(UINT menu)
{
	if(!menu) return false;
	HMENU tmenu;
	tmenu=LoadMenu(GetModuleHandle(0),MAKEINTRESOURCE(menu));
	tmenu=::GetSubMenu(tmenu,0);//Получить субменю	
	return Attach(tmenu);
}
//Вставить сепаратор
bool TINYPopupMenu::InsertSeparator(int index)
{
	MENUITEMINFO mi;
	mi.cbSize=sizeof(MENUITEMINFO);
	mi.fMask=MIIM_TYPE;
	mi.fType=MFT_SEPARATOR;
	if(!InsertMenuItem(_menu,index,TRUE,&mi)) return false;
	return true;
}
//Добавить сепаратор
bool TINYPopupMenu::AddSeparator() {return InsertSeparator(-1);}
//Задизейблить меню
bool TINYPopupMenu::EnableItem(int index,bool enable)
{
	DWORD state;
	if(enable) state=MFS_ENABLED;
	else state=MFS_DISABLED|MFS_GRAYED;
	return SetItemState(index,state);
}
//Проверить задизейблен ли пункт меню
bool TINYPopupMenu::GetEnableItem(int index)
{
	if(GetItemState(index)&MFS_ENABLED) return true;
	return false;
}
//Поставить галочку
bool TINYPopupMenu::CheckItem(int index,bool check)
{
	DWORD state;
	if(check) state=MFS_CHECKED;
	else state=MFS_UNCHECKED;
	return SetItemState(index,state);
}
//Проверить галочку
bool TINYPopupMenu::GetCheckItem(int index)
{
	if(GetItemState(index)&MFS_CHECKED) return true;
	return false;
}
//Показать меню
bool TINYPopupMenu::Track(TINYBaseWnd *parent,int x,int y)
{
	int nx,ny;
	//Если x и y равны -1
	//То показать меню в позиции курсора
	if((x==-1)&&(y==-1))
	{
		//Получении позиции курсора 
		POINT point;
		GetCursorPos(&point);
		nx=point.x;
		ny=point.y;
	}else{
		nx=x; 
		ny=y;
	}
	if(!parent) return false;
	HWND hparent=parent->GetHWND();	
	if(!TrackPopupMenu(_menu,TPM_LEFTALIGN|TPM_VERTICAL,nx,ny,0,hparent,0)) return false;
	return true;
}