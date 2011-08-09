//------------------------------
//tiny 2.5
//tinygdi.cpp - Объекты GDI и DC
//© 2009-2010 Stepan Prokofjev
//------------------------------

#include "tinygdi.h"

using namespace tiny;

//------------------
//Базовый объект GDI
//------------------

TINYGDIObject::TINYGDIObject() {_hobj=0;}
//Получить HGDIOBJ
HGDIOBJ TINYGDIObject::GetHGDIOBJ() {return _hobj;}
//Связать с HGDIOBJ
bool TINYGDIObject::Attach(HGDIOBJ hobj)
{
	HGDIOBJ gdiobj=hobj;
	if(!gdiobj) return false;
	Delete();//Удалить предыдущий объект GDI
	_hobj=gdiobj;
	return true;
}
//Удалить объект GDI
bool TINYGDIObject::Delete()
{
	if(_hobj) if(!DeleteObject(_hobj)) return false;
	return true;
}
TINYGDIObject::operator HGDIOBJ() {return _hobj;}

//------
//Битмап
//------

TINYBitmap::TINYBitmap() {}
TINYBitmap::TINYBitmap(UINT bmp) {LoadBitmap(bmp);}
TINYBitmap::TINYBitmap(int w,int h,int bpp,void *bits) {Create(w,h,bpp,bits);}
//Получить HBTIMAP
HBITMAP TINYBitmap::GetHBITMAP() {return HBITMAP(GetHGDIOBJ());}
bool TINYBitmap::Create(int w,int h,int bpp/*Кол-во битов на пиксель*/,
						void* bits/*Указатель на массив пикселей*/)
{
	return Attach(CreateBitmap(w,h,1,bpp,bits));
}
//Загрузить битмап
bool TINYBitmap::LoadBitmap(UINT bmp)
{
	return Attach(::LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(bmp)));
}
//Создать совместимый битмап
bool TINYBitmap::CreateCompatibleBitmap(TINYDC* dc,int w,int h)
{
	if(!dc) return false;
	return Attach(::CreateCompatibleBitmap(dc->GetHDC(),w,h));
}
//Получить ширину
int TINYBitmap::GetW() 
{
	BITMAP bmp;
	GetObject(GetHBITMAP(),sizeof(BITMAP),&bmp);//Получаем стрктуру BITMAP
	return bmp.bmWidth;
}
//Получить высоту
int TINYBitmap::GetH() 
{
	BITMAP bmp;
	GetObject(GetHBITMAP(),sizeof(BITMAP),&bmp);//Получаем стрктуру BITMAP
	return bmp.bmHeight;
}
TINYBitmap::operator HBITMAP() {return GetHBITMAP();}

//-----
//Кисть
//-----

//Получить HBRUSH
TINYBrush::TINYBrush() {}
TINYBrush::TINYBrush(TINYBitmap* bmp) {CreateBitmapBrush(bmp);}
TINYBrush::TINYBrush(COLORREF color) {CreateSolidBrush(color);}
HBRUSH TINYBrush::GetHBRUSH() {return HBRUSH(GetHGDIOBJ());}
//Создать кисть из битмапа
bool TINYBrush::CreateBitmapBrush(TINYBitmap* bmp)
{
	if(!bmp) return false;
	return Attach(CreatePatternBrush(bmp->GetHBITMAP()));
}
//Создать обычную кисть
bool TINYBrush::CreateSolidBrush(COLORREF color)
{
	return Attach(::CreateSolidBrush(color));
}
//Создать кисть системного цвета
bool TINYBrush::CreateSysColorBrush(int color)
{
	return Attach(GetSysColorBrush(color));
}
TINYBrush::operator HBRUSH() {return GetHBRUSH();}

//----
//Перо
//----

TINYPen::TINYPen() {}
TINYPen::TINYPen(int style,int w,COLORREF color) {Create(style,w,color);}
//Получить перо
HPEN TINYPen::GetHPEN() {return HPEN(GetHGDIOBJ());}
//Создать перо
bool TINYPen::Create(int style,int w,COLORREF color)
{
	return Attach(CreatePen(style,w,color));
}
TINYPen::operator HPEN() {return GetHPEN();}

//-----
//Шрифт
//-----

//Получить HFONT
HFONT TINYFont::GetHFONT() {return HFONT(GetHGDIOBJ());}
//Получить стандартный шрифт
bool TINYFont::GetDefaultFont()
{
	return Attach(HFONT(GetStockObject(DEFAULT_GUI_FONT)));
}
//Создать шрифт
bool TINYFont::Create(LPCWSTR name,//L"Default" - стандартный шрифт
		int size,//0 - стандартный размер
		bool bold,//Жирный
		bool italic,//Наклонный
		bool underline,//Подчеркнутый
		bool strikeout)//Зачеркнутый
{
	//Толщина шрифта
	DWORD weight=FW_NORMAL;//Нормальный
	if(bold) weight=FW_BOLD;//Жирный
	return Attach(CreateFont(size,0,0,0,weight,
		DWORD(italic),DWORD(underline),DWORD(strikeout),
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		name));
}
TINYFont::operator HFONT() {return GetHFONT();}

