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

//����һ���쳣��
class CollidWithUnkownObject
{
public:
	CollidWithUnkownObject(GameObject& whatWeHit) {}
};

#pragma region �汾1
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

private: //�����½�һ��ӳ���
	typedef void(SpaceShip::*HitFuntionPtr)(GameObject&);
	static HitFuntionPtr lookup(const GameObject&whatWeHit);//���Һ���
	typedef std::map<std::string, HitFuntionPtr> HitMap; //ʹ��һ��map��λ���ұ�
														 //static HitMap  initializeCollisionMap(); //�����Ļ���Ҫ����һ��
	static HitMap* initializeCollisionMap(); //��Ϊ����ָ�룬����֪����ʱӦ���ͷţ������auto_ptr����

};

//����SpaceShip::collideʵ������:
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
	static std::unique_ptr<HitMap> collisionMap(initializeCollisionMap()); //��̬����ֻ֤����ʼ��һ��

	HitMap::iterator mapEntry = collisionMap->find(typeid(whatWeHit).name());
	if (mapEntry == collisionMap->end()) return NULL;
	return (*mapEntry).second;
}

SpaceShip::HitMap* SpaceShip::initializeCollisionMap()
{
	HitMap* phm = new HitMap;
	(*phm)["SpaceShip"] = &hitSpaceShips;//�����ǻᱨ��ģ���Ϊ���������ǲ�һ�µģ���������SpaceShip& ��HitFunctionPtr�Ĳ������ͱ�����GameObject
										 //ʹ��reinterpret_cast ������ǳ����Զ�λ�Ĵ���
}
#pragma endregion


#pragma region �汾2

class GameObject
{
public:
	virtual void collide(GameObject&  other) = 0;
};

class SpaceShip :public GameObject
{
public:
	virtual void collide(GameObject&  other);

	virtual void hitSpaceShips(GameObject&  other)//����ֱ�ӻ���GameObject
	{
		//process xxx
	}
	virtual void hitSpaceStation(GameObject&  other) {}
	virtual void hitAsteroid(GameObject&  other) {}

private: //�����½�һ��ӳ���
	typedef void(SpaceShip::*HitFuntionPtr)(GameObject&);
	static HitFuntionPtr lookup(const GameObject&whatWeHit);//���Һ���
	typedef std::map<std::string, HitFuntionPtr> HitMap; //ʹ��һ��map��λ���ұ�
														 //static HitMap  initializeCollisionMap(); //�����Ļ���Ҫ����һ��
	static HitMap* initializeCollisionMap(); //��Ϊ����ָ�룬����֪����ʱӦ���ͷţ������auto_ptr����

};

//����SpaceShip::collideʵ������:
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
	static std::unique_ptr<HitMap> collisionMap(initializeCollisionMap()); //��̬����ֻ֤����ʼ��һ��

	HitMap::iterator mapEntry = collisionMap->find(typeid(whatWeHit).name());
	if (mapEntry == collisionMap->end()) return NULL;
	return (*mapEntry).second;
}

SpaceShip::HitMap* SpaceShip::initializeCollisionMap()
{
	HitMap* phm = new HitMap;
	(*phm)["SpaceShip"] = &hitSpaceShips; //���ڿ����ˣ�ֻ��Ҫ�ھ��庯��ʵ��������΢��һ��
	(*phm)["SpaceStation"] = &hitSpaceStation;
	(*phm)["Asteroid"] = &hitAsteroid;
	return phm;
}

//����ʵ���ڲ���ת������
void SpaceShip::hitSpaceShips(GameObject& other)
{
	SpaceShip& ss = dynamic_cast<SpaceShip &>(other);
	//process ....
}

//����������


//����һ�ж���ִ���ˣ�����ȱ���ǣ��������ʱ��map���滹����Ҫ�仯�������˶���Ҫ���±���
//���⣬����汾�����ֻʹ���麯���Ķ��ε�����˵����һ����Ҫ֪������ͬ����Ĵ����𣿶���Ҳ����RTTI,�о�û��ʲô����

#pragma endregion



