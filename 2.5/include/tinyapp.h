//----------------------------
//tiny 2.5
//tinyapp.h - Приложение
//© 2009-2010 Stepan Prokofjev
///----------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYApp: public TINYObject
{
public:
	TINYApp();
	virtual int OnInit(LPSTR cmd,int showcmd)=0;//Инитиализация
	int Run();//Запуск цикла сообщений
	void Quit(int code=0);//Выход
};

extern TINYApp *THIS_APP;//Глобальный указатель на приложение

};