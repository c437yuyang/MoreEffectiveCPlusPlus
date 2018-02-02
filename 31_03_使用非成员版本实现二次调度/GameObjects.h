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