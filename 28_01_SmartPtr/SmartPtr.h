#pragma once
#ifndef SMART_PTR_H
#define SMART_PTR_H
#include "SmartPtrToConst.h"

template <class T>
class SmartPtr :public SmartPtrToConst<T>
{
public:
	SmartPtr(T* realPtr = 0) :SmartPtrToConst(realPtr) {};
	virtual ~SmartPtr()
	{
		if (pointee != 0)
		{
			delete pointee;
			pointee = 0;
		}
	}
	SmartPtr( SmartPtr& rhs);
	SmartPtr& operator=( SmartPtr& rhs);
	T* operator->();
	T& operator*();
	bool operator!();
	template<class NewType>
	operator SmartPtr<NewType>() { return SmartPtr<NewType>(pointee); } //模板成员函数实现所有可能隐式转型的类实现智能指针的隐式转型(主要是多态的时候的用处)
//private:
//	T* pointee; //改成继承自基类配合union，解决const问题

};
#endif

template<class T>
inline SmartPtr<T>::SmartPtr(SmartPtr & rhs)
{
	//通常采用对象转移实现拷贝和赋值

	pointee = rhs.pointee;
	rhs.pointee = 0;

}

template<class T>
inline SmartPtr<T> & SmartPtr<T>::operator=( SmartPtr<T> & rhs)
{
	if (this != &rhs)
	{
		if (pointee != 0)
			delete pointee; //必须先删除自己的对象才行
		pointee = rhs.pointee;
		rhs.pointee = 0;
	}
	return *this;
}

template<class T>
inline T * SmartPtr<T>::operator->()
{
	return pointee;
}

template<class T>
inline T & SmartPtr<T>::operator*()
{
	return *this;
}

//测试是否为空
template<class T>
inline bool SmartPtr<T>::operator!()
{
	if (pointee == 0)
		return true;
	return false;
}
