// 33_01_将非尾端类设计为抽象类.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#pragma region 版本1
class AbstractAnimal
{
public:
	AbstractAnimal& operator=(const AbstractAnimal&rhs);
};

class Lizard :public AbstractAnimal
{
public:
	Lizard& operator=(const Lizard&rhs);
};
class Chicken :public AbstractAnimal
{
public:
	Chicken& operator=(const Chicken&rhs);

};


#pragma endregion

#pragma region 版本2，使用虚函数
class AbstractAnimal
{
public:
	virtual AbstractAnimal& operator=(const AbstractAnimal&rhs);
};

class Lizard :public AbstractAnimal
{
public:
	virtual	Lizard& operator=(const AbstractAnimal&rhs); //虚函数只能更改返回类型，参数类型不能更改
};
class Chicken :public AbstractAnimal
{
public:
	virtual	Chicken& operator=(const AbstractAnimal&rhs);
};
#pragma endregion

#pragma region 版本3，增加dynamic_cast
class AbstractAnimal
{
public:
	virtual AbstractAnimal& operator=(const AbstractAnimal&rhs);
};

class Lizard :public AbstractAnimal
{
public:

	virtual	Lizard& operator=(const AbstractAnimal&rhs)
	{
		const Lizard& rhs_liz = dynamic_cast<const Lizard&>(rhs);//现在如果转型失败的话会抛出bad_cast异常
		//处理
	}
};
class Chicken :public AbstractAnimal
{
public:
	virtual	Chicken& operator=(const AbstractAnimal&rhs);
};
//这个版本的问题是太过于昂贵了使用dynamic_cast
//大多数时候我们只是liz1 = liz2这样赋值。

#pragma endregion

#pragma region 版本4,为了单独处理liz1 = liz2这种情况
class Lizard :public AbstractAnimal
{
public:
	virtual	Lizard& operator=(const AbstractAnimal&rhs)
	{
		const Lizard& rhs_liz = dynamic_cast<const Lizard&>(rhs);//现在如果转型失败的话会抛出bad_cast异常
		//现在调用的时候可以直接调用前者
		return operator=(rhs_liz);
	}

	Lizard & operator=(const Lizard&rhs); //现在再提供一个正常版本的赋值操作，当遇到liz1 = liz2这种情况时会直接调用这个版本，就避免了dynamic_cast

};

//问题还是在于使用了dynamic_cast,需要用户每次都准备好捕获bad_cast异常。

#pragma endregion

#pragma region 版本5
class AbstractAnimal
{
private: //现在，这里变成private
	AbstractAnimal& operator=(const AbstractAnimal&rhs);
};

class Lizard :public AbstractAnimal
{
public: //这里还是public
	Lizard& operator=(const Lizard&rhs);//只能同类型
};
class Chicken :public AbstractAnimal
{
public:
	Chicken& operator=(const Chicken&rhs);
};


#pragma endregion

#pragma region 版本6，将Animal直接变成抽象类


class AbstractAnimal
{
protected: //现在，这里变成protected
	AbstractAnimal& operator=(const AbstractAnimal&rhs);
public:
	virtual ~AbstractAnimal() = 0 {} //给一个纯虚析构函数表明不能实例化,给实现是因为在派生类中基类的析构函数必须被调用
};

class Animal :public AbstractAnimal
{
public:
	Animal& operator=(const Animal&rhs); //现在这个类就达到了所要求的同类型可以赋值，不同类型不能赋值
};

class Lizard :public AbstractAnimal
{
public:
	Lizard& operator=(const Lizard&rhs);
};
class Chicken :public AbstractAnimal
{
public:
	Chicken& operator=(const Chicken&rhs);
};


//这个类的好处不仅在于解决了上面的赋值问题，还帮助我们 强制性确定了抽象类AbstractAnimal,原来其实从Animal继承的时候(更多是在其他时候把)，你其实不清楚所谓的共性到底是什么，现在就是强制帮你确定了共性。
#pragma endregion


int main()
{

	//版本1错误
	{
		//现在出现错误的调用
		Lizard liz1, liz2;
		AbstractAnimal *pAnimal1 = &liz1;
		AbstractAnimal *pAnimal2 = &liz2;
		*pAnimal1 = *pAnimal2; //现在只有基类部分被拷贝修改
	}

	//版本2错误
	{


		//但是
		Lizard liz1, liz2;
		AbstractAnimal *pAnimal1 = &liz1;
		AbstractAnimal *pAnimal2 = &liz2;
		*pAnimal1 = *pAnimal2; //现在正确了有了虚函数


		Lizard liz;
		Chicken chick;
		AbstractAnimal *pAnimal1 = &liz;
		AbstractAnimal *pAnimal2 = &chick;
		*pAnimal1 = *pAnimal2; //但是现在这样也是正确的了，因为能够查找到对应虚函数，我们应该要禁止不同类型相互赋值
	}

	//版本5问题
	{
		//现在两个相同对象之间赋值没问题，但是

		Lizard liz1, liz2;
		Chicken chk1, chk2;
		liz1 = liz2;
		chk1 = chk2;
		AbstractAnimal *pAnimal1 = &liz1;
		AbstractAnimal *pAnimal2 = &chk1;
		*pAnimal1 = *pAnimal2; //报错，禁止了不同对象的赋值，达到目的

		//但是两个animal实体之间赋值却被禁止了
		AbstractAnimal a1, a2;
		a1 = a2;
		//而且它也不能正确实现子类的赋值操作，因为派生类需要调用基类的赋值操作函数完成父类部分的拷贝
	}

	return 0;
}

