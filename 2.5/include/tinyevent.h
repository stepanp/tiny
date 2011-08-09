//----------------------------
//tiny 2.5
//tinyevent.h - Класс события
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyobject.h"
#include "tinyarr.h"

namespace tiny{

class TINYBaseWnd;

//Тип параметров
typedef LPARAM TINYParams;

//-------------
//Класс события
//-------------
class TINYEvent: public TINYObject
{
	//Типы указателей на обработчики
	typedef LRESULT (TINYObject::*Handler)(TINYBaseWnd* /*Указатель на окно обработчика*/,TINYParams/*Параметры*/);//Обычный обработчик
	typedef void (TINYObject::*NotifyHandler)();//Обработчик без параметов

public:
	TINYEvent();
protected:
	TINYObject* _ptr;//Указатель на объект класса, которому принадлежит обработчик
	Handler _handler;//Указатель на обработчик
	NotifyHandler _ntfhandler;//Указатель на обработчик без параметров
public:
	//Подключение обработчика к событию
	template<class Class_T>
	bool Connect(TINYObject* ptr,LRESULT (Class_T::*handler)(TINYBaseWnd*,TINYParams))
	{
		if(!ptr || !handler) return false;
		//Сохранение указателей
		_ptr=ptr;
		//Преобразование Class_T::*Handler в TINYObject::*Handler
		_handler=reinterpret_cast<Handler>(handler);
		_ntfhandler=0;
		return true;	
	}
	template<class Class_T>
	bool Connect(TINYObject* ptr,void (Class_T::*ntfhandler)())
	{
		if(!ptr || !ntfhandler) return false;
		//Сохранение указателей
		_ptr=ptr;
		_handler=0;
		//Преобразование Class_T::*NotifyHandler в TINYObject::*NotifyHandler
		_ntfhandler=reinterpret_cast<NotifyHandler>(ntfhandler);
		return true;	
	}	
	void Disconnect();//Отключение обработчика
	//Проверка, задан ли обработчик
	//Возвращает 0 если не задан
	//1, если задан обычный обработчик
	//2, если задан обработчик без параметров
	int IsConnected();
	LRESULT operator()(TINYBaseWnd* wnd,TINYParams params);//Оператор вызова функции
};

//-------------------
//Класс карты событий
//-------------------
class TINYEventMap: public TINYObject
{
protected:
	TINYArr<TINYEvent> _events;//Массив событий
	TINYArr<UINT> _keys;//Массив ключей
public:
	template<class Class_T>
	bool Connect(TINYObject* ptr,UINT key,LRESULT (Class_T::*handler)(TINYBaseWnd*,TINYParams))
	{
		if(!ptr || !handler) return false;

		//Проверка наличия события с таким ключем
		int index=GetEventIndex(key);
		//Если событие с таким ключем уже есть в карте, то заменить новым
		if(index>-1) return _events[index].Connect(ptr,handler);

		//Иначе добавить в карту
		_keys.Add(key);
		//Создание нового события
		TINYEvent nevent;
		nevent.Connect(ptr,handler);
		_events.Add(nevent);
		return true;
	}
	template<class Class_T>
	bool Connect(TINYObject* ptr,UINT key,void (Class_T::*ntfhandler)())
	{
		if(!ptr || !ntfhandler) return false;

		//Проверка наличия события с таким ключем
		int index=GetEventIndex(key);
		//Если событие с таким ключем уже есть в карте, то заменить новым
		if(index>-1) return _events[index].Connect(ptr,ntfhandler);

		//Иначе добавить в карту
		_keys.Add(key);
		//Создание нового события
		TINYEvent nevent;
		nevent.Connect(ptr,ntfhandler);
		_events.Add(nevent);
		return true;
	}
	bool Disconnect(UINT key);//Отключить обработчик по ключу
	//Получить индекс события по ключу
	//если события с таким ключем нет, вернет -1
	int GetEventIndex(UINT key);
	LRESULT operator()(TINYBaseWnd* wnd,UINT key,TINYParams params);//Операторы вызова функции по ключу
};

};