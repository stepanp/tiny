//----------------------------------
//tiny 2.5
//tinycontainer.cpp - Окно-контейнер
//© 2009-2010 Stepan Prokofjev
//----------------------------------

#include "tinycontainer.h"

using namespace tiny;

bool TINYContainer::Create(TINYBaseWnd *parent)
{
	return TINYBaseWnd::Create(parent,L"TINYContainer",0,0,
		LoadCursor(0,IDC_ARROW),0,WS_CHILD|WS_VISIBLE,0,0,0,100,100);
}