//------
//Регион
//------

//Получить HRGN
HRGN TINYRgn::GetHRGN() {return HRGN(GetHGDIOBJ());}
//Создать регион по области
bool TINYRgn::CreateRectRgn(RECT rect)
{
	return Attach(::CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom));
}
//Создать овальный регион
bool TINYRgn::CreateEllipticRgn(RECT rect)
{
	return Attach(::CreateEllipticRgn(rect.left,rect.top,rect.right,rect.bottom));
}
//Создать регион с закругленными краями
bool TINYRgn::CreateRoundRectRgn(RECT rect,
		int corw,//Закругление угла по горизонтали
		int corh//Закругление угла по вертикали
		)
{
	return Attach(::CreateRoundRectRgn(rect.left,rect.top,rect.right,rect.bottom,
		corw,corh));
}
//Обьединить регионы 
bool TINYRgn::CombineRgn(TINYRgn *rgn1,TINYRgn *rgn2,int mode)
{
	HRGN hrgn1=0;
	HRGN hrgn2=0;
	if(rgn1) hrgn1=rgn1->GetHRGN();
	if(rgn2) hrgn2=rgn2->GetHRGN();
	if(::CombineRgn(GetHRGN(),hrgn1,hrgn2,mode)==ERROR) return false;
	return true;
}
//Установить регион окну
/*bool TINYRgn::SetToWindow(TINYBaseWnd *wnd)
{
	if(!wnd) return false;
	if(!SetWindowRgn(wnd->GetHWND(),GetHRGN(),TRUE)) return false;
	return true;
}*/
TINYRgn::operator HRGN() {return GetHRGN();}



//--
//DC
//--

//Функции DC
//Получить HDC
HDC TINYDC::GetHDC()
{
	return _dc;
}
//Связать с HDC
bool TINYDC::Attach(HDC hdc)
{
	if(!hdc) return false;
	_dc=hdc;
	return true;
}
//Создать совместимый DC
bool TINYDC::CreateCompatibleDC(TINYDC *dc)
{
	HDC cmpdc=0;
	if(dc) cmpdc=dc->GetHDC();
	return Attach(::CreateCompatibleDC(cmpdc));
}
//Удалить DC
bool TINYDC::Delete()
{
	if(!DeleteDC(_dc)) return false;
	return true;
}
//Освободить DC
bool TINYDC::Release(HWND wnd)
{
	if(!wnd) return false;
	if(!ReleaseDC(wnd,_dc)) return false;
	return true;
}
//Получить DC окна
bool TINYDC::GetDC(HWND hwnd)
{
	return Attach(::GetDC(hwnd));
}
//Получить размеры DC
RECT TINYDC::GetClipBox()
{
	RECT rect;
	::GetClipBox(_dc,&rect);
	return rect;
}
//Скопировать содержимое
bool TINYDC::BitBlt(int x,int y,int w,int h,
		TINYDC *src,int nx,int ny,DWORD mode)
{
	if(!src) return false;
	if(!::BitBlt(_dc,x,y,w,h,src->GetHDC(),nx,ny,mode)) return false;
	return true;
}
//Начать рисование
bool TINYDC::BeginPaint(HWND parent/*Родительское окно*/)
{
	if(!parent) return false;
	_parent=parent;//Сохранение указателя на родительское окно(для EndPaint)
	return Attach(::BeginPaint(parent,&_ps));
}
//Закончить рисование
bool TINYDC::EndPaint()
{
	if(!_parent) return false;
	if(!::EndPaint(_parent,&_ps)) return false;
	return true;
}

//Функции рисования текста
//Вывести текст
bool TINYDC::TextOut(LPCWSTR text,int x,int y)
{
	if(!::TextOut(_dc,x,y,text,lstrlen(text))) return false;
	return true;
}
//Отрисовать текст
bool TINYDC::DrawText(LPCWSTR text,RECT rect,UINT format)
{
	if(!::DrawText(_dc,text,-1,&rect,format)) return false;
	return true;
}
//Установить цвет текста
bool TINYDC::SetTextColor(COLORREF color)
{
	if(!::SetTextColor(_dc,color)) return false;
	return true;
}

