#pragma once
#include "RCPtr.h"
#include "RCObject.h"
#include <cstring>
//现在实现String类
class String
{
public:
	String(const char *value = "") :value_(new StringValue(value)) {}
	//现在默认合成的copying 函数和dtor就能满足要求了
	//合成的copying函数会分别调用RCPtr的copyting函数
	//合成的dtor调用RCPtr的析构函数
	const char & operator[](int index) const { return value_->data_[index]; }
	char &operator[](int index)
	{
		if (value_->isShared()) //如果有人一起共享，拷贝一份
			value_ = new StringValue(value_->data_);
		
		value_->markUnshareable(); //设为不可共享
		return value_->data_[index];
	}
private:
	struct StringValue:public RCObject //继承自这个类，拥有ref_count_和shareable_成员,相当于只是拥有了引用计数的功能，但是并没有实现，需要自己实现，这里把StringValue的成员交给了RCPtr的对象来管理就实现了
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