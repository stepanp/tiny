//-----------------------------
//tiny 2.5
//tinyevent.cpp - Класс события
//© 2009-2010 Stepan Prokofjev
//-----------------------------

#include "tinyevent.h"

using namespace tiny;

//-------------
//Класс события
//-------------

TINYEvent::TINYEvent()
{
	//Обнуление указателей
	_ptr=0;
	_handler=0;
	_ntfhandler=0;
}
//Отключение обработчика
void TINYEvent::Disconnect()
{
	//Обнуление указателей
	_ptr=0;
	_handler=0;	
	_ntfhandler=0;
}
//Проверка, задан ли обработчик
//Возвращает 0 если не задан
//1, если задан обычный обработчик
//2, если задан обработчик без параметров
int TINYEvent::IsConnected()
{
	if(_ptr && _handler && !_ntfhandler) return 1;
	if(_ptr && !_handler && _ntfhandler) return 2;
	return 0;
}
//Оператор вызова функции
LRESULT TINYEvent::operator()(TINYBaseWnd* wnd,TINYParams params)
{
	if(IsConnected()==1)
	{
		return (_ptr->*_handler)(wnd,params);
	}
	else if(IsConnected()==2)
	{
		(_ptr->*_ntfhandler)();
	}
	return 0;
}

//-------------------
//Класс карты событий
//-------------------

//Отключить обработчик по ключу
bool TINYEventMap::Disconnect(UINT key)
{
	//Проверка наличия события с таким ключем
	int index=GetEventIndex(key);

	//Если событик с таким ключем есть
	if(index>-1)
	{
		//Удалить
		_events.Delete(index);
		return true;
	}
	return false;
}
//Получить индекс события по ключу
//если события с таким ключем нет, вернет -1
int TINYEventMap::GetEventIndex(UINT key)
{
	int count=_keys.GetCount();//Кол-во ключей
	//Перебор ключей
	for(int i=0;i<count;i++) if(_keys[i]==key) return i;
	return -1;
}
//Оператор вызова функции по ключу
LRESULT TINYEventMap::operator()(TINYBaseWnd* wnd,UINT key,TINYParams params)
{
	//Проверка наличия события с таким ключем
	int index=GetEventIndex(key);

	//Вызов обработчика события
	if(index>-1) return _events[index](wnd,params);
	return 0;		
}