//----------------------------
//tiny 2.5
//tinyarr.h - Строка
//© 2009-2010 Stepan Prokofjev
//----------------------------

#pragma once

#include "tinyarr.h"
#include "tinyobject.h"

namespace tiny{

template<typename T/*wchar_t или char*/>
class TINYStr_T: public TINYArr<T>
{
public:
	TINYStr_T() {};
	TINYStr_T(const T* str)
	{
		CopyStr(str);	
	}
	//Число в строку
	TINYStr_T(int value)
	{
		wchar_t* str=new wchar_t[MAX_PATH];
		if(_itow_s(value,str,MAX_PATH,10)==0) CopyStr(str);
		delete[] str;
	}
public:
	//Обьеденить строки
	void Append(TINYStr_T<T>& str)
	{
		int clen,nlen,len;
		clen=GetLen();//Длина текущей строки
		nlen=str.GetLen();//Длина присоединяемой строки
		len=clen+nlen+1;//Длина обеих строк + 0 в конце
		//Изменение размера
		Resize(len);
		//Копирование элементов
		for(int i=0;i<nlen;i++) _t[clen+i]=str[i];
		//0 в конец
		_t[len-1]=0;	
	}
	void Append(const T* str)
	{
		int clen,nlen,len;
		clen=GetLen();//Длина текущей строки
		nlen=lstrlen(str);//Длина присоединяемой строки
		len=clen+nlen+1;//Длина обеих строк + 0 в конце
		//Изменение размера
		Resize(len);
		//Копирование элементов
		for(int i=0;i<nlen;i++) _t[clen+i]=str[i];	
		//0 в конец
		_t[len-1]=0;	
	}
	//Скопировать содержимое строки
	void CopyStr(const T* str)
	{
		int len=lstrlen(str)+1;//Длина строки + 0 в конце
		//Создание новой строки
		T *temp=new T[len];
		//Копирование строки в массив
		for(int i=0;i<len-1;i++) temp[i]=str[i];
		//Поставить ноль в конец
		temp[len-1]=0;
		//Удаление массива
		if(_t) delete[] _t;
		//Подмена указателя
		_t=temp;
		//Размер массива равен длине строки
		_count=len;	
	}
	//Сравнить строки
	bool Compare(const T* str)
	{
		if(!_count || lstrlen(str)!=_count-1/*Если длина не совпадает*/) return false;
		//Перебор всех символов
		for(int i=0;i<_count-1;i++)
		{
			//Сравнение символов
			if(_t[i]!=str[i]) return false;
		}
		return true;
	}
	//Получить длину строки
	int GetLen()
	{
		if(_count) return _count-1;
		else return 0;
	}
	//Преобразовать в число
	int ToInt()
	{
		if(_count<0 || !_t) return 0;
		return _wtoi(_t);	
	}
	//Получить строку
	const T* c_str() {return _t;}
	//Оператор копирования строки
	TINYStr_T<T>& operator=(const T* str)
	{
		CopyStr(str);
		return *this;	
	}
	//Операторы сложения
	TINYStr_T<T>& operator+(TINYStr_T<T>& str)
	{
		Append(str);
		return *this;	
	}
	TINYStr_T<T>& operator+(const T* str)
	{
		Append(str);
		return *this;	
	}
	TINYStr_T<T>& operator+=(TINYStr_T<T>& str)
	{
		Append(str);
		return *this;	
	}
	TINYStr_T<T>& operator+=(const T* str)
	{
		Append(str);
		return *this;	
	}
	//Оператор сравнения
	bool operator==(TINYStr_T<T>& str) {return Compare(str);}
	bool operator==(const T* str) {return Compare(str);}
	operator const T*() {return c_str();}
};

typedef TINYStr_T<wchar_t> TINYStr;

};