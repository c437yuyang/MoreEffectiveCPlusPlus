// 25_01_构造函数和非成员函数虚拟化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
class NLComonent
{
public:
	virtual NLComonent * clone() const = 0;//虚拟拷贝构造函数
	virtual std::ostream& print(std::ostream& s) const = 0; //虚拟非成员函数的实现方法
};

class TextBlock :public NLComonent
{
public:
	virtual TextBlock* clone() const { return new TextBlock(*this); }
	virtual std::ostream& print(std::ostream& s) const { return std::cout << "textblock" << std::endl; }//各自有不同的实现
};

class Graphic :public NLComonent
{
public:
	virtual Graphic* clone() const { return new Graphic(*this); }
	virtual std::ostream& print(std::ostream& s) const { return std::cout << "graphic" << std::endl; }
};

class NewsLetter
{
public:
	NewsLetter(std::istream &str); //假设有一个从istream读入生成对象的构造函数
	NewsLetter(const NewsLetter&rhs);
private:
	std::list<NLComonent*> components_;
};

//虚拟构造函数，其实并不是真正意义上的构造函数，是类似于工厂函数的实现方式
NewsLetter::NewsLetter(std::istream &str)
{
	while (str)
	{
		//根据读取到的信息创建指定的对象，就实现了在运行期创建不同的对象
		//虚拟构造函数就是根据指定的数据建立不同的对象
	}
}

//有了那些组件的虚拟拷贝构造函数，再来实现NewsLetter的拷贝构造函数
NewsLetter::NewsLetter(const NewsLetter& rhs)
{
	for (std::list<NLComonent*>::iterator it = components_.begin(); it != components_.end(); ++it)
	{
		components_.push_back((*it)->clone()); //这时运行期就会调用每个类应该调用的拷贝构造函数，虽然指针全部都是NLComponent*
	}
}

//如果要把operator<<实现成虚拟函数，写成成员函数(virtual ostream& operator<<(ostream &os))不合理，因为这样虽然能够实现多态
//但是需要str<<cout 这样使用，因此采用在类内定义一个业务逻辑的虚拟函数，外部调用即可。
inline //这里inline适合避免这样调用带来的开销。
std::ostream& operator<<(std::ostream& os, const NLComonent&component)
{
	return component.print(os);
}

int main()
{
	return 0;
}