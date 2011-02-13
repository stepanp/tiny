//----------------------------
//tiny 2.5
//tinysyslink.cpp - Ссылка
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinysyslink.h"

using namespace tiny;

TINYSysLink::TINYSysLink()
{
	//AddReflectMessage(WM_CTLCOLORSTATIC,&TINYSysLink::OnColor);//WM_CTLCOLORSTATIC
	//AddMessage(WM_LBUTTONUP,&TINYSysLink::OnMouseUp);//WM_LBUTTONUP
	//Настройки по-умолчанию
	_visited=false;//Ссылка не посещена
	_enablevis=true;//Включить посещение ссылки
}

bool TINYSysLink::Create(TINYBaseWnd *parent,LPCWSTR text,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	//Получение класса статика
	WNDCLASS wndc;
	GetClassInfo(GetModuleHandle(0),L"Static",&wndc);
	//Установить курсор в виде руки
	wndc.hCursor=LoadCursor(0,IDC_HAND);
	wndc.lpszClassName=L"TINYSysLink";
	//Зарегистрировать новый класс
	RegisterClass(&wndc);
	//Создать контрол на основе нового класса
	if(!TINYControl::Create(parent,L"TINYSysLink",text,exstyle,style|WS_TABSTOP
		|SS_NOTIFY//Обрабатывать движение мыши
		,x,y,w,h)) return false;
	//Установить подчеркнутый шрифт
	LOGFONT font;
	//Получить LOGFONT стандартного шрифта
	if(!GetObject(HFONT(GetStockObject(DEFAULT_GUI_FONT)),
		sizeof(font),LPVOID(&font))) return false;
	font.lfUnderline=TRUE;//Подчеркнутый
	//Установить шрифт контролу
	if(!SendMessage(_hwnd,WM_SETFONT,
		WPARAM(CreateFontIndirect(&font)),LPARAM(TRUE))) return false;
	return true;
}
//Включить смену цвета при посещении
bool TINYSysLink::EnableVisiting(bool enable)
{
	bool ret=_enablevis;//Запомнить предыдущее состояние
	_enablevis=enable;
	return ret;//Вернуть предыдущее состояние
}
//Узнать включена ли смена цвета при посещении
bool TINYSysLink::GetEnableVisiting() {return _enablevis;}
//Установить посещена ли ссылка
bool TINYSysLink::SetVisited(bool visited)
{
	bool ret=_visited;//Запомнить предыдущее состояние
	_visited=visited;
	//Перерисовать окно
	RedrawWindow(_hwnd,0,0,RDW_INVALIDATE);
	return ret;//Вернуть предыдущее состояние
}
//Узнать посещена ли ссылка
bool TINYSysLink::GetVisited() {return _visited;}

//Обработчики сообщений
//WM_CTLCOLORSTATIC
LRESULT TINYSysLink::OnColor(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	if(wnd==this)//Устанавливать только для текущего контрола
	{
		//Изменить цвет шрифта и фона для ссылки
		TINYDC dc;
		dc.Attach(HDC(wparam));
		//Цвет текста
		if(_visited) dc.SetTextColor(RGB(128,0,128));//Цвет посещенной ссылки(purple)
		else dc.SetTextColor(GetSysColor(COLOR_HOTLIGHT));//Обычный цвет сылки
		dc.SetBkColor(GetSysColor(COLOR_BTNFACE));//Цвет фона текста
		TINYBrush brush;
		brush.CreateSysColorBrush(COLOR_BTNFACE);//Цвет фона
		return LRESULT(brush.GetHBRUSH());
	}else return 0;
}
//WM_LBUTTONUP
LRESULT TINYSysLink::OnMouseUp(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	//Если посещение ссылки включено
	//то изменить цвет ссылки
	if(_enablevis) _visited=true;
	//Перерисовать окно
	RedrawWindow(_hwnd,0,0,RDW_INVALIDATE);
	return 0;
}