//----------------------------
//tiny 2.5
//tinygdi.h - Объекты GDI и DC
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyobject.h"
#pragma comment(lib,"Msimg32.lib")//Для градиента

namespace tiny{

class TINYDC;

//------------------
//Базовый объект GDI
//------------------
class TINYGDIObject: public TINYObject
{
public:
	TINYGDIObject();
protected:
	HGDIOBJ _hobj;//Объект GDI
public:
	HGDIOBJ GetHGDIOBJ();//Получить HGDIOBJ
	bool Attach(HGDIOBJ hobj);//Связать с HGDIOBJ
	bool Delete();//Удалить объект GDI
	operator HGDIOBJ();	
};

//------
//Битмап
//------
class TINYBitmap: public TINYGDIObject
{
public:
	TINYBitmap();
	TINYBitmap(UINT bmp);
	TINYBitmap(int w,int h,int bpp,void *bits);
public:
	HBITMAP GetHBITMAP();//Получить HBTIMAP
	bool Create(int w,int h,int bpp/*Кол-во битов на пиксель*/,
		void* bits/*Указатель на массив пикселей*/);
	bool LoadBitmap(UINT bmp);//Загрузить битмап
	bool CreateCompatibleBitmap(TINYDC* dc,int w,int h);//Создать совместимый битмап
	int GetW();//Получить ширину
	int GetH();//Получить высоту
	operator HBITMAP();	
};

//-----
//Кисть
//-----
class TINYBrush: public TINYGDIObject
{
public:
	TINYBrush();
	TINYBrush(TINYBitmap* bmp);
	TINYBrush(COLORREF color);
public:
	HBRUSH GetHBRUSH();//Получить HBRUSH
	bool CreateBitmapBrush(TINYBitmap* bmp);//Создать кисть из битмапа
	bool CreateSolidBrush(COLORREF color);//Создать обычную кисть
	bool CreateSysColorBrush(int color);//Создать кисть системного цвета
	operator HBRUSH();	
};

//----
//Перо
//----
class TINYPen: public TINYGDIObject
{
public:
	TINYPen();
	TINYPen(int style,int w,COLORREF color);
public:
	HPEN GetHPEN();//Получить HPEN
	bool Create(int style,int w,COLORREF color);//Создать перо
	operator HPEN();	
};

//-----
//Шрифт
//-----
class TINYFont: public TINYGDIObject
{
public:
	HFONT GetHFONT();//Получить HFONT
	bool GetDefaultFont();//Получить стандартный шрифт
	//Создать шрифт
	bool Create(LPCWSTR name,//L"Default" - стандартный шрифт
		int size,//0 - стандартный размер
		bool bold,//Жирный
		bool italic=false,//Наклонный
		bool underline=false,//Подчеркнутый
		bool strikeout=false);//Зачеркнутый
	operator HFONT();
};

//------
//Регион
//------
class TINYRgn: public TINYGDIObject
{
public:
	HRGN GetHRGN();//Получить HRGN
	bool CreateRectRgn(RECT rect);//Создать регион по области
	bool CreateEllipticRgn(RECT rect);//Создать овальный регион
	//Создать регион с закругленными краями
	bool CreateRoundRectRgn(RECT rect,
		int corw,//Закругление угла по горизонтали
		int corh//Закругление угла по вертикали
		);
	bool CombineRgn(TINYRgn *rgn1,TINYRgn *rgn2,int mode);//Обьединить регионы 
	//bool SetToWindow(TINYBaseWnd *wnd);//Установить регион окну
	operator HRGN();
};

//--
//DC
//--
class TINYDC: public TINYObject
{
protected:
	HDC _dc;//HDC
	PAINTSTRUCT _ps;
	HWND _parent;//Родительское окно(для Begin/EndPaint)
public:

	//Функции DC
	HDC GetHDC();//Получить HDC
	bool Attach(HDC hdc);//Связать с HDC
	bool CreateCompatibleDC(TINYDC *dc);//Создать совместимый DC
	bool Delete();//Удалить DC
	bool Release(HWND wnd);//Освободить DC
	bool GetDC(HWND hwnd);//Получить DC окна
	RECT GetClipBox();//Получить размеры DC
	bool BitBlt(int x,int y,int w,int h,
		TINYDC *src,int nx,int ny,DWORD mode);//Скопировать содержимое
	bool BeginPaint(HWND parent/*Родительское окно*/);//Начать рисование
	bool EndPaint();//Закончить рисование

	//Функции рисования текста
	bool TextOut(LPCWSTR text,int x,int y);//Вывести текст
	bool DrawText(LPCWSTR text,RECT rect,UINT format);//Отрисовать текст
	bool SetTextColor(COLORREF color);//Установить цвет текста

	//Функции рисования
	bool FillRect(RECT rect,TINYBrush* brush);//Заполнить область
	//Градиентная заливка
	bool FillGradient(RECT rect,
		COLORREF clrbegin,//Цвет начала градиента
		COLORREF clrend,//Цвет конца градиента
		bool vert//Вертикально или горизонтально 
		);
	bool DrawRectangle(RECT rect);//Рарисовать прямоугольник
	//Нарисовать прямоугольник с закругленными краями
	bool DrawRoundRect(RECT rect,
		int corw,//Закругление угла по горизонтали
		int corh//Закругление угла по вертикали
		);
	bool DrawEllipse(RECT rect);//Нарисовать эллипс
	bool DrawFocusRect(RECT rect);//Нарисовать рамку фокуса

	//Функции рисования линий
	bool MoveTo(int x,int y);//Текущая позиция
	bool LineTo(int x,int y);//Нарисовать линию

	//Функции работы с фоном и т.п.
	bool SetPixel(int x,int y,COLORREF color);//Установить цвет пикселя
	COLORREF GetPixel(int x,int y);//Получить цвет пикселя
	bool SetBkColor(COLORREF color);//Установить цвет фона
	COLORREF GetBkColor();//Получить цвет фона
	bool SetBkMode(int mode);//Установить режим фона(Прозрачный/Непрозрачный)
	int GetBkMode();//Получить режим фона(Прозрачный/Непрозрачный)

	//Функции работы с объектами GDI
	bool SelectObject(TINYGDIObject* obj);//Выбрать обьект
};

//--------------------------
//DC c двойной буфферизацией
//--------------------------
class TINYDBDC: public TINYDC
{
protected:
	TINYDC _memdc;//Задний буффер
	TINYBitmap _membmp;//Совместимый битмап для заднего буффера
public:
	TINYDC* GetMemDC();//Получить задний буффер
	bool InitDoubleBuffer();//Инитиализация двойной буфферизации
	bool DrawDoubleBuffer();//Отрисовать задний буффер
};

};