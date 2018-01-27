// 25_01_���캯���ͷǳ�Ա�������⻯.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <list>
class NLComonent
{
public:
	virtual NLComonent * clone() const = 0;//���⿽�����캯��
	virtual std::ostream& print(std::ostream& s) const = 0; //����ǳ�Ա������ʵ�ַ���
};

class TextBlock :public NLComonent
{
public:
	virtual TextBlock* clone() const { return new TextBlock(*this); }
	virtual std::ostream& print(std::ostream& s) const { return std::cout << "textblock" << std::endl; }//�����в�ͬ��ʵ��
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
	NewsLetter(std::istream &str); //������һ����istream�������ɶ���Ĺ��캯��
	NewsLetter(const NewsLetter&rhs);
private:
	std::list<NLComonent*> components_;
};

//���⹹�캯������ʵ���������������ϵĹ��캯�����������ڹ���������ʵ�ַ�ʽ
NewsLetter::NewsLetter(std::istream &str)
{
	while (str)
	{
		//���ݶ�ȡ������Ϣ����ָ���Ķ��󣬾�ʵ�����������ڴ�����ͬ�Ķ���
		//���⹹�캯�����Ǹ���ָ�������ݽ�����ͬ�Ķ���
	}
}

//������Щ��������⿽�����캯��������ʵ��NewsLetter�Ŀ������캯��
NewsLetter::NewsLetter(const NewsLetter& rhs)
{
	for (std::list<NLComonent*>::iterator it = components_.begin(); it != components_.end(); ++it)
	{
		components_.push_back((*it)->clone()); //��ʱ�����ھͻ����ÿ����Ӧ�õ��õĿ������캯������Ȼָ��ȫ������NLComponent*
	}
}

//���Ҫ��operator<<ʵ�ֳ����⺯����д�ɳ�Ա����(virtual ostream& operator<<(ostream &os))��������Ϊ������Ȼ�ܹ�ʵ�ֶ�̬
//������Ҫstr<<cout ����ʹ�ã���˲��������ڶ���һ��ҵ���߼������⺯�����ⲿ���ü��ɡ�
inline //����inline�ʺϱ����������ô����Ŀ�����
std::ostream& operator<<(std::ostream& os, const NLComonent&component)
{
	return component.print(os);
}

int main()
{
	return 0;
}