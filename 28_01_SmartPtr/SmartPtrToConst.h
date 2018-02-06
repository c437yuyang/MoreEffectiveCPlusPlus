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
	operator SmartPtrToConst<NewType>() { return SmartPtr<NewType>(pointee); } //ģ���Ա����ʵ�����п�����ʽת�͵���ʵ������ָ�����ʽת��(��Ҫ�Ƕ�̬��ʱ����ô�)
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
	//ͨ�����ö���ת��ʵ�ֿ����͸�ֵ
	constPointee = rhs.constPointee;
	rhs.constPointee = 0;
}

template<class T>
inline SmartPtrToConst<T> & SmartPtrToConst<T>::operator=(const SmartPtrToConst<T> & rhs)
{
	if (rhs == *this)
		return *this;
	if (constPointee != 0)
		delete constPointee; //������ɾ���Լ��Ķ������

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

//�����Ƿ�Ϊ��
template<class T>
inline bool SmartPtrToConst<T>::operator!()
{
	if (constPointee == 0)
		return true;
	return false;
}
