//----------------------------------
//tiny 2.5
//tinybasewnd.h - Базовой класс окон
//© 2009-2010 Stepan Prokofjev
//----------------------------------

#pragma once

#include "tinyobject.h"
#include "tinyarr.h"
#include "tinystr.h"
#include "tinymisc.h"
#include "tinyproperty.h"
#include "tinyevent.h"
#include "tinygdi.h"

namespace tiny{

#define TINY_MESSAGE WM_APP+200

class TINYBaseWnd;

//Структура параметров сообщения
struct TINYMSGPARAMS
{
	UINT code;//Сообщение
	WPARAM wparam;
	LPARAM lparam;
};

//Структура для полей
struct TINYPADDING
{
	TINYPADDING()
	{
		//Обнуление полей
		left=top=right=bottom=0;
	}
	TINYPADDING(int _left,int _top,int _right,int _bottom)
	{
		left=_left;
		top=_top;
		right=_right;
		bottom=_bottom;
	}
	//Размеры полей
	int left,top,right,bottom;
};

class TINYBaseWnd: public TINYObject
{
public:
	TINYBaseWnd();
protected:
	HWND _hwnd;//HWND окна
	bool _isctrl;//Если класс отнаследован от TINYControl = true, иначе false
	HACCEL _acc;//Акселератор (горячие клавиши)
public:
	//Свойства
	TINYStrProperty proptext;//Текст
	TINYIntProperty propx;//Х
	TINYIntProperty propy;//Y
	TINYIntProperty propw;//Ширина
	TINYIntProperty proph;//Высота
	TINYIconProperty propicon;//Большая иконка
	TINYIconProperty propsmicon;//Маленькая иконка (16х16)
	//Стили
	TINYStyleProperty proptabstop,//Для этого окна можно перемещать фокус по Tab
		propvscroll,//Вертикальный скролл
		prophscroll,//Горизонтальный скролл
		propclientedge,//Вдавленная рамка
		propstaticedge,//Статичная рамка
		propwindowedge,//Выпуклая рамка
		proptransparent,//Прозрачное окно
		propacceptfiles;//Принимает файлы через Drag&Drop
	bool propdoublebuf;//Двойная буферизация
	COLORREF propbkcolor;//Цвет фона
	//События
	TINYEvent oncreate,//При создании
		ondestroy,//При уничтожении
		onsize,//При ресайзе
		onpaint,//При отрисовке
		onmousemove,//При движении мыши
		onlbtndown,//При нажатии левой кнопки
		onlbtnup,//При отпускании левй кнопки
		ontimer;//При срабатывании таймера
	//Карты событий
	TINYEventMap onmessage,//Карта сообщений
		oncommand,//Карта команд
		onmenu,//Карта команд меню
		onacc,//Карта команд акселераторов
		onnotify;//Карта нотификаций
	//События для кастомной обработки сообщений в контролах
	TINYEvent _oncustommsg,//При приходе сообщения
		_oncustomcmd,//При приходе комнады
		_oncustomntf;//При приходе  нотификации
public:
	HWND GetHWND();//Получить HWND окна
	HACCEL GetAccel();//Получить акселератор
	bool SetAccel(HACCEL acc);//Установить акселератор
	//Создание окна
	bool Create(TINYBaseWnd *parent,LPCWSTR classname,LPCWSTR text,
		HICON icon,HCURSOR cursor,DWORD exstyle,DWORD style,UINT wndstyle,
		int x,int y,int w,int h);
	bool Attach(HWND hwnd);//Связать с HWND
	bool IsCtrl();//Если класс отнаследован от TINYControl возврващает true, иначе false

	//Функции окна
	bool Destroy();//Уничтожить окно
	bool Show(int ncmd);//Показать окно
	bool Update();//Обновить размеры клиентской области
	//Обновить окно
	bool Redraw(UINT flags);
	bool Redraw(RECT *uprect,//Область для обновления
		HRGN uprgn,//Регион для обновления
		UINT flags);
	bool SetText(TINYStr text);//Установить текст окна
	TINYStr GetText();//Получить текст окна
	int GetTextLen();//Получить длину текста окна
	TINYBaseWnd* GetParent();//Получить указатель на класс родительского окна
	bool SetParent(TINYBaseWnd* parent);//Установить родительское окно
	TINYStr GetClassName();//Получить название класса

	//Функции для работы со стилями
	bool AddStyle(DWORD style);//Добавить стиль
	bool DelStyle(DWORD style);//Удалить стиль
	bool AddExStyle(DWORD style);//Добавить расширеный стиль
	bool DelExStyle(DWORD style);//Удалить расширеный стиль
	bool SetStyle(DWORD style);//Установить стиль
	DWORD GetStyle();//Получить стиль
	bool SetExStyle(DWORD style);//Установить расширеный стиль
	DWORD GetExStyle();//Получить расширеный стиль

	//Функции для работы с иконкам
	bool SetIcon(TINYIcon icon);//Установить большую иконку
	bool SetSmallIcon(TINYIcon icon);//Установить большую иконку
	TINYIcon GetIcon();//Получить большую иконку
	TINYIcon GetSmallIcon();//Получить маленькую иконку

	//Функции для работы с положением и размерами окна
	TINYRect GetRect();//Получить область окна
	TINYRect GetClientRect();//Получить клиентскую область окна
	bool SetSize(int w,int h);//Установить размеры окна
	bool SetW(int w);//Установить ширину
	bool SetH(int h);//Установить высоту
	int GetW();//Получить ширину
	int GetH();//Получить высоту
	bool Move(int x,int y);	//Передвинуть окно
	bool SetX(int x);//Установить X
	bool SetY(int y);//Установить Y
	int GetX();//Получить Х
	int GetY();//Получить Y

	//При срабатывании таймера окну приходит сообщение WM_TIMER
	bool StartTimer(UINT id,UINT time);//Запустить таймер
	bool StopTimer(UINT id);//Остановить таймер

	bool Top();//На передний план
	bool Bottom();//На задний план
	bool SetZOrder(TINYBaseWnd* wndafter);//Установить z-положение

public:
	operator HWND();

protected:
	//Оконная функция
	static LRESULT CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
	//Функция обработки сообщений
	LRESULT _OnMessage(TINYBaseWnd* wnd,UINT message,WPARAM wparam,LPARAM lparam);

};

TINYBaseWnd* TinyGetPointer(HWND hwnd);//Получить TINYBaseWnd* из HWND

};