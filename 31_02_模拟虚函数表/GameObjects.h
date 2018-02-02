#pragma once
#include <typeinfo>
#include <map>
#include <string>
#include <memory>
class GameObject {};
class SpaceShip :public GameObject {};
class SpaceStation :public GameObject {};
class Asteroid :public GameObject {};

class SpaceShip;
class SpaceStation;
class Asteroid;

//定义一个异常类
class CollidWithUnkownObject
{
public:
	CollidWithUnkownObject(GameObject& whatWeHit) {}
};

#pragma region 版本1
class GameObject
{
public:
	virtual void collide(GameObject&  other) = 0;
};

class SpaceShip :public GameObject
{
public:
	virtual void collide(GameObject&  other);

	virtual void hitSpaceShips(SpaceShip&  other)
	{
		//process xxx
	}
	virtual void hitSpaceStation(SpaceStation&  other) {}
	virtual void hitAsteroid(Asteroid&  other) {}

private: //现在新建一个映射表
	typedef void(SpaceShip::*HitFuntionPtr)(GameObject&);
	static HitFuntionPtr lookup(const GameObject&whatWeHit);//查找函数
	typedef std::map<std::string, HitFuntionPtr> HitMap; //使用一个map座位查找表
														 //static HitMap  initializeCollisionMap(); //这样的话需要拷贝一次
	static HitMap* initializeCollisionMap(); //改为返回指针，但不知道何时应该释放，因此用auto_ptr接收

};

//现在SpaceShip::collide实现如下:
void SpaceShip::collide(GameObject& other)
{
	HitFuntionPtr hfp = lookup(other);
	if (hfp)
	{
		(this->*hfp)(other);
	}
	else
	{
		throw CollidWithUnkownObject(other);
	}
}

SpaceShip::HitFuntionPtr SpaceShip::lookup(const GameObject&whatWeHit)
{
	static std::unique_ptr<HitMap> collisionMap(initializeCollisionMap()); //静态对象保证只被初始化一次

	HitMap::iterator mapEntry = collisionMap->find(typeid(whatWeHit).name());
	if (mapEntry == collisionMap->end()) return NULL;
	return (*mapEntry).second;
}

SpaceShip::HitMap* SpaceShip::initializeCollisionMap()
{
	HitMap* phm = new HitMap;
	(*phm)["SpaceShip"] = &hitSpaceShips;//现在是会报错的，因为参数类型是不一致的，声明的是SpaceShip& 而HitFunctionPtr的参数类型必须是GameObject
										 //使用reinterpret_cast 会带来非常难以定位的错误
}
#pragma endregion


#pragma region 版本2

class GameObject
{
public:
	virtual void collide(GameObject&  other) = 0;
};

class SpaceShip :public GameObject
{
public:
	virtual void collide(GameObject&  other);

	virtual void hitSpaceShips(GameObject&  other)//这里直接换成GameObject
	{
		//process xxx
	}
	virtual void hitSpaceStation(GameObject&  other) {}
	virtual void hitAsteroid(GameObject&  other) {}

private: //现在新建一个映射表
	typedef void(SpaceShip::*HitFuntionPtr)(GameObject&);
	static HitFuntionPtr lookup(const GameObject&whatWeHit);//查找函数
	typedef std::map<std::string, HitFuntionPtr> HitMap; //使用一个map座位查找表
														 //static HitMap  initializeCollisionMap(); //这样的话需要拷贝一次
	static HitMap* initializeCollisionMap(); //改为返回指针，但不知道何时应该释放，因此用auto_ptr接收

};

//现在SpaceShip::collide实现如下:
void SpaceShip::collide(GameObject& other)
{
	HitFuntionPtr hfp = lookup(other);
	if (hfp)
	{
		(this->*hfp)(other);
	}
	else
	{
		throw CollidWithUnkownObject(other);
	}
}

SpaceShip::HitFuntionPtr SpaceShip::lookup(const GameObject&whatWeHit)
{
	static std::unique_ptr<HitMap> collisionMap(initializeCollisionMap()); //静态对象保证只被初始化一次

	HitMap::iterator mapEntry = collisionMap->find(typeid(whatWeHit).name());
	if (mapEntry == collisionMap->end()) return NULL;
	return (*mapEntry).second;
}

SpaceShip::HitMap* SpaceShip::initializeCollisionMap()
{
	HitMap* phm = new HitMap;
	(*phm)["SpaceShip"] = &hitSpaceShips; //现在可以了，只需要在具体函数实现里面稍微改一下
	(*phm)["SpaceStation"] = &hitSpaceStation;
	(*phm)["Asteroid"] = &hitAsteroid;
	return phm;
}

//现在实现内部做转换即可
void SpaceShip::hitSpaceShips(GameObject& other)
{
	SpaceShip& ss = dynamic_cast<SpaceShip &>(other);
	//process ....
}

//其他的类似


//现在一切都能执行了，但是缺点是，新增类的时候，map里面还是需要变化，所有人都需要重新编译
//问题，这个版本相比于只使用虚函数的二次调度来说，不一样需要知道所有同胞类的存在吗？而且也用了RTTI,感觉没有什么优势

#pragma endregion



