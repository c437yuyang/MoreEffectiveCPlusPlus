// 09_01_�����������з�ֹ�׳��쳣.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
using namespace std;
class Image
{
public:
	Image(const string& imageDataFileName) {}
};

class AudioClip
{
public:
	AudioClip(const string& audioDataFileName) {}
};

#pragma region ԭʼ�汾
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name), theAddress(addr), theImage(0), theAudioClip(0)
	{
		if (imageFilleName != "")
			theImage = new Image(imageFilleName);//����汾���
		if (audioFileName != "")
			theAudioClip = new AudioClip(audioFileName);//�����������new AudioClip�׳��쳣�ˣ���ôtheImage���ܱ���ȷ�ͷţ���ΪBookEntryû�й�����ȫ�����������������ᱻ���á�
	}

	~BookEntry()
	{
		delete theImage;
		delete theAudioClip;
	}


private:
	string theName;
	string theAddress;
	Image* theImage;
	AudioClip *theAudioClip;

};

//һ�ֵ��÷�ʽ
void TestBookEntryClass()
{
	BookEntry *pb = 0;
	try
	{
		pb = new BookEntry("aa", "bb", "cc", "dd");
	}
	catch (...) { delete pb; throw; } //������ʵ������û���õģ���Ϊnew��ʱ���׳��쳣��new���ص���NULL,deleteҲû�á�
	delete pb;
}

//��һ�ַ�ʽ
#include <memory>
void TestBookEntryClass1()
{
	unique_ptr<BookEntry> pb = 0;

	pb.reset(new BookEntry("aa", "bb", "cc", "dd")); //����Ҳ��û���õģ�new�ɹ�֮ǰ����û�ж�pb��ֵ

}

#pragma endregion

#pragma region �޸�1,ʹ��try catch��ֹ�ڴ�й¶�����ǲ�������const��Ա�����
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name), theAddress(addr), theImage(0), theAudioClip(0)
	{
		try //�޸ĳ���������ȷ�ܹ������ڴ�й©�����������������Ա��constָ�����ܣ���Ϊconstָ��ֻ���ڳ�Ա��ʼ���б��н��г�ʼ��������ʼ���б���ֻ������ڱ��ʽ�����ܴ������
		{
			if (imageFilleName != "")
				theImage = new Image(imageFilleName);
			if (audioFileName != "")
				theAudioClip = new AudioClip(audioFileName);
		}
		catch (...)
		{
			cleanUp();
			throw;
		}
	}

	~BookEntry()
	{
		cleanUp();
	}

private:
	void cleanUp()
	{
		delete theImage;
		delete theAudioClip;
	}

private:

	string theName;
	string theAddress;
	Image* theImage;
	AudioClip *theAudioClip;

};
#pragma endregion

#pragma region �޸�2,const��Ա��ʾ��
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name),
		theAddress(addr),
		theImage(imageFilleName != "" ? new Image(imageFilleName) : 0), //const��Աֻ����������ʼ�������ǾͲ��ܱ����ڴ�й©��
		theAudioClip(audioFileName != "" ? new AudioClip(audioFileName) : 0)
	{

	}

	~BookEntry()
	{
		cleanUp();
	}

private:
	void cleanUp()
	{
		delete theImage;
		delete theAudioClip;
	}

private:

	string theName;
	string theAddress;
	const Image* theImage; //������constָ����
	const AudioClip *theAudioClip;

};
#pragma endregion

#pragma region �޸�3,��Ϊ�����Ľ���취
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name),
		theAddress(addr),
		theImage(initImage(imageFilleName)), //��������������,����������ȱ���ǹ��캯�����ֳ��˺ü����֣�������ά��
		theAudioClip(initAudioClip(audioFileName)) 
	{

	}

	~BookEntry()
	{
		cleanUp();
	}

private:

	Image * initImage(const string&filename)
	{
		if (filename != "")return new Image(filename);
		return 0;
	}
	//�ڶ�����������ȷ��theImage��ʧ�ܵ�ʱ���ͷ�
	AudioClip* initAudioClip(const string& filename) 
	{
		try
		{
			if (filename != "")
				return new AudioClip(filename);
			return 0;
		}
		catch (const std::exception&)
		{
			delete theImage;
			throw;
		}
	}

	void cleanUp()
	{
		delete theImage;
		delete theAudioClip;
	}

private:

	string theName;
	string theAddress;
	const Image* theImage; //������constָ����
	const AudioClip *theAudioClip;

};
#pragma endregion

#pragma region �޸�4,ʹ��auto_ptr�����հ汾
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name),
		theAddress(addr),
		theImage(imageFilleName != "" ? new Image(imageFilleName) : 0), //����ֱ�Ӻ�����һ�����й��캯���Ĳ������ɡ�
		theAudioClip(audioFileName != "" ? new AudioClip(audioFileName) : 0)//�����������ʧ���ˣ�theImage��һ��������ɵĶ�����˻����theImage��������������˲�������ڴ�й©��
	{

	}

	//~BookEntry() //���ڲ���Ҫ����������
	//{
	//	
	//}
private:
	string theName;
	string theAddress;
	const unique_ptr<Image> theImage; //�ĳ�ʹ������ָ��
	const unique_ptr<AudioClip> theAudioClip;

};
#pragma endregion


int main()
{
	return 0;
}

