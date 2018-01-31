#pragma once
//������T��Ҫ��:
//Ҫ��T���͵Ŀ������캯�������
//Ҫ��T��RCObject�̳л������õ����Ǽ�������
//Ҫ��RCPtr<T> ָ��Ķ�����T ����������

//��������������RCObject������������Ӽ��ٵĺ�����

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
inline RCPtr<T>::RCPtr(const RCPtr & rhs):pointee_(rhs.pointee_) //��������õ�������д����ʱ��֪��Ϊʲô
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
		pointee_ = new T(*pointee_);//���������T���͵�copy ctor�����
	pointee_->addReference();
}
