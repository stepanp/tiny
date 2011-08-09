//-----------------------------------------------
//tiny 2.5
//tinyfiledialog.cpp - Диалог открытия/сохранения
//© 2009-2010 Stepan Prokofjev
//-----------------------------------------------

#include "tinyfiledialog.h"

using namespace tiny;

void TINYFileDialog::Create(TINYBaseWnd *parent,LPCWSTR filter,DWORD flags)
{
	ZeroMemory(namebuf,MAX_PATH);//Обнулить буфер пути файла
	ZeroMemory(&ofn,sizeof(OPENFILENAME));//Обнулить структуру диалога
	//Заполнение структуры диалога
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.lpstrFile=namebuf;//Буфер пути файла
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFilter=filter;//Фильтр
	ofn.nFilterIndex=0;//Индекс выбранного фильтра по умолчанию
	ofn.Flags=OFN_EXPLORER|flags;
	HWND hparent=0;
	if(parent) hparent=parent->GetHWND();
	ofn.hwndOwner=hparent;//HWND родительского окна
}
//Создать диалог открытия
bool TINYFileDialog::DoOpen()
{
	if(!GetOpenFileName(&ofn)) return false;
	return true;
}
//Создать диалог сохранения
bool TINYFileDialog::DoSave()
{
	if(!GetSaveFileName(&ofn)) return false;
	return true;
}
//Получить имя файла
TINYStr TINYFileDialog::GetFilename()
{
	TINYStr str=namebuf;
	return str;
}