//Функции рисования
//Заполнить область
bool TINYDC::FillRect(RECT rect,TINYBrush* brush)
{
	if(!brush) return false;
	if(!::FillRect(_dc,&rect,brush->GetHBRUSH())) return false;
	return true;
}
//Градиентная заливка
bool TINYDC::FillGradient(RECT rect,
		COLORREF clrbegin,//Цвет начала градиента
		COLORREF clrend,//Цвет конца градиента
		bool vert//Вертикально или горизонтально 
		)
{
	TRIVERTEX tvx[2];
	//Начальный цвет
	tvx[0].x=rect.left;
	tvx[0].y=rect.top;
	tvx[0].Red=COLOR16(GetRValue(clrbegin)<<8);
	tvx[0].Green=COLOR16(GetGValue(clrbegin)<<8);
	tvx[0].Blue=COLOR16(GetBValue(clrbegin)<<8);
	tvx[0].Alpha=0;
	//Конечный цвет
	tvx[1].x=rect.right;
	tvx[1].y=rect.bottom;
	tvx[1].Red=COLOR16(GetRValue(clrend)<<8);
	tvx[1].Green=COLOR16(GetGValue(clrend)<<8);
	tvx[1].Blue=COLOR16(GetBValue(clrend)<<8);
	tvx[1].Alpha=0;

	GRADIENT_RECT grect;
	grect.UpperLeft=0;
	grect.LowerRight=1;
	
	ULONG mode;
	if(vert) mode=GRADIENT_FILL_RECT_V;
	else mode=GRADIENT_FILL_RECT_H;

	if(!GradientFill(_dc,tvx,2,&grect,1,mode)) return false;
	return true;
}

//Рарисовать прямоугольник
bool TINYDC::DrawRectangle(RECT rect)
{
	if(!Rectangle(_dc,rect.left,rect.top,rect.right,rect.bottom)) return false;
	return true;
}
//Нарисовать прямоугольник с закругленными краями
bool TINYDC::DrawRoundRect(RECT rect,
		int corw,//Закругление угла по горизонтали
		int corh//Закругление угла по вертикали
		)
{
	if(!RoundRect(_dc,rect.left,rect.top,rect.right,rect.bottom,
		corw,corh)) return false;
	return true;
}
//Нарисовать эллипс
bool TINYDC::DrawEllipse(RECT rect)
{
	if(!Ellipse(_dc,rect.left,rect.top,rect.right,rect.bottom)) return false;
	return true;
}
//Нарисовать рамку фокуса
bool TINYDC::DrawFocusRect(RECT rect)
{
	if(!::DrawFocusRect(_dc,&rect)) return false;
	return true;
}

//Функции рисования линий
//Нарисовать линию
bool TINYDC::LineTo(int x,int y)
{
	::LineTo(_dc,x,y);
	return true;
}
bool TINYDC::MoveTo(int x,int y)
{
	if(!::MoveToEx(_dc,x,y,0)) return false;
	return true;
}

//Функции работы с фоном и т.п.
//Установить цвет пикселя
bool TINYDC::SetPixel(int x,int y,COLORREF color)
{
	if(::SetPixel(_dc,x,y,color)==-1||ERROR_INVALID_PARAMETER) return false;
	return true;
}
//Получить цвет пикселя
COLORREF TINYDC::GetPixel(int x,int y)
{
	return ::GetPixel(_dc,x,y);
}
//Установить цвет фона
bool TINYDC::SetBkColor(COLORREF color)
{
	if(::SetBkColor(_dc,color)==CLR_INVALID) return false;
	return true;
}
//Получить цвет фона
COLORREF TINYDC::GetBkColor()
{
	return ::GetBkColor(_dc);
}
//Установить режим фона(Прозрачный/Непрозрачный)
bool TINYDC::SetBkMode(int mode)
{
	if(!::SetBkMode(_dc,mode)) return false;
	return true;
}
//Получить режим фона(Прозрачный/Непрозрачный)
int TINYDC::GetBkMode()
{
	return ::GetBkMode(_dc);
}

//Функции работы с объектами GDI
//Выбрать обьект
bool TINYDC::SelectObject(TINYGDIObject* obj)
{
	if(!obj) return false;
	if(!::SelectObject(_dc,obj->GetHGDIOBJ())) return false;
	return true;
}

//--------------------------
//DC c двойной буфферизацией
//--------------------------

//Получить задний буффер
TINYDC* TINYDBDC::GetMemDC()
{
	return &_memdc;
}
//Инитиализация двойной буфферизации
bool TINYDBDC::InitDoubleBuffer()
{
	//Создание совместимого DC
	if(!_memdc.CreateCompatibleDC(this)) return false;
	//Получение размеров DC
	RECT rect=GetClipBox();
	//Создание совместимого битмапа
	_membmp.CreateCompatibleBitmap(this,rect.left+rect.right,rect.top+rect.bottom);
	_memdc.SelectObject(&_membmp);
	//Копирование содержимого переднего буфера в задний
	return _memdc.BitBlt(0,0,rect.left+rect.right,rect.top+rect.bottom,
		this,0,0,SRCCOPY);
}
//Отрисовать задний буффер
bool TINYDBDC::DrawDoubleBuffer()
{
	//Получение размеров DC
	RECT rect=GetClipBox();
	//Копирование содержимого заднего буфера в передний
	if(!BitBlt(0,0,rect.left+rect.right,rect.top+rect.bottom,
		&_memdc,0,0,SRCCOPY)) return false;
	//Удаление битмапа
	if(!_membmp.Delete()) return false;
	//Удаление заднего буфера
	return _memdc.Delete();
}