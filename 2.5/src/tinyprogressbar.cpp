//---------------------------------
//tiny 2.5
//tinyprogressbar.cpp - Прогрессбар
//© 2009-2010 Stepan Prokofjev
//---------------------------------

#include "tinyprogressbar.h"

using namespace tiny;

bool TINYProgressBar::Create(TINYBaseWnd *parent,DWORD exstyle,DWORD style,
		int x,int y,int w,int h)
{
	if(!TINYControlEx::Create(parent,0,PROGRESS_CLASS,0,exstyle,style,x,y,w,h)) return false;
	//Удалить стиль PBS_MARQUEE, если он не указан при создании
	if(style!=(style|PBS_MARQUEE)) DelStyle(PBS_MARQUEE);
	return true;
}
//Установить позицию
bool TINYProgressBar::SetPos(int pos)
{
	if(!SendMessage(_hwnd,PBM_SETPOS,WPARAM(pos),0)) return false;
	return true;
}
//Получить позицию
int TINYProgressBar::GetPos()
{
	return SendMessage(_hwnd,PBM_GETPOS,0,0);
}
//Установить шаг прогрессбара
int TINYProgressBar::SetStep(int step)
{
	return SendMessage(_hwnd,PBM_SETSTEP,WPARAM(step),0);
}
//Получить шаг прогрессбара
int TINYProgressBar::GetStep()
{
	//Устанавливаем новый шаг, получаем старый
	int step=SendMessage(_hwnd,PBM_SETSTEP,WPARAM(0),0);
	//Возвращаем обратно старый
	SendMessage(_hwnd,PBM_SETSTEP,WPARAM(step),0);
	return step;
}
//Установить позицию по кол-ву шагов
int TINYProgressBar::DeltaPos(int pos)
{
	return SendMessage(_hwnd,PBM_DELTAPOS,WPARAM(pos),0);
}
//Продвинуться на 1 шаг
int TINYProgressBar::StepIt()
{
	return SendMessage(_hwnd,PBM_STEPIT,0,0);
}
//Установить минимальную и максимальную позиции
void TINYProgressBar::SetRange(int min,int max)
{
	SendMessage(_hwnd,PBM_SETRANGE32,WPARAM(min),LPARAM(max));
}
//Получить минимальную позицию
int TINYProgressBar::GetMinRange()
{
	return SendMessage(_hwnd,PBM_GETRANGE,WPARAM(TRUE),0);
}
//Получить максимальную позицию
int TINYProgressBar::GetMaxRange()
{
	return SendMessage(_hwnd,PBM_GETRANGE,WPARAM(FALSE),0);
}
//Начиная с XP
#if(_WIN32_WINNT>=0x0501)
//Вкл/выкл бегущую полоску и установить её скорость
void TINYProgressBar::SetMarquee(bool enable,int speed)
{
	SendMessage(_hwnd,PBM_SETMARQUEE,WPARAM(enable),LPARAM(speed));
}
#endif