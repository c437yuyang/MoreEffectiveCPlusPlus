#pragma once
#include <map>
#include <utility>
#include <string>
#include <memory>
class GameObject;
class SpaceShip;
class SpaceStation;
class Asteriod;

//定义一个异常类
class CollidWithUnkownObject
{
public:
	CollidWithUnkownObject(GameObject& obj1, GameObject &obj2) {}
};


namespace //无名命名空间，确保只属于当前编译文件
{
	void shipAsteriod(GameObject& lhs, GameObject& rhs);
	void shipStation(GameObject& lhs, GameObject& rhs);
	void stationAsteriod(GameObject& lhs, GameObject& rhs);
	//...以及对应的对称碰撞函数


	typedef void(*HitFunctionPtr)(GameObject&, GameObject&);
	typedef std::map<std::pair<std::string, std::string>, HitFunctionPtr> HitMap;
	std::pair<std::string, std::string> makeStringPair(const char*s1, const char *s2);
	HitMap * initializeCollisionMap();
	HitFunctionPtr lookup(const std::string&class1, const std::string&s2);

}



void ProcessCollision(GameObject&obj1, GameObject&obj2)
{
	HitFunctionPtr hfp = lookup(typeid(obj1).name(), typeid(obj2).name()); //现在这样来调用
	if (hfp) hfp(obj1, obj2);
	else throw CollidWithUnkownObject(obj1, obj2);
}


namespace
{
	std::pair<std::string, std::string> makeStringPair(const char*s1, const char *s2)
	{
		return std::pair<std::string, std::string>(s1, s2);
	}
}

namespace
{
	HitMap * initializeCollisionMap()
	{
		HitMap*phm = new HitMap;
		(*phm)[makeStringPair("SpaceShip", "Asteroid")] = shipAsteriod;
		//....
	}
}

namespace
{
	HitFunctionPtr lookup(const std::string&s1, const std::string&s2)
	{
		static std::unique_ptr<HitMap> collisionMap(initializeCollisionMap());
		HitMap::iterator iter = collisionMap->find(makeStringPair(s1.c_str(), s2.c_str()));
		if (iter == collisionMap->end())return NULL;
		return iter->second;
	}
}

//现在这样新增子类的时候就不需要全部重新编译了，也没有了RTTI 用于if else的混乱
//新增的时候只需要在initializeCollisionMap里面新增一个映射关系，processCollision所在命名空间中新增一个处理函数即可。


//现在我们的设计完全是静态的，假如我们想在游戏运行过程中增删查改对于碰撞处理函数的话，是不行的。于是我们换一个方式
//将映射关系放入一个类中，由它提供动态增删查看的功能。

class CollisionMap
{
public:
	typedef void(*HitFunctionPtr)(GameObject&, GameObject&);
	void AddEntry(const std::string&c1, const std::string &c2,
		HitFunctionPtr collisionFunction, bool symmetric = true); //symmetric自动增加对称的对应关系
	void RemoveEntry(const std::string&c1, const std::string &c2);
	HitFunctionPtr lookup(const std::string&s1, const std::string&s2);
	static CollisionMap& theCollisionMap; //限制只能有一个对象
private:
	CollisionMap();
	CollisionMap(const CollisionMap&);
};

//再来一个类，
class RegisterCollisionFunction
{
public:
	RegisterCollisionFunction(const std::string&c1, const std::string &c2,
		CollisionMap::HitFunctionPtr collisionFunction, bool symmetric = true)
	{
		CollisionMap::theCollisionMap.AddEntry(c1, c2, collisionFunction, symmetric);
	}
};

//现在每次用户只需要使用一个全局对象即可注册
RegisterCollisionFunction cf1("SpaceShip", "SpaceStation", &shipStation);