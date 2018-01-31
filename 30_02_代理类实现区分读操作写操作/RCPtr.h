#pragma once
//这个类对T的要求:
//要求T类型的拷贝构造函数是深拷贝
//要求T从RCObject继承或者有用到的那几个函数
//要求RCPtr<T> 指向的对象是T 不是派生类

//这个类就是来调用RCObject的相关引用增加减少的函数的

template<class T>
class RCPtr
{
public:
	RCPtr(T*real_ptr = 0) :pointee_(real_ptr) { init(); }
	RCPtr(const RCPtr& rhs);
	RCPtr& operator=(const RCPtr&rhs);
	~RCPtr();
	T*operator->() const;
	T&operator*() const;
private:
	T *pointee_;
	void init();
};

template<class T>
inline RCPtr<T>::RCPtr(const RCPtr & rhs):pointee_(rhs.pointee_) //这里必须拿到类外面写，暂时不知道为什么
{
	init();
}

template<class T>
inline RCPtr<T>::~RCPtr()
{
	if (pointee_)
		pointee_->removeReference();
}

template<class T>
inline RCPtr<T> & RCPtr<T>::operator=(const RCPtr & rhs)
{
	if (pointee_ != rhs.pointee_)
	{
		if (pointee_)
			pointee_->removeReference();

		pointee_ = rhs.pointee_;
		init();
	}
	return *this;
}

template<class T>
inline T * RCPtr<T>::operator->() const
{
	return pointee_;
}

template<class T>
inline T & RCPtr<T>::operator*() const
{
	return *pointee_;
}

template<class T>
inline void RCPtr<T>::init()
{
	if (pointee_ == 0) { return; }
	if (pointee_->isShareable() == false)
		pointee_ = new T(*pointee_);//这里假设了T类型的copy ctor是深拷贝
	pointee_->addReference();
}
