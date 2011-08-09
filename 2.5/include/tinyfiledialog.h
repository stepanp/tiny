//---------------------------------------------
//tiny 2.5
//tinyfiledialog.h - Диалог открытия/сохранения
//© 2009-2010 Stepan Prokofjev
//---------------------------------------------

#pragma once

#include "tinybasewnd.h"

namespace tiny{

class TINYFileDialog: public TINYObject
{
protected:
	OPENFILENAME ofn;//Структура диалога
	wchar_t namebuf[MAX_PATH];//Буфер имени файла
public:
	void Create(TINYBaseWnd *parent,LPCWSTR filter,DWORD flags);
	bool DoOpen();//Создать диалог открытия
	bool DoSave();//Создать диалог сохранения
	TINYStr GetFilename();//Получить имя файла
};


};