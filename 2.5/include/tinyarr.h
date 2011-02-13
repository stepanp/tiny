//-------------------------------
//tiny 2.5
//tinyarr.h - Динамический массив
//© 2009-2010 Stepan Prokofjev
//-------------------------------

#pragma once

#include "tinyobject.h"

namespace tiny{

template<typename T>
class TINYArr: public TINYObject
{
public:
	TINYArr()
	{
		_t=0;
		_count=0;	
	}
	TINYArr(int size/*Начальный размер*/) 
	{
		_t=new T[size];
		_count=size;
	}
	TINYArr(const TINYArr<T>& arr)
	{
		_t=0;
		Copy(arr);
	}
	~TINYArr() {if(_t) delete[] _t;}
protected:
	T *_t;//Массив
	int _count;//Размер массива
public:
	//Добавить элемент
	int Add(T t)
	{
		//Создание нового массива
		//размером на 1 элемент больше
		T*temp=new T[_count+1];
		//Копирование элементов в новый массив
		for(int i=0;i<_count;i++) temp[i]=_t[i];
		//Удаление старого массива
		if(_t) delete[] _t;
		//Подмена указателя
		_t=temp;
		//Добавление нового элемента
		_t[_count]=t;
		//Увеличение размера массива на 1
		_count++;
		return _count-1;//Вернуть индекс нового элемета
	}
	//Вставить элемент
	int Insert(int index,T t)
	{
		//Создание нового массива
		//размером на 1 элемент больше
		T*temp=new T[_count+1];
		//Копирование элементов, до index в новый массив
		for(int i=0;i<index;i++) temp[i]=_t[i];
		//Вставка нового элемента
		temp[index]=t;
		//Копирование остальных элементов
		for(int i=index+1;i<_count+1;i++) temp[i]=_t[i-1];
		//Удаление старого массива
		if(_t) delete[] _t;
		//Подмена указателя
		_t=temp;
		//Увеличение размера массива на 1
		_count++;
		return index;//Вернуть индекс нового элемета
	}
	//Удалить элемент
	void Delete(int index)
	{
		//Создание нового массива
		//размером на 1 элемент меньше
		T*temp=new T[_count-1];
		//Копирование элементов, до index в новый массив
		for(int i=0;i<index;i++) temp[i]=_t[i];
		//Копирование остальных элементов
		for(int i=index;i<_count;i++) temp[i]=_t[i+1];
		//Удаление старого массива
		delete[] _t;
		//Подмена указателя
		_t=temp;
		//Уменьшение размера массива на 1
		_count;
	}
	//Переместить элемент
	void Move(int index,int nindex)
	{
		//Сохраняем элемент
		T temp=_t[index];
		//Если элемент нужно подвинуть вверх
		if(index<nindex)
		{
			//Сдвигаем элементы вниз
			for(int i=index;i<nindex;i++) _t[i]=_t[i+1];
			//Вставляеи сохраненный элемент
			_t[nindex]=temp;		
		}
		//Если элемент нужно подвинуть вниз
		if(index>nindex)
		{
			//Сдвигаем элементы вверх
			for(int i=nindex;i>index;i--) _t[i]=_t[i-1];
			//Вставляеи сохраненный элемент
			_t[nindex]=temp;		
		}	
	}
	//Поменять элементы местами
	void Swap(int index,int nindex)
	{
		//Сохраняем элемент
		T temp=_t[index];
		//Меняем местами
		_t[index]=_t[nindex];
		_t[nindex]=temp;	
	}
	//Очистить массив
	void Clear()
	{
		if(_t) delete[] _t;
		_t=0;
		_count=0;
	}
	//Изменить размер массива
	void Resize(int size)
	{
		//Создание нового массива
		T*temp=new T[size];
		int count;//Кол-во копируемых элементов
		//Если старый массив больше нового,
		//то копировать size элементов
		if(_count>size) count=size;
		else count=_count;//Иначе копировать все элементы
		//Копирование элементов в новый массив
		for(int i=0;i<count;i++) temp[i]=_t[i];
		//Удаление старого массива
		if(_t) delete[] _t;
		//Подмена указателя
		_t=temp;
		_count=size;	
	}
	//Скопировать содержимое другого массива
	void Copy(const TINYArr<T>& arr)
	{
		int count=arr.GetCount();
		//Создание нового массива
		T *temp=new T[count];
		//Получение указателя на массив
		T* t=arr.GetPointer();
		//Копирование элементов
		for(int i=0;i<count;i++) temp[i]=t[i];
		//Удаление старого массива
		if(_t) delete[] _t;
		//Подмена указателя
		_t=temp;
		_count=count;
	}
	//Получить размер
	int GetCount() const {return _count;}
	//Получить элемент
	T Get(int index) {return _t[index];}
	T& operator[](int index) {return _t[index];}
	//Получить указатель на сам массив
	T* GetPointer() const {return _t;}
	//Оператор копирования
	TINYArr<T>& operator=(const TINYArr<T>& arr) 
	{
		Copy(arr);
		return *this;
	}
};

};