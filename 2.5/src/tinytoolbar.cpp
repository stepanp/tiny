//----------------------------
//tiny 2.5
//tinytoolbar.cpp - Тулбар
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinytoolbar.h"

using namespace tiny;


TINYToolBar::TINYToolBar()
{
	//Обработчик для всплывающих подсказок
	//AddMessage(WM_NOTIFY,&TINYToolBar::_OnToolTip);
}

bool TINYToolBar::Create(TINYBaseWnd *parent)
{
	return TINYControlEx::Create(parent,ICC_BAR_CLASSES,TOOLBARCLASSNAME,0,0,
		CCS_NOPARENTALIGN|//Не растягивать
		CCS_NODIVIDER|//Без полоски сверху
		CCS_NORESIZE|//Не менять размер автоматически
		TBSTYLE_TRANSPARENT|TBSTYLE_FLAT|//Прозрачный фон	
		TBSTYLE_TOOLTIPS,//Всплывающие подсказки на кнопках
		0,0,0,25);
}
//Установить расширенный стиль
bool TINYToolBar::SetExtendedStyle(DWORD style)
{
	if(!SendMessage(_hwnd,TB_SETEXTENDEDSTYLE,0,LPARAM(style))) return false;
	return true;
}
//Вставить кнопку
bool TINYToolBar::InsertButton(int index,DWORD style,DWORD state,int nimage,
							LPCWSTR text,LPCWSTR tip,UINT id)
{
	//Создание кнопки
	TBBUTTON btn;
	btn.fsState=BYTE(state);
	btn.fsStyle=BYTE(style);
	btn.iBitmap=nimage;
	btn.iString=INT_PTR(text);
	btn.idCommand=id;
	btn.dwData=DWORD_PTR(tip);//Всплывающая подсказка
	//Добавление кнопки
	if(!SendMessage(_hwnd,TB_INSERTBUTTON,WPARAM(index),LPARAM(&btn))) return false;
	return true;
}
//Добавить кнопку
bool TINYToolBar::AddButton(DWORD style,DWORD state,int nimage,LPCWSTR text,LPCWSTR tip,UINT id)
{
	return InsertButton(-1,style,state,nimage,text,tip,id);
}
//Втавить сепаратор
bool TINYToolBar::InsertSeparator(int index)
{
	return InsertButton(index,BTNS_SEP,0,0,0,0,0);
}
//Добавить сепаратор
bool TINYToolBar::AddSeparator()
{
	return InsertSeparator(-1);
}
//Удалить кнопку
bool TINYToolBar::DeleteButton(int index)
{
	if(!SendMessage(_hwnd,TB_DELETEBUTTON,WPARAM(index),0)) return false;
	return true;
}
//Передвинуть кнопку
bool TINYToolBar::MoveButton(int index,int nindex/*Новый индекс кнопки*/)
{
	if(!SendMessage(_hwnd,TB_MOVEBUTTON,WPARAM(index),LPARAM(index))) return false;
	return true;
}
//Установить состояние кнопки
bool TINYToolBar::SetButtonState(int id,DWORD state)
{
	if(!SendMessage(_hwnd,TB_SETSTATE,WPARAM(id),LPARAM(MAKELONG(state,0)))) return false;
	return true;
}
//Получить состояние кнопки
DWORD TINYToolBar::GetButtonState(int id)
{
	return SendMessage(_hwnd,TB_GETSTATE,WPARAM(id),0);
}
//Включить/Выключить кнопку
bool TINYToolBar::EnableButton(int id,bool enable)
{
	if(!SendMessage(_hwnd,TB_ENABLEBUTTON,WPARAM(id),LPARAM(enable))) return false;
	return true;
}
//Показать/Скрыть кнопку
bool TINYToolBar::ShowButton(int id,bool show)
{
	bool ishow=show;
	if(show) ishow=false;
	else ishow=true;
	if(!SendMessage(_hwnd,TB_HIDEBUTTON,WPARAM(id),LPARAM(ishow))) return false;
	return true;
}
//Установить имаджлист
bool TINYToolBar::SetImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!SendMessage(_hwnd,TB_SETIMAGELIST,WPARAM(0),LPARAM(hlist))) return false;
	return true;
}
//Установить имаджлист для подсвеченных кнопок
bool TINYToolBar::SetHotImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!SendMessage(_hwnd,TB_SETHOTIMAGELIST,WPARAM(0),LPARAM(hlist))) return false;
	return true;
}
//Установить имаджлист для отключенных кнопок
bool TINYToolBar::SetDisbaleImageList(TINYImageList *list)
{
	HIMAGELIST hlist;
	if(!list) hlist=0;
	else hlist=list->GetHIMAGELIST();
	if(!SendMessage(_hwnd,TB_SETDISABLEDIMAGELIST,WPARAM(0),LPARAM(hlist))) return false;
	return true;
}
//Установить размер автоматически
void TINYToolBar::AutoSize()
{
	SendMessage(_hwnd,TB_AUTOSIZE,0,0);
}
//Получить кол-во кнопок
int TINYToolBar::GetButtonCount()
{
	return SendMessage(_hwnd,TB_BUTTONCOUNT,0,0);
}
//Получить кнопку
TBBUTTON TINYToolBar::GetButton(int index)
{
	TBBUTTON btn;
	SendMessage(_hwnd,TB_GETBUTTON,WPARAM(index),LPARAM(&btn));
	return btn;
}

//Обработчик для всплывающих подсказок
LRESULT TINYToolBar::_OnToolTip(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	if(LPNMHDR(lparam)->code==TTN_GETDISPINFO)
	{
		LPTOOLTIPTEXT tip=LPTOOLTIPTEXT(lparam);
		tip->hinst=GetModuleHandle(0);
		//Получение id кнопки
		int id=tip->hdr.idFrom;
		//Поиск кнопки с таким id
		for(int i=0;i<GetButtonCount();i++)
		{
			TBBUTTON btn=GetButton(i);
			//Если id совпадают то показать подсказку
			//Для этой кнопки
			if(btn.idCommand==id)
			{
				tip->lpszText=LPWSTR(btn.dwData);	
				break;
			}
		}	
	}
	return 0;
}