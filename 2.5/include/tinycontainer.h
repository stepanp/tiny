//--------------------------------
//tiny 2.5
//tinycontainer.h - Окно-контейнер
//© 2009-2010 Stepan Prokofjev
//---------------------------------

#pragma once

#include "tinybase.h"

namespace tiny{

class TINYContainer: public TINYBaseWnd
{
public:
	bool Create(TINYBaseWnd *parent);	
};

};