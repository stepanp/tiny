//-------------------------------
//tiny 2.5
//tinyprogressbar.h - Прогрессбар
//© 2009-2010 Stepan Prokofjev
//-------------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYProgressBar: public TINYControlEx
{
public:
	bool Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h);
	bool SetPos(int pos);//Установить позицию
	int GetPos();//Получить позицию
	int DeltaPos(int pos);//Установить позицию по кол-ву шагов
	int SetStep(int step);//Установить шаг прогрессбара
	int GetStep();//Получить шаг прогрессбара
	int StepIt();//Продвинуться на 1 шаг
	void SetRange(int min,int max);//Установить минимальную и максимальную позиции
	int GetMinRange();//Получить минимальную позицию
	int GetMaxRange();//Получить максимальную позицию
	//Начиная с XP
#if(_WIN32_WINNT>=0x0501)
	void SetMarquee(bool enable,int speed);//Вкл/выкл бегущую полоску и установить её скорость
#endif
};

};