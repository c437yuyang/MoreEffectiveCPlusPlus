// ex_09_03_�������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//ָ��:
// 1.���԰�ȫ
// 2.����ʹ��
// 3.��Ч��(�ռ��ʱ��)

#pragma region �汾1
//class Widget
//{
//public:
//	Widget() { ++obj_num_; }
//	Widget(const Widget& rhs) { ++obj_num_; } //�����˿���ctor
//	~Widget() { --obj_num_; }
//	static int how_many() { return obj_num_; }
//private:
//	static int obj_num_;
//};
//int Widget::obj_num_ = 0;

#pragma endregion


#pragma region �汾2��������������
//class Counter
//{
//public:
//	Counter() { ++obj_num_; }
//	Counter(const Counter& rhs) { ++obj_num_; } //�����˿���ctor
//	~Counter() { --obj_num_; }
//	static size_t how_many() { return obj_num_; }
//private:
//	static size_t obj_num_;
//};
//size_t Counter::obj_num_ = 0;
//
////����1:public�̳�
//class Widget :public Counter
//{
//
//};
////����2:���
//class Widget
//{
//private:
//	Counter c;
//};

//�����ǣ����ڲ��������ٸ��࣬�����õ�һ��static obj_num_;
#pragma endregion

#pragma region �汾3������templateʵ�ֲ�ͬ���ò�ͬstatic��Ա

//template<class T>
//class Counter
//{
//public:
//	Counter() { ++obj_num_; }
//	Counter(const Counter& rhs) { ++obj_num_; } //�����˿���ctor
//	~Counter() { --obj_num_; }
//	static size_t how_many() { return obj_num_; }
//private:
//	static size_t obj_num_;
//};
//template<class T>
//size_t Counter<T>::obj_num_ = 0;
//
////����1:public�̳�
//class Widget :public Counter<Widget>
//{
//};
////����2:���
//class Widget
//{
//public:
//	static size_t how_many() { return Counter<Widget>::how_many(); } //����Ҫָ�����ò���
//private:
//	Counter<Widget> c;
//};

#pragma endregion

#pragma region �汾4����ϸ����public�̳�
//1.Ϊ�˰�ȫ��Ӧ����virtual dtor,��ֹ����ɾ��ָ���������ĸ���ָ�����
//2.Ϊ��Ч�ʣ�����virtual dtor��ÿ������֮�󶼻Ậ����Ӧ�Ĵ���(vptr,vtbl)
//3.���Ӧ��virtual����Ҫ����base class pointer ɾ��derived class object�Ļ���ֻ��private Counter�е�operator delete

class Widget :public Counter<Widget>
{
};

template<class T>
class Counter
{
public:
	Counter() { ++obj_num_; }
	Counter(const Counter& rhs) { ++obj_num_; } //�����˿���ctor
	~Counter() { --obj_num_; }
	static size_t how_many() { return obj_num_; }
private:
	void operator delete(void *); //private
	static size_t obj_num_;
};
template<class T>
size_t Counter<T>::obj_num_ = 0;
//��������һ��
Counter<Widget> *pw = new Widget; //��������Ҳ������,��Ϊoperator delete��operator new�ǳɶԵ�

//�������ʹ��public �̳��ǲ�����ģ�����
#pragma endregion


#pragma region �汾5����ϸ������ϵķ�ʽ
//1.��Ч������˵��Counterû��non-static data member����˴�С��1
//2.����Ч�ʾ�ȡ����Widget�����ݵĴ�С��
//���Widget�����ֻ��һ��int��һ��short����ô����û����һ���ֽڣ�Ҳ��Ҫ���뵽8������Ҳ��8��������������û��Ӱ�졣
//���ܵ���˵ռ�˿ռ䡣
#pragma endregion

#pragma region �汾6��˽�м̳�
//private�̳У����ȿ��Ա���base pointerָ��derived class objects
//��β�ռ�ÿռ��С���������õ�ѡ��
class Widget :private Counter<Widget> //��Ϊprivate�̳�
{
public: //��ʾ���ã���Ȼprivate�̳о���private����
	static size_t how_many() { return Counter<Widget>::how_many(); }

};

template<class T>
class Counter
{
public:
	Counter() { ++obj_num_; }
	Counter(const Counter& rhs) { ++obj_num_; } //�����˿���ctor
	~Counter() { --obj_num_; }
	static size_t how_many() { return obj_num_; }
private:
	void operator delete(void *); //private
	static size_t obj_num_;
};
template<class T>
size_t Counter<T>::obj_num_ = 0;


#pragma endregion


#pragma region �汾7��������ټ̳���Widget
class Widget :private Counter<Widget> //��Ϊprivate�̳�
{
public: //��ʾ���ã���Ȼprivate�̳о���private����
	//static size_t how_many() { return Counter<Widget>::how_many(); }
	//����
	using Counter<Widget>::how_many;

};

template<class T>
class Counter
{
public:
	Counter() { ++obj_num_; }
	Counter(const Counter& rhs) { ++obj_num_; } //�����˿���ctor
	~Counter() { --obj_num_; }
	static size_t how_many() { return obj_num_; }
private:
	void operator delete(void *); //private
	static size_t obj_num_;
};
template<class T>
size_t Counter<T>::obj_num_ = 0;

class SpecialWidget :public Widget, private Counter<SpecialWidget> 
	//��ʱ����һ�μ̳У���ô�������������Counterһ����Counter<Widget>,һ����Counter<SpecialWidget>
	//������ȷ�Ŀ϶���Counter<SpecialWidget>,�����ʾָ�����ã���Ҫע�����Counter<Widget>Ҳ����������������Ķ�����Ŀ��
{
public:
	static size_t how_many()
	{
		return Counter<SpecialWidget>::how_many();
	}
};
#pragma endregion


int main()
{
	return 0;
}

