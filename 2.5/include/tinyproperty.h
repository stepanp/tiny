//-------------------------------
//tiny 2.5
//tinyproperty.h - Класс свойства
//© 2009-2010 Stepan Prokofjev
//-------------------------------

#pragma once

#include "tinyobject.h"

namespace tiny{

//--------------
//Класс свойства
//--------------
template<typename T/*Тип свойства*/>
class TINYProperty: public TINYObject
{
protected:

	//Типы указателей
	typedef bool (TINYObject::*SetFunc)(T);//Сеттер
	typedef T (TINYObject::*GetFunc)();//Геттер

protected:
	TINYObject *_pointer;//Указатель на объект, которому принадлежат указатели на функции
	//Указатели на функции
	SetFunc _set;
	GetFunc _get;
public:
	//Инициализация свойства
	template<class Class_T>
	void Init(TINYObject *pointer,//Указатель на объект, которому принадлежат указатели на функции
		bool (Class_T::*set)(T),//Сеттер
		T (Class_T::*get)()//Геттер
		)
	{
		//Сохранение указателей
		_pointer=pointer;
		_set=reinterpret_cast<SetFunc>(set);
		_get=reinterpret_cast<GetFunc>(get);
	}
	//Оператор присваивания
	void operator=(const T& t)
	{
		//Вызов функции
		(_pointer->*_set)(t);
	}
	//Оператор T
	operator T() const
	{
		//Вызов функции
		return (_pointer->*_get)();
	}
};


//--------------
//Свойство стиля
//--------------
class TINYStyleProperty: public TINYProperty<DWORD>
{
protected:
	DWORD _style;//Стиль, устанавливаемый свойством
public:
	//Инициализация свойства
	template<class Class_T>
	void Init(TINYObject *pointer,//Указатель на объект, которому принадлежат указатели на функции
		DWORD style,//Стиль
		bool (Class_T::*set)(DWORD),//Сеттер
		DWORD (Class_T::*get)()//Геттер
		)
	{
		//Сохранение стиля
		_style=style;
		TINYProperty<DWORD>::Init(pointer,set,get);
	}
	//Оператор присваивания для bool
	void operator=(const bool value)
	{
		//Если value true, то добавляем стиль
		if(value) (_pointer->*_set)((_pointer->*_get)()|_style);
		//Иначе убираем стиль
		else (_pointer->*_set)((_pointer->*_get)()&~_style);
	}
	//Оператор bool
	operator bool() const
	{
		//Если стиль установлен вернуть true
		if((_pointer->*_get)()&_style) return true;
		else return false;
	}
private:
	//Закрываем операторы для DWORD
	void operator=(const DWORD& value) {}
	operator DWORD() const {return 0;}
};

//Основные типы свойств
typedef TINYProperty<bool> TINYBoolProperty;//bool
typedef TINYProperty<TINYStr> TINYStrProperty;//TINYStr - строка
typedef TINYProperty<int> TINYIntProperty;//int
typedef TINYProperty<TINYIcon> TINYIconProperty;//TINYIcon - иконка


};