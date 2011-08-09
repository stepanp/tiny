//----------------------------
//tiny 2.5
//tinyimagelist.h - Имаджлист
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"
#include "tinygdi.h"
#include <shlobj.h>
#pragma comment(lib,"shell32")

namespace tiny{

class TINYImageList: public TINYObject
{
protected:
	HIMAGELIST _hlist;
public:
	HIMAGELIST GetHIMAGELIST();//Получить HIMAGELSIT
	bool Create(DWORD flags,int w,int h);
	int AddIcon(HICON icon);//Добавить иконку
	int AddBitmap(HBITMAP bmp);//Добавить битмап
	//Добавить битмап с маской
	int AddMasked(HBITMAP bmp,
		COLORREF mask=RGB(255,0,255)//Цвет маски(Фуксия)
		);
	int GetCount();//Получить кол-во картинок
	bool Delete(int index);//Удалить картинку
	bool Clear();//Очистить
	HICON GetIcon(int index);//Получит иконку
};

};