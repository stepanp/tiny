//----------------------------
//tiny 2.5
//tinystatusbar.h - Статусбар
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

//Структура части статусбара
struct TINYSTATUS
{
	int w;//Ширина
	LPCWSTR text;//Текст
	HICON icon;//Иконка
	bool hide;//Скрывать часть
};

class TINYStatusBar: public TINYControlEx
{
protected:
	TINYArr<TINYSTATUS> _parts;//Массив частей
	bool _UpdateParts();//Обновить части
	bool _CheckIndex(int index);//Проверка индекса
public:
	bool Attach(HWND hwnd);
	bool Create(TINYBaseWnd *parent);
	bool InsertPart(int index,int w,LPCWSTR text,HICON icon);//Вставить часть
	bool AddPart(int w,LPCWSTR text,HICON icon);//Добавить часть
	bool DeletePart(int index);//Удалить часть
	bool MovePart(int index,int nindex);//Передвинуть часть
	bool ShowPart(int index,bool show);//Скрыть/показать часть
	bool GetShowPart(int index);//Проверить показана ли часть
	bool Clear();//Удалить все части
	int GetPartCount();//Получить кол-во частей
	bool SetPartW(int index,int w);//Установить ширину части
	int GetPartW(int index);//Получить ширину части
	bool SetPartIcon(int index,HICON icon);//Установить иконку для части
	HICON GetPartIcon(int index);//Получить иконку части
	bool SetPartText(int index,PCWSTR text);//Установить текст части
	int GetPartText(int index,LPWSTR text);//Получить текст части
	int GetPartTextLen(int index);//Получить длину текста
};

};
