#pragma once
#include <cstring>
//建立这个类的两个动机:
// 1.方便跟踪堆中的对象，没人使用的时候自动销毁。
// 2.如果很多对象有相同的值，存储多次是浪费。

#pragma region 普通String类型的做法

//class String
//{
//public:
//	String(const char *value = "");
//	String &operator=(const String &rhs);
//private:
//	char * data;
//};

//String & String::operator=(const String & rhs)
//{
//	if (this == &rhs)
//	{
//		return *this;
//	}
//
//	char * data_new = new char[strlen(rhs.data) + 1];
//	strcpy(data, rhs.data);
//	delete[] data;
//	data = data_new;
//	return *this;
//}
#pragma endregion

#pragma region 引用计数版本，版本1
//class String
//{
//public:
//	String(const char *value = "") :value_(new StringValue(value)) {} //这样的话，每次新建对象就算是指向同一个字符串还是会建立不同的对象，但是这里主要讨论的是拷贝之后的引用计数
//	String &operator=(const String &rhs)
//	{
//		if (value_ == rhs.value_)
//			return *this;
//
//		if (--value_->ref_count_ == 0)
//			delete value_;
//
//		value_ = rhs.value_;
//		++value_->ref_count_;
//		return *this;
//	}
//	String(const String& rhs) :value_(rhs.value_) { ++value_->ref_count_; }
//	~String()
//	{
//		if (--value_->ref_count_ == 0)
//			delete value_; //然后value_的析构函数会去delete掉实际的data_
//	}
//
//	//实现写时拷贝,这也是lazy原则的一个特例
//	const char & operator[](int index) const { return value_->data_[index]; } //const版本因为肯定是只读的，因此不会拷贝
//	char &operator[](int index) //C++的operator[]没有办法告知是读还是写，因此只能假设非const版本的全部是写
//	{
//		if (value_->ref_count_ > 1)
//		{
//			--value_->ref_count_;
//			value_ = new StringValue(value_->data_);
//			//value_->ref_count_ = 1; //这一步构造函数里面其实已经做了
//		}
//		return value_->data_[index];
//	}
//private:
//	struct StringValue
//	{
//		int ref_count_;
//		char *data_;
//		StringValue(const char *initValue);
//		~StringValue();
//	};
//	StringValue *value_;
//};
//
//String::StringValue::StringValue(const char * init_value)
//	:ref_count_(1)
//{
//	data_ = new char[strlen(init_value) + 1];
//	strcpy(data_, init_value);
//}
//
//String::StringValue::~StringValue()
//{
//	delete[] data_;
//}

//这个版本的问题参看main函数
#pragma endregion


#pragma region 版本2,增加shareable变量
class String
{
public:
	String(const char *value = "") :value_(new StringValue(value)) {} 
	String &operator=(const String &rhs)
	{
		if (value_ == rhs.value_)
			return *this;

		if (--value_->ref_count_ == 0)
			delete value_;

		value_ = rhs.value_;
		++value_->ref_count_;
		return *this;
	}
	String(const String& rhs) //这里需要判断了现在
	{
		if (!rhs.value_->shareable_)
		{
			value_ = new StringValue(rhs.value_->data_);
			return;
		}
		value_ = rhs.value_;
		++value_->ref_count_;
	}
	~String()
	{
		if (--value_->ref_count_ == 0)
			delete value_; 
	}

	const char & operator[](int index) const { return value_->data_[index]; } 
	char &operator[](int index) 
	{
		if (value_->ref_count_ > 1)
		{
			--value_->ref_count_;
			value_ = new StringValue(value_->data_);
		}
		//现在需要把这里设置一下
		value_->shareable_ = false; //写的时候关闭共享
		return value_->data_[index];
	}
private:
	struct StringValue
	{
		int ref_count_;
		char *data_;
		bool shareable_;
		StringValue(const char *initValue);
		~StringValue();
	};
	StringValue *value_;
};

String::StringValue::StringValue(const char * init_value)
	:ref_count_(1), shareable_(true)
{
	data_ = new char[strlen(init_value) + 1];
	strcpy(data_, init_value);
}

String::StringValue::~StringValue()
{
	delete[] data_;
}
#pragma endregion
