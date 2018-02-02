#pragma once
#include <map>
#include <utility>
#include <string>
#include <memory>
class GameObject;
class SpaceShip;
class SpaceStation;
class Asteriod;

//����һ���쳣��
class CollidWithUnkownObject
{
public:
	CollidWithUnkownObject(GameObject& obj1, GameObject &obj2) {}
};


namespace //���������ռ䣬ȷ��ֻ���ڵ�ǰ�����ļ�
{
	void shipAsteriod(GameObject& lhs, GameObject& rhs);
	void shipStation(GameObject& lhs, GameObject& rhs);
	void stationAsteriod(GameObject& lhs, GameObject& rhs);
	//...�Լ���Ӧ�ĶԳ���ײ����


	typedef void(*HitFunctionPtr)(GameObject&, GameObject&);
	typedef std::map<std::pair<std::string, std::string>, HitFunctionPtr> HitMap;
	std::pair<std::string, std::string> makeStringPair(const char*s1, const char *s2);
	HitMap * initializeCollisionMap();
	HitFunctionPtr lookup(const std::string&class1, const std::string&s2);

}



void ProcessCollision(GameObject&obj1, GameObject&obj2)
{
	HitFunctionPtr hfp = lookup(typeid(obj1).name(), typeid(obj2).name()); //��������������
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

//�����������������ʱ��Ͳ���Ҫȫ�����±����ˣ�Ҳû����RTTI ����if else�Ļ���
//������ʱ��ֻ��Ҫ��initializeCollisionMap��������һ��ӳ���ϵ��processCollision���������ռ�������һ�����������ɡ