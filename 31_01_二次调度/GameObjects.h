#pragma once
#include <typeinfo>

class GameObject {};
class SpaceShip :public GameObject {};
class SpaceStation :public GameObject {};
class Asteroid :public GameObject {};

//假设现在要进行碰撞检测,以下函数:
void checkForCollision(GameObject& object1, GameObject & object2)
{
	//伪代码
	//processCollision(object1,object2);//需要一种作用于多个对象上的虚函数
}

#pragma region 方法1，虚函数+RTTI
class GameObject
{
public:
	virtual void collide(GameObject&  other) = 0;
};

//定义一个异常类
class CollidWithUnkownObject
{
public:
	CollidWithUnkownObject(GameObject& whatWeHit) {}
};

class SpaceShip :public GameObject
{
public:
	virtual void collide(GameObject&other)
	{
		const type_info&object_type = typeid(other);
		if (object_type == typeid(SpaceShip))
		{
			SpaceShip& ss = static_cast<SpaceShip&>(other);
			//process spaceship collide with spaceship
		}
		else if (object_type == typeid(SpaceStation))
		{
			SpaceStation &ss = static_cast<SpaceStation&>(other);
			//process
		}
		//else if() ...
		else
		{
			throw CollidWithUnkownObject(other);
		}

	}
};
//其他同胞类 类似

//这样做的缺点是:放弃封装，每个collide函数都必须知道所有其他同胞类中的版本。新增的时候，每个if else 都需要新加这些东西，并且一旦出错就会抛出异常
#pragma endregion

#pragma region 方法2，只用虚函数

class SpaceShip;
class SpaceStation;
class Asteroid;

class GameObject
{
public:
	virtual void collide(GameObject&  other) = 0;
	virtual void collide(SpaceShip&  other) = 0;
	virtual void collide(SpaceStation&  other) = 0;
	virtual void collide(Asteroid&  other) = 0;
};

class SpaceShip :public GameObject
{
public:
	virtual void collide(GameObject&  other)
	{
		other.collide(*this); //函数重载是根据静态类型来匹配，这里的*this是SpaceShip所以会调用对应形参的函数
	}
	virtual void collide(SpaceShip&  other)
	{
		//process xxx
	}
	virtual void collide(SpaceStation&  other) {}
	virtual void collide(Asteroid&  other) {}
};
//其他类类似

//这个方法不用RTTI，也不会抛异常。
//缺点是也是必须知道自己的同胞类，并且当新增类的时候所有代码都需要更新，甚至比if else 更烦，需要增加虚函数
//总的来说最好就是不使用二次调度。
#pragma endregion
