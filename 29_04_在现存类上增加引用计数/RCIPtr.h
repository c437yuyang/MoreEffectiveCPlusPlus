#pragma once
#include "RCObject.h"
template<class T>
class RCIPtr
{
public:
	RCIPtr(T*real_ptr = 0);
	RCIPtr(const RCIPtr& rhs);
	~RCIPtr();
	RCIPtr& operator=(const RCIPtr&rhs);
	const T* operator->() const;
	T* operator->();
	const T& operator*() const;
	T& operator*();

private:
	struct CountHolder :public RCObject
	{
		~CountHolder() { delete pointee_; }
		T *pointee_;
	};

	CountHolder *counter_;
	void init();
	void make_copy();

};

template<class T>
void RCIPtr<T>::init()
{
	if (counter_->isShareable() == false)
	{
		T* old_value = counter_->pointee_;
		counter_ = new CountHolder;
		counter_->pointee_ = new T(*old_value);
	}
	counter_->addReference();
}

template<class T>
inline void RCIPtr<T>::make_copy()
{
	if (counter_->isShared())
	{
		T *old_value = counter_->pointee_;
		counter_->removeReference();
		counter_ = new CountHolder; //一个counter对应一个指针，所以这里要新建一个
		counter_->pointee_ = new T(*old_value);
		init();
	}
}

template<class T>
inline RCIPtr<T>::RCIPtr(T * real_ptr)
	:counter_(new CountHolder)
{
	counter_->pointee_ = real_ptr;
	init();
}

template<class T>
inline RCIPtr<T>::RCIPtr(const RCIPtr & rhs)
	:counter_(rhs.counter_)
{
	init();
}

template<class T>
inline RCIPtr<T>::~RCIPtr()
{
	counter_->removeReference();
}

template<class T>
inline RCIPtr<T> & RCIPtr<T>::operator=(const RCIPtr<T> & rhs)
{
	if (counter_ != rhs.counter_)
	{
		counter_->removeReference();
		counter_ = rhs.counter_;
		init();
	}
	return *this;
}

template<class T>
inline const T * RCIPtr<T>::operator->() const
{
	return counter_->pointee_;
}

template<class T>
inline T * RCIPtr<T>::operator->()
{
	make_copy();
	return counter_->pointee_;
}

template<class T>
inline const T & RCIPtr<T>::operator*() const
{
	return *(counter_->pointee_); //本身->优先级更高的，还是加上括号好看点
}

template<class T>
inline T & RCIPtr<T>::operator*()//写时拷贝
{
	make_copy();
	return *(counter_->pointee_);
}
