// 33_01_����β�������Ϊ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#pragma region �汾1
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

#pragma region �汾2��ʹ���麯��
class AbstractAnimal
{
public:
	virtual AbstractAnimal& operator=(const AbstractAnimal&rhs);
};

class Lizard :public AbstractAnimal
{
public:
	virtual	Lizard& operator=(const AbstractAnimal&rhs); //�麯��ֻ�ܸ��ķ������ͣ��������Ͳ��ܸ���
};
class Chicken :public AbstractAnimal
{
public:
	virtual	Chicken& operator=(const AbstractAnimal&rhs);
};
#pragma endregion

#pragma region �汾3������dynamic_cast
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
		const Lizard& rhs_liz = dynamic_cast<const Lizard&>(rhs);//�������ת��ʧ�ܵĻ����׳�bad_cast�쳣
		//����
	}
};
class Chicken :public AbstractAnimal
{
public:
	virtual	Chicken& operator=(const AbstractAnimal&rhs);
};
//����汾��������̫���ڰ�����ʹ��dynamic_cast
//�����ʱ������ֻ��liz1 = liz2������ֵ��

#pragma endregion

#pragma region �汾4,Ϊ�˵�������liz1 = liz2�������
class Lizard :public AbstractAnimal
{
public:
	virtual	Lizard& operator=(const AbstractAnimal&rhs)
	{
		const Lizard& rhs_liz = dynamic_cast<const Lizard&>(rhs);//�������ת��ʧ�ܵĻ����׳�bad_cast�쳣
		//���ڵ��õ�ʱ�����ֱ�ӵ���ǰ��
		return operator=(rhs_liz);
	}

	Lizard & operator=(const Lizard&rhs); //�������ṩһ�������汾�ĸ�ֵ������������liz1 = liz2�������ʱ��ֱ�ӵ�������汾���ͱ�����dynamic_cast

};

//���⻹������ʹ����dynamic_cast,��Ҫ�û�ÿ�ζ�׼���ò���bad_cast�쳣��

#pragma endregion

#pragma region �汾5
class AbstractAnimal
{
private: //���ڣ�������private
	AbstractAnimal& operator=(const AbstractAnimal&rhs);
};

class Lizard :public AbstractAnimal
{
public: //���ﻹ��public
	Lizard& operator=(const Lizard&rhs);//ֻ��ͬ����
};
class Chicken :public AbstractAnimal
{
public:
	Chicken& operator=(const Chicken&rhs);
};


#pragma endregion

#pragma region �汾6����Animalֱ�ӱ�ɳ�����


class AbstractAnimal
{
protected: //���ڣ�������protected
	AbstractAnimal& operator=(const AbstractAnimal&rhs);
public:
	virtual ~AbstractAnimal() = 0 {} //��һ����������������������ʵ����,��ʵ������Ϊ���������л���������������뱻����
};

class Animal :public AbstractAnimal
{
public:
	Animal& operator=(const Animal&rhs); //���������ʹﵽ����Ҫ���ͬ���Ϳ��Ը�ֵ����ͬ���Ͳ��ܸ�ֵ
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


//�����ĺô��������ڽ��������ĸ�ֵ���⣬���������� ǿ����ȷ���˳�����AbstractAnimal,ԭ����ʵ��Animal�̳е�ʱ��(������������ʱ���)������ʵ�������ν�Ĺ��Ե�����ʲô�����ھ���ǿ�ư���ȷ���˹��ԡ�
#pragma endregion


int main()
{

	//�汾1����
	{
		//���ڳ��ִ���ĵ���
		Lizard liz1, liz2;
		AbstractAnimal *pAnimal1 = &liz1;
		AbstractAnimal *pAnimal2 = &liz2;
		*pAnimal1 = *pAnimal2; //����ֻ�л��ಿ�ֱ������޸�
	}

	//�汾2����
	{


		//����
		Lizard liz1, liz2;
		AbstractAnimal *pAnimal1 = &liz1;
		AbstractAnimal *pAnimal2 = &liz2;
		*pAnimal1 = *pAnimal2; //������ȷ�������麯��


		Lizard liz;
		Chicken chick;
		AbstractAnimal *pAnimal1 = &liz;
		AbstractAnimal *pAnimal2 = &chick;
		*pAnimal1 = *pAnimal2; //������������Ҳ����ȷ���ˣ���Ϊ�ܹ����ҵ���Ӧ�麯��������Ӧ��Ҫ��ֹ��ͬ�����໥��ֵ
	}

	//�汾5����
	{
		//����������ͬ����֮�丳ֵû���⣬����

		Lizard liz1, liz2;
		Chicken chk1, chk2;
		liz1 = liz2;
		chk1 = chk2;
		AbstractAnimal *pAnimal1 = &liz1;
		AbstractAnimal *pAnimal2 = &chk1;
		*pAnimal1 = *pAnimal2; //������ֹ�˲�ͬ����ĸ�ֵ���ﵽĿ��

		//��������animalʵ��֮�丳ֵȴ����ֹ��
		AbstractAnimal a1, a2;
		a1 = a2;
		//������Ҳ������ȷʵ������ĸ�ֵ��������Ϊ��������Ҫ���û���ĸ�ֵ����������ɸ��ಿ�ֵĿ���
	}

	return 0;
}

