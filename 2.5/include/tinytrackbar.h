//----------------------------
//tiny 2.5
//tinytrackbar.h - Трекбар
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYTrackBar: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool SetPos(int pos);//Установить позицию
	int GetPos();//Получить позицию
	void SetRange(int min,int max);//Установить минимальную и максимальную позиции
	int GetMinRange();//Получить минимальную позицию
	int GetMaxRange();//Получить максимальную позицию
	bool SetTick(int pos);//Установить риску
	int GetTick(int index);//Получить позицию риски
	bool SetTickFrequency(int freq);//Установить частоту рисок
	bool SetBuddies(TINYBaseWnd *left,TINYBaseWnd *right);//Установить боковые контролы
	TINYBaseWnd* GetLeftBuddy();//Получить левый контрол
	TINYBaseWnd* GetRightBuddy();//Получить правый контрол
};

};