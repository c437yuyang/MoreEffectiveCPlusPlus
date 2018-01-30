#pragma once
#include "RCObject.h"
#include <cstring>

//��������RCObject��ʵ��String
class String
{
	//�����һϵ�к����������䣬ͨ������addrefercen��removereference������value_��ref_count_
private:
	struct StringValue :public RCObject
	{
		char *data_;
		StringValue(const char *init_value);
		~StringValue();
	};
};

String::StringValue::StringValue(const char* init_value)
{
	data_ = new char[strlen(init_value) + 1];
	strcpy(data_, init_value);
}

String::StringValue::~StringValue()
{
	delete data_;
}