
#include <tinybase.h>
#include <tinysimple.h>
#pragma comment(lib,"Tiny.lib")

using namespace tiny;

//-----------------
//Main window class
//-----------------
class CMainWnd: public TINYAppWnd
{
public:
	TINYButton button;//Button
	CMainWnd()
	{
		//Connectig events to functions
		oncreate.Connect(this/*Pointer to class that contain function*/,/*Pointer to function*/&CMainWnd::OnCreate);//On create event
		ondestroy.Connect(this/*Pointer to class that contain function*/,/*Pointer to function*/&CMainWnd::OnDestroy);//On destroy event
	}
	LRESULT OnCreate(TINYBaseWnd *wnd/*Pointer to instance that generated event*/,TINYParams params/*Parameters of event*/)
	{
		//Creating button
		button.Create(this/*Parent control*/);
		//Setting size and position
		button.Move(10,10);
		button.SetSize(100,25);
		//Setting properties
		button.proptext=L"Click me";
		//Connectig events button with function inside CMainWnd
		button.onclick.Connect(this/*Set pointer to CMainWnd*/,&CMainWnd::OnCilck);
		return 0;
	}
	void OnCilck()
	{
		MessageBox(0,L"Clicked!",L"",0);
	}
	void OnDestroy()
	{
		THIS_APP->Quit();
	}

};

//-----------------
//Application class
//-----------------
class CApp: public TINYApp
{
protected:
	CMainWnd wnd;//Main window
	//Overloading fuction of initialization
	int OnInit(LPSTR cmd,int showcmd)
	{
		wnd.Create(0);
		wnd.Show(showcmd);
		return Run();//Run program
	}
};

CApp app;