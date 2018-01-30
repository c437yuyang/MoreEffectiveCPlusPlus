#pragma once
#include <cstring>
//������������������:
// 1.������ٶ��еĶ���û��ʹ�õ�ʱ���Զ����١�
// 2.����ܶ��������ͬ��ֵ���洢������˷ѡ�

#pragma region ��ͨString���͵�����

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

#pragma region ���ü����汾���汾1
//class String
//{
//public:
//	String(const char *value = "") :value_(new StringValue(value)) {} //�����Ļ���ÿ���½����������ָ��ͬһ���ַ������ǻὨ����ͬ�Ķ��󣬵���������Ҫ���۵��ǿ���֮������ü���
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
//			delete value_; //Ȼ��value_������������ȥdelete��ʵ�ʵ�data_
//	}
//
//	//ʵ��дʱ����,��Ҳ��lazyԭ���һ������
//	const char & operator[](int index) const { return value_->data_[index]; } //const�汾��Ϊ�϶���ֻ���ģ���˲��´��
//	char &operator[](int index) //C++��operator[]û�а취��֪�Ƕ�����д�����ֻ�ܼ����const�汾��ȫ����д
//	{
//		if (value_->ref_count_ > 1)
//		{
//			--value_->ref_count_;
//			value_ = new StringValue(value_->data_);
//			//value_->ref_count_ = 1; //��һ�����캯��������ʵ�Ѿ�����
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

//����汾������ο�main����
#pragma endregion


#pragma region �汾2,����shareable����
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
	String(const String& rhs) //������Ҫ�ж�������
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
		//������Ҫ����������һ��
		value_->shareable_ = false; //д��ʱ��رչ���
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
