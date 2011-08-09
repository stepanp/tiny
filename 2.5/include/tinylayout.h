//----------------------------
//tiny 2.5
//tinylayout.h - Компоновщик
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyobject.h"
#include "tinyarr.h"
#include "tinybasewnd.h"

namespace tiny{

#define TINY_SIZE_AUTO 0//Размер элемента устанавливается автоматически

class TINYLayout;

//Структура элемента компоновщика
struct TINYLAYOUTITEM
{
	TINYBaseWnd* wnd;//Указатель на окно
	TINYLayout* layout;//Указатель на компоновщик
	int size;//Размер элемента(ширина/высота)
};

class TINYLayout: public TINYObject
{
public:
	TINYLayout();
protected:
	TINYBaseWnd* _parent;//Родительское окно
	TINYLayout* _layout;//Родительский компоновщик
	TINYArr<TINYLAYOUTITEM> _items;//Массив элементов
	bool _vert;//Горизонтальный или вертикальный
	TINYPADDING _padding;//Поля
	int _spacing;//Расстояние между элементами
public:
	//Свойства
	TINYProperty<TINYPADDING> proppadding;//Поля
	TINYIntProperty	propspacing;//Расстояние между элементами
public:
	bool Create(TINYBaseWnd* parent,bool vert/*Горизонтальный или вертикальный*/);
	bool Create(TINYLayout* parent,bool vert/*Горизонтальный или вертикальный*/);
	int AddWnd(TINYBaseWnd* wnd,int size=TINY_SIZE_AUTO);//Добавить окно
	int AddLayout(TINYLayout* layout,int size=TINY_SIZE_AUTO);//Добавить компоновщик
	int AddSeparator(int size=TINY_SIZE_AUTO);//Добавить разделитель
	bool SetWnd(int index,TINYBaseWnd* wnd);//Установить окно
	TINYBaseWnd* GetWnd(int index);//Получить окно
	bool SetLayout(int index,TINYLayout* layout);//Установить компоновщик
	TINYLayout* GetLayout(int index);//Получить компоновщик
	bool SetSeparator(int index);//Установить разделитель
	bool SetItemSize(int index,int size);//Установаить размер элемента
	int GetItemSize(int index);//Получить размер элемента
	void DeleteItem(int index);//Удалить элемент
	void MoveItem(int index,int nindex);//Переместить элемент
	void SwapItems(int index,int nindex);//Поменять элементы местами
	void Align(int x,int y,int w,int h);//Перерасположить окна
	bool Update();//Обновить компоновшик
	//Функции для свойств
	bool SetPadding(TINYPADDING padding);//Установить поля
	TINYPADDING GetPadding();//Получить поля
	bool SetSpacing(int spacing);//Установить расстояние между элементами
	int GetSpacing();//Получить расстояние между элементами
public:
	void OnAlign();//Обработчик растягивания
};

};