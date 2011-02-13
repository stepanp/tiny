//-----------------------------
//tiny 2.5
//tinystatusbar.cpp - Статусбар
//© 2009-2010 Stepan Prokofjev
//-----------------------------

#include "tinystatusbar.h"

using namespace tiny;

bool TINYStatusBar::Attach(HWND hwnd)
{
	if(!TINYBaseWnd::Attach(hwnd)) return false;
	//Кол-во частей
	int count=GetPartCount();
	int *wparts=new int[count];
	//Получение частей
	if(!SendMessage(_hwnd,SB_GETPARTS,
		WPARAM(count),LPARAM(wparts))) return false;
	_parts.Clear();
	_parts.Resize(count);
	//Заполнение массива
	int allw=0;
	for(int i=0;i<count;i++)
	{
		//Преобразовывание ширины
		allw=allw+wparts[i];
		TINYSTATUS part;
		part.w=allw;
		//Получение текста
		wchar_t *text=new wchar_t[MAX_PATH];
		GetPartText(i,text);
		part.text=text;
		delete[] text;
		//Получение иконки
		part.icon=GetPartIcon(i);
		//Показывать часть
		part.hide=false;
		//Добаваление части
		_parts[i]=part;
	}
	return true;
}
bool TINYStatusBar::Create(TINYBaseWnd *parent)
{
	return TINYControlEx::Create(parent,ICC_BAR_CLASSES,STATUSCLASSNAME,0,0,
		SBARS_SIZEGRIP|//Ресайзер в углу окна
		0,0,0,0,0);
}
//Вставить часть
bool TINYStatusBar::InsertPart(int index,int w,LPCWSTR text,HICON icon)
{
	int count=_parts.GetCount();
	//Определение индекса
	if(index<-1) return false;
	int nindex=0;
	if((index==-1)||(index>count)) nindex=count;
	else nindex=index;
	//Заполнение структуры TINYSTATUS
	TINYSTATUS part;
	part.w=w;
	part.text=text;
	part.icon=icon;
	part.hide=true;
	//Добавление части в массив
	_parts.Insert(nindex,part);
	//Обновить части
	return _UpdateParts();
}
//Добавить часть
bool TINYStatusBar::AddPart(int w,LPCWSTR text,HICON icon)
{
	return InsertPart(-1,w,text,icon);
}
//Обновить части
bool TINYStatusBar::_UpdateParts()
{
	int count=_parts.GetCount();
	if(!count) return false;
	//Создание массива ширин
	int *wparts=new int[count];
	int allw=0;
	//Определение ширины
	for(int i=0;i<count;i++)
	{
		if(_parts[i].hide)//Если часть скрыта, не показывать
		{
			allw=allw+_parts[i].w;
			wparts[i]=allw;
		}
	}
	//Установка частей
	if(!SendMessage(_hwnd,SB_SETPARTS,WPARAM(count),LPARAM(wparts))) return false;
	delete[] wparts;
	//Установка текста иконок и подсказок
	for(int i=0;i<count;i++)
	{
		if(!SetPartText(i,_parts[i].text)) return false;
		if(!SetPartIcon(i,_parts[i].icon)) return false;
	}
	return true;		
}
//Удалить часть
bool TINYStatusBar::DeletePart(int index)
{
	if(!_CheckIndex(index)) return false;
	_parts.Delete(index);
	return _UpdateParts();
}
//Передвинуть часть
bool TINYStatusBar::MovePart(int index,int nindex)
{
	if(!_CheckIndex(index)) return false;
	//Скопировать часть
	TINYSTATUS part=_parts[index];
	_parts.Delete(index);//Удалить часть
	//Вставить в новое место
	InsertPart(nindex,
		part.w,
		part.text,
		part.icon);
	return _UpdateParts();
}
//Скрыть/показать часть
bool TINYStatusBar::ShowPart(int index,bool show)
{
	if(!_CheckIndex(index)) return false;
	_parts[index].hide=!show;
	return _UpdateParts();
}
//Проверить показана ли часть
bool TINYStatusBar::GetShowPart(int index)
{
	if(!_CheckIndex(index)) return false;
	return !_parts[index].hide;
}
//Удалить все части
bool TINYStatusBar::Clear()
{
	//Очистка частей в статусбаре
	int *wparts=new int[1];
	wparts[0]=0;
	if(!SendMessage(_hwnd,SB_SETPARTS,WPARAM(1),LPARAM(wparts))) return false;
	delete[] wparts;
	//Очистка массива частей
	_parts.Clear();
	return true;
}
//Получить кол-во частей
int TINYStatusBar::GetPartCount()
{
	return SendMessage(_hwnd,SB_GETPARTS,0,0);
}
//Установить ширину части
bool TINYStatusBar::SetPartW(int index,int w)
{
	if((!_CheckIndex(index))||(w<0)) return false;
	_parts[index].w=w;
	return _UpdateParts();
}
//Получить ширину части
int TINYStatusBar::GetPartW(int index)
{
	if(!_CheckIndex(index)) return false;
	return _parts[index].w;
}
//Установить иконку для части
bool TINYStatusBar::SetPartIcon(int index,HICON icon)
{
	if(!SendMessage(_hwnd,SB_SETICON,WPARAM(index),LPARAM(icon))) return false;
	return true;
}
//Получить иконку части
HICON TINYStatusBar::GetPartIcon(int index)
{
	return HICON(SendMessage(_hwnd,SB_GETICON,WPARAM(index),0));
}
//Установить текст части
bool TINYStatusBar::SetPartText(int index,PCWSTR text)
{
	if(!SendMessage(_hwnd,SB_SETTEXT,MAKEWPARAM(index,0),LPARAM(text))) return false;
	return true;
}
//Получить текст части
int TINYStatusBar::GetPartText(int index,LPWSTR text)
{
	return SendMessage(_hwnd,SB_GETTEXT,WPARAM(index),LPARAM(text));
}
//Получить длину текста
int TINYStatusBar::GetPartTextLen(int index)
{
	return SendMessage(_hwnd,SB_GETTEXTLENGTH,WPARAM(index),0);
}
//Проверка индекса
bool TINYStatusBar::_CheckIndex(int index)
{
	if((index<-1)||(index>_parts.GetCount())) return false;
	return true;
}