#pragma once
#include <typeinfo>

class GameObject {};
class SpaceShip :public GameObject {};
class SpaceStation :public GameObject {};
class Asteroid :public GameObject {};

//��������Ҫ������ײ���,���º���:
void checkForCollision(GameObject& object1, GameObject & object2)
{
	//α����
	//processCollision(object1,object2);//��Ҫһ�������ڶ�������ϵ��麯��
}

#pragma region ����1���麯��+RTTI
class GameObject
{
public:
	virtual void collide(GameObject&  other) = 0;
};

//����һ���쳣��
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
//����ͬ���� ����

//��������ȱ����:������װ��ÿ��collide����������֪����������ͬ�����еİ汾��������ʱ��ÿ��if else ����Ҫ�¼���Щ����������һ������ͻ��׳��쳣
#pragma endregion

#pragma region ����2��ֻ���麯��

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
		other.collide(*this); //���������Ǹ��ݾ�̬������ƥ�䣬�����*this��SpaceShip���Ի���ö�Ӧ�βεĺ���
	}
	virtual void collide(SpaceShip&  other)
	{
		//process xxx
	}
	virtual void collide(SpaceStation&  other) {}
	virtual void collide(Asteroid&  other) {}
};
//����������

//�����������RTTI��Ҳ�������쳣��
//ȱ����Ҳ�Ǳ���֪���Լ���ͬ���࣬���ҵ��������ʱ�����д��붼��Ҫ���£�������if else ��������Ҫ�����麯��
//�ܵ���˵��þ��ǲ�ʹ�ö��ε��ȡ�
#pragma endregion
