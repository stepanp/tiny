//----------------------------
//tiny 2.5
//tinylayout.cpp - Компоновщик
//© 2009-2010 Stepan Prokofjev
//----------------------------

#include "tinylayout.h"

using namespace tiny;

TINYLayout::TINYLayout()
{
	proppadding.Init(this,&TINYLayout::SetPadding,&TINYLayout::GetPadding);
	propspacing.Init(this,&TINYLayout::SetSpacing,&TINYLayout::GetSpacing);
	//Обнуление полей
	_padding=TINYPADDING(0,0,0,0);
}
bool TINYLayout::Create(TINYBaseWnd* parent,bool vert/*Горизонтальный или вертикальный*/) 
{
	if(!parent) return false;
	_parent=parent;
	_layout=0;
	_vert=vert;
	return true;
}
bool TINYLayout::Create(TINYLayout* parent,bool vert/*Горизонтальный или вертикальный*/)
{
	if(!parent) return false;
	_parent=0;
	_layout=parent;
	_vert=vert;
	return true;
}
//Добавить окно
int TINYLayout::AddWnd(TINYBaseWnd* wnd,int size)
{
	if(!wnd) return -1;
	TINYLAYOUTITEM item;
	item.wnd=wnd;
	item.layout=0;
	item.size=size;
	return _items.Add(item);
}
//Добавить компоновщик
int TINYLayout::AddLayout(TINYLayout* layout,int size)
{
	if(!layout) return -1;
	TINYLAYOUTITEM item;
	item.wnd=0;
	item.layout=layout;
	item.size=size;
	return _items.Add(item);
}
//Добавить разделитель
int TINYLayout::AddSeparator(int size)
{
	TINYLAYOUTITEM item;
	item.wnd=0;
	item.layout=0;
	item.size=size;
	return _items.Add(item);
}
//Установить окно
bool TINYLayout::SetWnd(int index,TINYBaseWnd* wnd)
{
	//Если индекс выходит за границы массива
	if(index<0 && index>=_items.GetCount()) return false;

	_items[index].wnd=wnd;
	_items[index].layout=0;	
	return true;
}
//Получить окно
TINYBaseWnd* TINYLayout::GetWnd(int index)
{
	//Если индекс выходит за границы массива
	if(index<0 && index>=_items.GetCount()) return 0;
	return _items[index].wnd;
}
//Установить компоновщик
bool TINYLayout::SetLayout(int index,TINYLayout* layout)
{
	//Если индекс выходит за границы массива
	if(index<0 && index>=_items.GetCount()) return false;

	_items[index].wnd=0;
	_items[index].layout=layout;	
	return true;
}
//Получить компоновщик
TINYLayout* TINYLayout::GetLayout(int index)
{
	//Если индекс выходит за границы массива
	if(index<0 && index>=_items.GetCount()) return 0;
	return _items[index].layout;
}
//Установить разделитель
bool TINYLayout::SetSeparator(int index)
{
	//Если индекс выходит за границы массива
	if(index<0 && index>=_items.GetCount()) return false;

	_items[index].wnd=0;
	_items[index].layout=0;
	return true;
}
//Установаить размер элемента
bool TINYLayout::SetItemSize(int index,int size)
{
	//Если индекс выходит за границы массива
	if(index<0 && index>=_items.GetCount()) return false;
	_items[index].size=size;
	return true;
}
//Получить размер элемента
int TINYLayout::GetItemSize(int index)
{
	//Если индекс выходит за границы массива
	if(index<0 && index>=_items.GetCount()) return -1;
	return _items[index].size;
}
//Удалить элемент
void TINYLayout::DeleteItem(int index) {_items.Delete(index);}
//Переместить элемент
void TINYLayout::MoveItem(int index,int nindex) {_items.Move(index,nindex);}
//Поменять элементы местами
void TINYLayout::SwapItems(int index,int nindex) {_items.Swap(index,nindex);}
//Перерасположить окна
void TINYLayout::Align(int x,int y,int w,int h)
{
	int count=_items.GetCount();//Кол-во элементов
	int acount=0;//Кол-во элементов с TINY_SIZE_AUTO
	int allsize=0;//Общий размер элементов без TINY_SIZE_AUTO
	int alast=-1;//Индекс последнего элемента с TINY_SIZE_AUTO

	//Получение кол-ва элементов с TINY_SIZE_AUTO
	//и общего размера элементов без TINY_SIZE_AUTO
	for(int i=0;i<count;i++)
	{
		if(_items[i].size==TINY_SIZE_AUTO) 
		{
			acount++;//Кол-во элементов с TINY_SIZE_AUTO
			alast=i;///Сохраняем индекс последнего элемента с TINY_SIZE_AUTO
		}
		else allsize+=_items[i].size;//Общий размер элементов без TINY_SIZE_AUTO
	}

	//Размер элемента с TINY_SIZE_AUTO
	int asize=0;
	//Координаты и размеры элемента с учетом полей
	int ax=x+_padding.left;
	int ay=y+_padding.top;
	int aw=w-_padding.right-_padding.left;
	int ah=h-_padding.bottom-_padding.top;
	//Расстояние между элементами
	int aspacing=_spacing*(count-1);

	//Вертикальный компоновщик
	if(_vert)
	{
		//Размер элемента с TINY_SIZE_AUTO
		if(acount) 
		{
			asize=(ah-allsize)/acount;
			//Учитываем расстояние между элементами
			asize-=_spacing-_spacing/acount;
		}

		//Перебираем элементы
		for(int i=0;i<count;i++)
		{
			TINYBaseWnd* wnd=_items[i].wnd;
			TINYLayout* layout=_items[i].layout;

			//Выбор размера элемента
			int size;
			if(_items[i].size==TINY_SIZE_AUTO)
			{
				size=asize;//Автоматический размер
				//Устраняем погрешность деления
				if(i==alast) size+=ah-allsize-(asize*acount)-aspacing;
			}
			else size=_items[i].size;//Заданный размер



			//Если контрол
			if(wnd)
			{
				//Растянуть контрол
				wnd->Move(ax,ay);
				wnd->SetSize(aw,size);			
			}
			//Если компоновщик
			if(layout)
			{
				//Вызвать метод Align() компоновщика
				layout->Align(ax,ay,aw,size);
			}	

			//Сдвинуть координаты элемента с учетом интервала
			ay+=size+_spacing;
		}	
	}else{
		//Горизонтальный компоновщик
	
		//Размер элемента с TINY_SIZE_AUTO
		if(acount) 
		{
			asize=(aw-allsize)/acount;
			//Учитываем расстояние между элементами
			asize-=_spacing-_spacing/acount;
		}

		//Перебираем элементы
		for(int i=0;i<count;i++)
		{
			TINYBaseWnd* wnd=_items[i].wnd;
			TINYLayout* layout=_items[i].layout;

			//Выбор размера элемента
			int size;
			if(_items[i].size==TINY_SIZE_AUTO)
			{
				size=asize;//Автоматический размер
				//Устраняем погрешность деления
				if(i==alast) size+=aw-allsize-(asize*acount)-aspacing;
			}
			else size=_items[i].size;//Заданный размер

			//Если контрол
			if(wnd)
			{
				//Растянуть контрол
				wnd->Move(ax,ay);
				wnd->SetSize(size,ah);			
			}
			//Если компоновщик
			if(layout)
			{
				//Вызвать метод Align() компоновщика
				layout->Align(ax,ay,size,ah);
			}
			//Сдвинуть координаты элемента с учетом интервала
			ax+=size+_spacing;
		}	
	}
}
//Обновить компоновшик
bool TINYLayout::Update()
{
	if(!_parent) return false;
	
	//Если родитель является окном
	if(_parent) 
	{
		RECT rect=_parent->GetClientRect();
		//Вызвать метод Align() с размерами клиентской области родительсокого окна 
		Align(rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top);
	}
	//Если родитель является компоновщиком вызвать родительский метод Update()
	if(_layout) return _layout->Update();
	return true;
}
//Функции для свойств
//Установить поля
bool TINYLayout::SetPadding(TINYPADDING padding)
{
	_padding=padding;
	return Update();//Обновить компоновшик
}
//Получить поля
TINYPADDING TINYLayout::GetPadding() {return _padding;}
//Установить расстояние между элементами
bool TINYLayout::SetSpacing(int spacing)
{
	_spacing=spacing;
	return Update();//Обновить компоновшик
}
//Получить расстояние между элементами
int TINYLayout::GetSpacing() {return _spacing;}
//Обработчик растягивания
void TINYLayout::OnAlign()
{
	Update();
}