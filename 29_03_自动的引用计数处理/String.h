#pragma once
#include "RCPtr.h"
#include "RCObject.h"
#include <cstring>
//����ʵ��String��
class String
{
public:
	String(const char *value = "") :value_(new StringValue(value)) {}
	//����Ĭ�Ϻϳɵ�copying ������dtor��������Ҫ����
	//�ϳɵ�copying������ֱ����RCPtr��copyting����
	//�ϳɵ�dtor����RCPtr����������


	const char & operator[](int index) const { return value_->data_[index]; }
	char &operator[](int index)
	{
		if (value_->isShared()) //�������һ��������һ��
			value_ = new StringValue(value_->data_);
		
		value_->markUnshareable(); //��Ϊ���ɹ���
		return value_->data_[index];
	}
private:
	struct StringValue:public RCObject
	{
		char *data_;
		StringValue(const char *initValue) { init(initValue); }
		~StringValue() { delete[]data_; };
		void init(const char *initValue)
		{
			data_ = new char[strlen(initValue) + 1];
			strcpy(data_, initValue);
		}
		StringValue(const StringValue&rhs)
		{
			init(rhs.data_);
		}
	};
	RCPtr<StringValue> value_;
};