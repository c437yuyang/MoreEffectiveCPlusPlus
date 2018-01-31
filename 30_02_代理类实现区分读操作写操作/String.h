#pragma once
#include "RCPtr.h"
#include "RCObject.h"
#include <cstring>

//现在换成由代理类来实现operator[]读写的判断
class String
{
public:
	String(const char *value = "") :value_(new StringValue(value)) {}
	//const char & operator[](int index) const { return value_->data_[index]; }
	//char &operator[](int index)
	//{
	//	if (value_->isShared())
	//		value_ = new StringValue(value_->data_);

	//	value_->markUnshareable();
	//	return value_->data_[index];
	//}

	class CharProxy
	{
	public:
		CharProxy(String& str, int index) :_the_string(str), _index(index) {}
		CharProxy& operator=(const CharProxy&rhs) //这两个operator=是用于赋值(左值)的地方
		{
			make_copy();
			_the_string.value_->data_[_index] = rhs._the_string.value_->data_[rhs._index];
			return *this;
		}
		CharProxy& operator=(char c)
		{
			make_copy();
			_the_string.value_->data_[_index] = c;
			return *this;
		}
		operator char() const { return _the_string.value_->data_[_index]; }

		char * operator&()//这里要重载一下，不然不能用于chaar *p = &s1[2];
		{
			make_copy();
			_the_string.value_->markUnshareable();
			return &_the_string.value_->data_[_index];
		} 
		const char *operator&() const{return static_cast<const char *>(&_the_string.value_->data_[_index]);}

	private:
		void make_copy()
		{
			if (_the_string.value_->isShared())
				_the_string.value_ = new StringValue(_the_string.value_->data_);
		}
		String &_the_string;
		int _index;
	};
	const CharProxy operator[](int index) const //这两个operator[] 都是用于右值的地方
	{
		return CharProxy(const_cast<String &>(*this), index);
	}
	CharProxy operator[](int index)
	{
		return CharProxy(*this, index);
	}


	const char * operator&() const;

	friend class CharProxy;
private:
	struct StringValue :public RCObject
	{
		StringValue(const char *initValue) { init(initValue); }
		~StringValue() { delete[]data_; };
		StringValue(const StringValue&rhs)
		{
			init(rhs.data_);
		}
		void init(const char *initValue)
		{
			data_ = new char[strlen(initValue) + 1];
			strcpy(data_, initValue);
		}
		char *data_;
	};
	RCPtr<StringValue> value_;
};