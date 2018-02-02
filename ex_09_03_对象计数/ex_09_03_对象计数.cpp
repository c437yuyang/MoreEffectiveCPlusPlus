// ex_09_03_对象计数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//指标:
// 1.绝对安全
// 2.容易使用
// 3.有效率(空间和时间)

#pragma region 版本1
//class Widget
//{
//public:
//	Widget() { ++obj_num_; }
//	Widget(const Widget& rhs) { ++obj_num_; } //别忘了拷贝ctor
//	~Widget() { --obj_num_; }
//	static int how_many() { return obj_num_; }
//private:
//	static int obj_num_;
//};
//int Widget::obj_num_ = 0;

#pragma endregion


#pragma region 版本2，适用于其他类
//class Counter
//{
//public:
//	Counter() { ++obj_num_; }
//	Counter(const Counter& rhs) { ++obj_num_; } //别忘了拷贝ctor
//	~Counter() { --obj_num_; }
//	static size_t how_many() { return obj_num_; }
//private:
//	static size_t obj_num_;
//};
//size_t Counter::obj_num_ = 0;
//
////做法1:public继承
//class Widget :public Counter
//{
//
//};
////做法2:组合
//class Widget
//{
//private:
//	Counter c;
//};

//问题是，现在不管来多少个类，都是用的一个static obj_num_;
#pragma endregion

#pragma region 版本3，利用template实现不同类用不同static成员

//template<class T>
//class Counter
//{
//public:
//	Counter() { ++obj_num_; }
//	Counter(const Counter& rhs) { ++obj_num_; } //别忘了拷贝ctor
//	~Counter() { --obj_num_; }
//	static size_t how_many() { return obj_num_; }
//private:
//	static size_t obj_num_;
//};
//template<class T>
//size_t Counter<T>::obj_num_ = 0;
//
////做法1:public继承
//class Widget :public Counter<Widget>
//{
//};
////做法2:组合
//class Widget
//{
//public:
//	static size_t how_many() { return Counter<Widget>::how_many(); } //还需要指明调用才行
//private:
//	Counter<Widget> c;
//};

#pragma endregion

#pragma region 版本4，详细讨论public继承
//1.为了安全，应该有virtual dtor,防止出现删除指向子类对象的父类指针出错
//2.为了效率，有了virtual dtor，每个子类之后都会含有相应的代价(vptr,vtbl)
//3.因此应该virtual，想要避免base class pointer 删除derived class object的话，只能private Counter中的operator delete

class Widget :public Counter<Widget>
{
};

template<class T>
class Counter
{
public:
	Counter() { ++obj_num_; }
	Counter(const Counter& rhs) { ++obj_num_; } //别忘了拷贝ctor
	~Counter() { --obj_num_; }
	static size_t how_many() { return obj_num_; }
private:
	void operator delete(void *); //private
	static size_t obj_num_;
};
template<class T>
size_t Counter<T>::obj_num_ = 0;
//但是这样一来
Counter<Widget> *pw = new Widget; //这样调用也不行了,因为operator delete和operator new是成对的

//因此最终使用public 继承是不合理的，放弃
#pragma endregion


#pragma region 版本5，详细讨论组合的方式
//1.从效率上来说，Counter没有non-static data member，因此大小是1
//2.所以效率就取决于Widget内数据的大小了
//如果Widget里面就只有一个int和一个short，那么就算没有这一个字节，也需要对齐到8，有了也是8，因此这种情况下没有影响。
//但总的来说占了空间。
#pragma endregion

#pragma region 版本6，私有继承
//private继承，首先可以避免base pointer指向derived class objects
//其次不占用空间大小，因此是最好的选择。
class Widget :private Counter<Widget> //改为private继承
{
public: //显示调用，不然private继承就是private得了
	static size_t how_many() { return Counter<Widget>::how_many(); }

};

template<class T>
class Counter
{
public:
	Counter() { ++obj_num_; }
	Counter(const Counter& rhs) { ++obj_num_; } //别忘了拷贝ctor
	~Counter() { --obj_num_; }
	static size_t how_many() { return obj_num_; }
private:
	void operator delete(void *); //private
	static size_t obj_num_;
};
template<class T>
size_t Counter<T>::obj_num_ = 0;


#pragma endregion


#pragma region 版本7，别的类再继承自Widget
class Widget :private Counter<Widget> //改为private继承
{
public: //显示调用，不然private继承就是private得了
	//static size_t how_many() { return Counter<Widget>::how_many(); }
	//或者
	using Counter<Widget>::how_many;

};

template<class T>
class Counter
{
public:
	Counter() { ++obj_num_; }
	Counter(const Counter& rhs) { ++obj_num_; } //别忘了拷贝ctor
	~Counter() { --obj_num_; }
	static size_t how_many() { return obj_num_; }
private:
	void operator delete(void *); //private
	static size_t obj_num_;
};
template<class T>
size_t Counter<T>::obj_num_ = 0;

class SpecialWidget :public Widget, private Counter<SpecialWidget> 
	//这时再来一次继承，那么这个对象有两个Counter一个是Counter<Widget>,一个是Counter<SpecialWidget>
	//但是正确的肯定是Counter<SpecialWidget>,因此显示指明调用，需要注意的是Counter<Widget>也包含了其所有子类的对象数目。
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

