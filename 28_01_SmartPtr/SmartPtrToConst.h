#pragma once
#ifndef SMART_PTR_TO_CONST_H
#define SMART_PTR_TO_CONST_H

template <class T>
class SmartPtrToConst
{
public:
	SmartPtrToConst(T* realPtr = 0) :pointee(realPtr) {};
	virtual ~SmartPtrToConst()
	{
		if (pointee != 0) 
			delete pointee;
	}
	SmartPtrToConst(const SmartPtrToConst& rhs);
	SmartPtrToConst& operator=(const SmartPtrToConst& rhs);
	T* operator->();
	T& operator*();
	bool operator!();
	template<class NewType>
	operator SmartPtrToConst<NewType>() { return SmartPtr<NewType>(pointee); } //模板成员函数实现所有可能隐式转型的类实现智能指针的隐式转型(主要是多态的时候的用处)
protected:
	union
	{
		const T* constPointee;
		T* pointee;
	};
};
#endif

template<class T>
inline SmartPtrToConst<T>::SmartPtrToConst(const SmartPtrToConst & rhs)
{
	//通常采用对象转移实现拷贝和赋值
	constPointee = rhs.constPointee;
	rhs.constPointee = 0;
}

template<class T>
inline SmartPtrToConst<T> & SmartPtrToConst<T>::operator=(const SmartPtrToConst<T> & rhs)
{
	if (rhs == *this)
		return *this;
	if (constPointee != 0)
		delete constPointee; //必须先删除自己的对象才行

	constPointee = rhs.constPointee;
	rhs.constPointee = 0;
	return *this;
}

template<class T>
inline T * SmartPtrToConst<T>::operator->()
{
	return constPointee;
}

template<class T>
inline T & SmartPtrToConst<T>::operator*()
{
	return *this;
}

//测试是否为空
template<class T>
inline bool SmartPtrToConst<T>::operator!()
{
	if (constPointee == 0)
		return true;
	return false;
}
