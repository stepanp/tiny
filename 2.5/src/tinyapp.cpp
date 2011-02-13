//----------------------------
//tiny 2.5
//tinyapp.cpp - Приложение
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinyapp.h"

using namespace tiny;

TINYApp *tiny::THIS_APP=0;//Глобальный указатель на приложение

TINYApp::TINYApp() {THIS_APP=this;}//Сохранить укзатель на экземпляр приложения в THIS_APP

//WinMain
int APIENTRY WinMain(HINSTANCE hinst,HINSTANCE prev,LPSTR cmd,int showcmd)
{
	if(!THIS_APP) return 0;//Проверка указателя на приложение
	InitCommonControls();//Для отображения диалогов в ХР с подключенным манифестом
	return THIS_APP->OnInit(cmd,showcmd);//Запуск инитиализации
}
//Запуск цикла сообщений
int TINYApp::Run()
{
	MSG msg;
	//Цикл сообщений
	while(GetMessage(&msg,0,0,0)!=0)
	{
		TINYBaseWnd* wnd=TinyGetPointer(msg.hwnd);
		//Преобразовать акслераторы
		if(!wnd || !TranslateAccelerator(msg.hwnd,wnd->GetAccel(),&msg))
		{
			//Преобразовать сообщения
			//и послать их в _WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
//Выход
void TINYApp::Quit(int code)
{
	PostQuitMessage(code);
}
