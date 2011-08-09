//------------------------------------
//tiny 2.5
//tinybasewnd.cpp - Базовой класс окон
//© 2009-2010 Stepan Prokofjev
//------------------------------------

#include "tinybasewnd.h"

using namespace tiny;

TINYBaseWnd::TINYBaseWnd()
{
	//Инитиализация свойств
	proptext.Init(this,&TINYBaseWnd::SetText,&TINYBaseWnd::GetText);
	propx.Init(this,&TINYBaseWnd::SetX,&TINYBaseWnd::GetX);
	propy.Init(this,&TINYBaseWnd::SetY,&TINYBaseWnd::GetY);
	propw.Init(this,&TINYBaseWnd::SetW,&TINYBaseWnd::GetW);
	proph.Init(this,&TINYBaseWnd::SetH,&TINYBaseWnd::GetH);
	propicon.Init(this,&TINYBaseWnd::SetIcon,&TINYBaseWnd::GetIcon);
	propsmicon.Init(this,&TINYBaseWnd::SetSmallIcon,&TINYBaseWnd::GetSmallIcon);
	//Стили
	proptabstop.Init(this,WS_TABSTOP,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propvscroll.Init(this,WS_VSCROLL,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	prophscroll.Init(this,WS_HSCROLL,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propclientedge.Init(this,WS_EX_CLIENTEDGE,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	propstaticedge.Init(this,WS_EX_STATICEDGE,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	propwindowedge.Init(this,WS_EX_WINDOWEDGE,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	proptransparent.Init(this,WS_EX_TRANSPARENT,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	propacceptfiles.Init(this,WS_EX_ACCEPTFILES,&TINYBaseWnd::SetExStyle,&TINYBaseWnd::GetExStyle);
	//Стандартный цвет окна
	propbkcolor=GetSysColor(COLOR_BTNFACE);

	_isctrl=false;//Не отнаследован от TINYControl
}

//Получить HWND окна
HWND TINYBaseWnd::GetHWND() {return _hwnd;}
//Получить акселератор
HACCEL TINYBaseWnd::GetAccel() {return _acc;}
//Установить акселератор
bool TINYBaseWnd::SetAccel(HACCEL acc)
{
	if(!acc) return false;
	_acc=acc;
	return true;
}
//Создание окна
bool TINYBaseWnd::Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
				HICON icon,HCURSOR cursor,DWORD exstyle,DWORD style,UINT wndstyle,
				int x,int y,int w,int h)
{
	WNDCLASSEX wndc;
	wndc.lpszClassName=classname;//Название класса
	wndc.cbSize=sizeof(WNDCLASSEX);
	wndc.lpfnWndProc=WNDPROC(_WndProc);//Оконная процедура
	wndc.cbClsExtra=0;
	wndc.cbWndExtra=0;
	wndc.hbrBackground=0;
	wndc.hInstance=GetModuleHandle(0);
	wndc.hCursor=cursor;//Курсор
	wndc.style=wndstyle;//Стиль окна
	//Установка иконки
	wndc.hIcon=icon;
	wndc.hIconSm=0;
	//Установка меню
	wndc.lpszMenuName=0;
	//Регистрация класса окна
	RegisterClassEx(&wndc);
	//Проверка указателя на класс родительского окна
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();
	//Создание окна
	_hwnd=CreateWindowEx(exstyle,classname,text,
	style|WS_CLIPCHILDREN,x,y,w,h,
	hparent,0,GetModuleHandle(0),
	this/*Передача указателя на экземпляр класса в оконную функцию*/);
	if(!_hwnd) return false;
	return true;
}
//Связать с HWND
bool TINYBaseWnd::Attach(HWND hwnd)
{
	if(!hwnd) return false;
	_hwnd=hwnd;
	//Сохранение указателя на экземпляр класса
	SetWindowLong(_hwnd,GWL_USERDATA,LONG(this));
	return true;
}
//Если класс отнаследован от TINYControl возврващает true, иначе false
bool TINYBaseWnd::IsCtrl() {return _isctrl;}

//Функции окна
//Уничтожить окно
bool TINYBaseWnd::Destroy()
{
	if(!DestroyWindow(_hwnd)) return false;
	return true;
}
//Показать окно
bool TINYBaseWnd::Show(int ncmd)
{
	if(!ShowWindow(_hwnd,ncmd)) return false;
	return true;
}
//Обновить размеры клиентской области
bool TINYBaseWnd::Update()
{
	if(!UpdateWindow(_hwnd)) return false;
	return true;
}
//Обновить окно
bool TINYBaseWnd::Redraw(UINT flags)
{
	return Redraw(0,0,flags);
}
bool TINYBaseWnd::Redraw(RECT *uprect,//Область для обновления
		HRGN uprgn,//Регион для обновления
		UINT flags)
{
	if(!RedrawWindow(_hwnd,uprect,uprgn,flags)) return false;
	return true;
}
//Установить текст окна
bool TINYBaseWnd::SetText(TINYStr text)
{
	if(!SetWindowText(_hwnd,text)) return false;
	return true;
}
//Получить текст окна
TINYStr TINYBaseWnd::GetText()
{
	wchar_t *text=new wchar_t[GetTextLen()+1];
	GetWindowText(_hwnd,text,GetTextLen()+1);
	TINYStr str=text;
	delete[] text;
	return str;
}
//Получить длину текста окна
int TINYBaseWnd::GetTextLen()
{
	return GetWindowTextLength(_hwnd);	
}
//Получить указатель на класс родительского окна
TINYBaseWnd* TINYBaseWnd::GetParent()
{
	return TinyGetPointer(::GetParent(_hwnd));
}
//Установить родительское окно
bool TINYBaseWnd::SetParent(TINYBaseWnd* parent)
{
	HWND hparent;
	if(!parent) hparent=0;
	else hparent=parent->GetHWND();
	if(!::SetParent(_hwnd,hparent)) return false;
	return true;
}
//Получить название класса
TINYStr TINYBaseWnd::GetClassName()
{
	wchar_t* text=new wchar_t[MAX_PATH];
	//Получить название класса
	::GetClassName(_hwnd,text,MAX_PATH);
	TINYStr str=text;
	delete[] text;
	return str;
}

//Функции для работы со стилями
//Добавить стиль
bool TINYBaseWnd::AddStyle(DWORD style)
{
	return SetStyle(GetStyle()|style);
}
//Удалить стиль
bool TINYBaseWnd::DelStyle(DWORD style)
{
	return SetStyle(GetStyle()&~style);
}
//Добавить расширеный стиль
bool TINYBaseWnd::AddExStyle(DWORD style)
{
	return SetExStyle(GetExStyle()|style);
}
//Удалить расширеный стиль
bool TINYBaseWnd::DelExStyle(DWORD style)
{
	return SetExStyle(GetExStyle()&~style);
}
//Установить стиль
bool TINYBaseWnd::SetStyle(DWORD style)
{
	if(!SetWindowLong(_hwnd,GWL_STYLE,style)) return false;
	return true;
}
//Получить стиль
DWORD TINYBaseWnd::GetStyle()
{
	return GetWindowLong(_hwnd,GWL_STYLE);
}
//Установить расширеный стиль
bool TINYBaseWnd::SetExStyle(DWORD style)
{
	if(!SetWindowLong(_hwnd,GWL_EXSTYLE,style)) return false;
	return true;
}
//Получить расширеный стиль
DWORD TINYBaseWnd::GetExStyle()
{
	return GetWindowLong(_hwnd,GWL_EXSTYLE);
}

//Функции для работы с иконкам
//Установить большую иконку
bool TINYBaseWnd::SetIcon(TINYIcon icon)
{
	//Устанавливаем большую иконку
	SendMessage(_hwnd,WM_SETICON,ICON_BIG,LPARAM(icon.GetHICON()));
	return true;
}
//Установить маленькую иконку
bool TINYBaseWnd::SetSmallIcon(TINYIcon icon)
{
	//Устанавливаем маленькую иконку
	SendMessage(_hwnd,WM_SETICON,ICON_SMALL,LPARAM(icon.GetHICON()));
	return true;
}
//Получить большую иконку
TINYIcon TINYBaseWnd::GetIcon()
{
	//Получение иконки
	HICON hicon=HICON(SendMessage(_hwnd,WM_GETICON,ICON_BIG,0));
	//Если иконки нет, то получение иконки из класса окна
	if(!hicon)
	{
		//Получение информации о классе
		WNDCLASSEX wndc;
		GetClassInfoEx(GetModuleHandle(0),GetClassName(),&wndc);
		//Получение иконки
		hicon=wndc.hIcon;
	}
	TINYIcon icon;
	icon.Attach(hicon);
	return icon;
}
//Получить маленькую иконку
TINYIcon TINYBaseWnd::GetSmallIcon()
{
	//Получение иконки
	HICON hicon=HICON(SendMessage(_hwnd,WM_GETICON,ICON_SMALL,0));
	//Если иконки нет, то получение иконки из класса окна
	if(!hicon)
	{
		//Получение информации о классе
		WNDCLASSEX wndc;
		GetClassInfoEx(GetModuleHandle(0),GetClassName(),&wndc);
		//Получение иконки
		hicon=wndc.hIconSm;
	}
	TINYIcon icon;
	icon.Attach(hicon);
	return icon;
}

//Функции для работы с положением и размерами окна
//Получить область окна
TINYRect TINYBaseWnd::GetRect()
{
	return TINYRect(GetX(),GetY(),GetW(),GetH());
}
//Получить клиентскую область окна
TINYRect TINYBaseWnd::GetClientRect()
{
	RECT rect;
	::GetClientRect(_hwnd,&rect);
	return rect;
}
//Установить размеры окна
bool TINYBaseWnd::SetSize(int w,int h)
{
	if(!SetWindowPos(_hwnd,0,0,0,w,h,
		SWP_NOMOVE|SWP_NOZORDER)) return false;
	return true;
}
//Установить ширину
bool TINYBaseWnd::SetW(int w)
{
	return SetSize(w,GetH());
}
//Установить высоту
bool TINYBaseWnd::SetH(int h)
{
	return SetSize(GetW(),h);
}
//Получить ширину
int TINYBaseWnd::GetW()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	return rect.right-rect.left;
}
//Получить высоту
int TINYBaseWnd::GetH()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	return rect.bottom-rect.top;
}
//Передвинуть окно
bool TINYBaseWnd::Move(int x,int y)
{
	if(!SetWindowPos(_hwnd,0,x,y,0,0,
		SWP_NOSIZE|SWP_NOZORDER)) return false;
	return true;
}
//Установить X
bool TINYBaseWnd::SetX(int x)
{
	return Move(x,GetY());
}
//Установить Y
bool TINYBaseWnd::SetY(int y)
{
	return Move(GetX(),y);
}
//Получить Х
int TINYBaseWnd::GetX()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	//Если у окна есть родитель,
	//то преобразовать координаты
	TINYBaseWnd* parent=GetParent();
	if(parent)
	{
		POINT point;
		point.x=rect.left;
		point.y=rect.top;
		ScreenToClient(parent->GetHWND(),&point);	
		return point.x;
	}
	return rect.left;
}
//Получить Y
int TINYBaseWnd::GetY()
{
	RECT rect;
	GetWindowRect(this->GetHWND(),&rect);
	//Если у окна есть родитель,
	//то преобразовать координаты
	TINYBaseWnd* parent=GetParent();
	if(parent)
	{
		POINT point;
		point.x=rect.left;
		point.y=rect.top;
		ScreenToClient(parent->GetHWND(),&point);	
		return point.y;
	}
	return rect.top;
}

//При срабатывании таймера окну приходит сообщение WM_TIMER
//Запустить таймер
bool TINYBaseWnd::StartTimer(UINT id,UINT time)
{
	if(!SetTimer(_hwnd,id,time,0)) return false;
	return true;
}
//Остановить таймер
bool TINYBaseWnd::StopTimer(UINT id)
{
	if(!KillTimer(_hwnd,id)) return false;
	return true;
}
//На передний план
bool TINYBaseWnd::Top()
{
	if(!SetWindowPos(_hwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE)) return false;
	return true;
}
//На задний план
bool TINYBaseWnd::Bottom()
{
	if(!SetWindowPos(_hwnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE)) return false;
	return true;
}
//Установить z-положение
bool TINYBaseWnd::SetZOrder(TINYBaseWnd* wndafter)
{
	if(!wndafter) return false;
	if(!SetWindowPos(_hwnd,wndafter->GetHWND(),
		0,0,0,0,SWP_NOMOVE|SWP_NOSIZE)) return false;
	return true;
}

TINYBaseWnd::operator HWND() {return GetHWND();}

//Оконная функция
LRESULT CALLBACK TINYBaseWnd::_WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	TINYBaseWnd *wnd=0;
	if(message==WM_NCCREATE)
	{
		//Получение указателя на экземпляр класса из LPCREATESTRUCT
		wnd=(TINYBaseWnd*)LPCREATESTRUCT(lparam)->lpCreateParams;
		if(wnd)
		{
			wnd->_hwnd=hwnd;//Сохранение HWND
			//Сохранение указателя на экземпляр класса в GWL_USERDATA окна
			SetWindowLong(hwnd,GWL_USERDATA,LONG(wnd));
			//Запуск функции обработки сообщений
			wnd->_OnMessage(wnd,message,wparam,lparam);
		}
	}
	//Получение указателя на экземпляр класса из GWL_USERDATA
	wnd=TinyGetPointer(hwnd);
	if(wnd)//Проверка указателя
	{
		//Запуск функции обработки сообщений
		LRESULT result=wnd->_OnMessage(wnd,message,wparam,lparam);
		//Если result не равен 0 то вернуть result
		if(result) return result;
	}
	return DefWindowProc(hwnd,message,wparam,lparam);
}

//Функция обработки сообщений
LRESULT TINYBaseWnd::_OnMessage(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	//Параметры сообщения
	TINYMSGPARAMS msg;
	msg.code=message;
	msg.wparam=wparam;
	msg.lparam=lparam;
	//Возвращаемое значение
	LRESULT ret=0;

	//---------------------------
	//Обработка reflect-сообщений
	//---------------------------
	TINYBaseWnd* rwnd=0;//Указатель на окно, от которого пришло reflect-сообщение
	switch(message)
	{
	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
	case WM_VKEYTOITEM:
	case WM_CHARTOITEM:
	case WM_HSCROLL:
	case WM_VSCROLL:
		//Получить указатель из lparam
		rwnd=TinyGetPointer(HWND(lparam));
		break;
	case WM_DRAWITEM:
	case WM_MEASUREITEM:
	case WM_COMPAREITEM:
	case WM_DELETEITEM:
		//Получить указатель по id из wparam
		if(wparam) rwnd=TinyGetPointer(GetDlgItem(*wnd,wparam));
		break;
	case WM_PARENTNOTIFY:
		//Получить указатель из lparam
		//если wparam равен WM_CREATE или WM_DESTROY
		if(LOWORD(wparam)==WM_CREATE||WM_DESTROY) rwnd=TinyGetPointer(HWND(lparam));
		break;
	}

	if(rwnd)
	{
		//Вызов обработчика кастомной обработки сообщений
		ret=rwnd->_oncustommsg(rwnd,TINYParams(&msg));
		//Если вернул не 0, вернуть значение
		if(ret) return ret;

		//Вызов обработчика сообщения из карты
		return rwnd->onmessage(rwnd,message,TINYParams(&msg));	
	}

	//Вызов обработчика кастомной обработки сообщений
	ret=_oncustommsg(wnd,TINYParams(&msg));
	//Если вернул не 0, вернуть значение
	if(ret) return ret;

	//Вызов обработчика сообщения из карты
	ret=onmessage(wnd,message,TINYParams(&msg));
	if(ret) return ret;

	//----------------------------
	//Обработка основных сообщений
	//----------------------------
	switch(message)
	{
	case WM_CREATE:
		return oncreate(wnd,0);
	case WM_DESTROY:
		return ondestroy(wnd,0);
	case WM_SIZE:
		return onsize(wnd,TINYParams(&msg));
	case WM_PRINT:
	case WM_PAINT:
	{
		//-------------------
		//Обработка отрисовки
		//-------------------

		//Если обработчик onpaint не задан - не обрабатывать
		if(!onpaint.IsConnected()) return 0;

		TINYDBDC dc;
		//Если в wparam пришло HDC, то приаттачить его к dc
		if(wparam) dc.Attach(HDC(wparam));
		//Иначе вызвать BeginPaint
		else dc.BeginPaint(*wnd);

		LRESULT ret=0;//Возвращаемое значение

		//Если двойная буферизция включена
		if(propdoublebuf)
		{
			//Включить двойную буферизацию
			dc.InitDoubleBuffer();

			//Вызвать обработчик onpaint
			ret=onpaint(wnd,TINYParams(dc.GetMemDC())/*Указатель на задний буффер*/);

			//Нарисовать задний буфер		
			dc.DrawDoubleBuffer();
		}else{
			//Если не включена

			//Вызвать обработчик onpaint
			ret=onpaint(wnd,TINYParams(&dc)/*Укзатель на DC*/);
		}
		
		//Если вызван BeginPaint, закончить рисование
		if(wparam) dc.EndPaint();
		//Отпустить DC
		else dc.Release(*this);

		return ret;
	}
	case WM_ERASEBKGND:
	{
		//Если это контрол, то фон по умолчанию
		if(wnd->IsCtrl()) return 0;

		//Если обработчик onpaint задан, то не закрашивать фон
		if(onpaint.IsConnected()) return TRUE;

		TINYDC dc;
		//Получить DC
		dc.Attach(HDC(wparam));

		//Закрасить фон цветом propbkcolor
		TINYBrush brush(propbkcolor);
		dc.FillRect(GetClientRect(),&brush);

		//Очистка
		dc.Release(*wnd);
		brush.Delete();
		return TRUE;
	}
	case WM_MOUSEMOVE:
		return onmousemove(wnd,0);
	case WM_LBUTTONDOWN:
		return onlbtndown(wnd,0);
	case WM_LBUTTONUP:
		return onlbtnup(wnd,0);
	case WM_TIMER:
		return ontimer(wnd,TINYParams(wparam));
	case WM_COMMAND:
	{
		//----------------
		//Обработка команд
		//----------------

		UINT code=HIWORD(wparam);//Код команды
		UINT id=LOWORD(wparam);//Id контрола

		if(lparam==0)
		{
			//---------------------
			//Обработка команд меню
			//---------------------
			if(HIWORD(wparam)==0) onmenu(wnd,id,0);

			//------------------------------
			//Обработка команд акселераторов
			//------------------------------
			if(HIWORD(wparam)==1) onacc(wnd,id,0);

		}else{
			//--------------------------
			//Обработка остальных команд
			//--------------------------

			//Получение указателя на контрол, от которого пришла команда
			TINYBaseWnd* ctrl=TinyGetPointer(HWND(lparam));

			if(ctrl)
			{
				//Параметры команды
				TINYMSGPARAMS cmd;
				cmd.code=code;//Код команды
				cmd.wparam=0;
				cmd.lparam=0;

				//Вызов обработчика кастомной обработки команд
				ctrl->_oncustomcmd(ctrl,TINYParams(&cmd));

				//Вызов обработчика команды из карты
				ctrl->oncommand(ctrl,code,0);
			}
		}		
		return 0;
	}
	case WM_NOTIFY:
	{
		//---------------------
		//Обработка нотификаций
		//---------------------

		//Указатель на контрол, от которого пришла нотификация
		TINYBaseWnd* ctrl=TinyGetPointer(LPNMHDR(lparam)->hwndFrom);
		UINT code=LPNMHDR(lparam)->code;//Код нотификации

		if(ctrl) 
		{
			//Параметры нотификации
			TINYMSGPARAMS ntf;
			ntf.code=code;//Код нотификации
			ntf.wparam=0;
			ntf.lparam=lparam;

			//Вызов обработчика кастомной обработки нотификаций
			ret=ctrl->_oncustomntf(ctrl,TINYParams(&ntf));
			if(ret) return ret;

			//Вызов обработчика нотификации из карты
			return ctrl->onnotify(ctrl,code,TINYParams(lparam));
		}
	}
	}
	return 0;
}

//Получить TINYBaseWnd* из HWND
TINYBaseWnd* tiny::TinyGetPointer(HWND hwnd)
{
	if(!hwnd) return 0;
	//Получение TINYBaseWnd* из поля UserData окна
	return (TINYBaseWnd*)GetWindowLong(hwnd,GWL_USERDATA);
}