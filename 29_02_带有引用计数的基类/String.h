#pragma once
#include "RCObject.h"
#include <cstring>

//现在利用RCObject来实现String
class String
{
	//这里的一系列函数基本不变，通过调用addrefercen和removereference来控制value_的ref_count_
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