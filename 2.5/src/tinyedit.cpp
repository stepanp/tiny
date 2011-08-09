//----------------------------
//tiny 2.5
//tinyedit.cpp - Едит
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinyedit.h"

using namespace tiny;

TINYEdit::TINYEdit()
{
	_oncustomcmd.Connect(this,&TINYEdit::_OnCustomCmd);
	//Инитиализация свойств
	propnumber.Init(this,ES_NUMBER,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	proppassword.Init(this,ES_PASSWORD,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propreadonly.Init(this,ES_READONLY,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propuppercase.Init(this,ES_UPPERCASE,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	proplowercase.Init(this,ES_LOWERCASE,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propautovscroll.Init(this,ES_AUTOVSCROLL,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propautohscroll.Init(this,ES_AUTOHSCROLL,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);
	propnohidesel.Init(this,ES_NOHIDESEL,&TINYBaseWnd::SetStyle,&TINYBaseWnd::GetStyle);

}
bool TINYEdit::Create(TINYBaseWnd *parent)
{
	return TINYControl::Create(parent,L"EDIT",0,WS_EX_CLIENTEDGE,0,0,0,100,25);
}
//Кастомная обработка команд
LRESULT TINYEdit::_OnCustomCmd(TINYBaseWnd* wnd,TINYParams params)
{
	//Параметры команды
	TINYMSGPARAMS* cmd=(TINYMSGPARAMS*)(params);

	if(cmd->code==EN_CHANGE) onchange(wnd,0);
	return 0;
}