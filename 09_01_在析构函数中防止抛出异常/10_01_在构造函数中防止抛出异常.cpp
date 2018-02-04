// 09_01_在析构函数中防止抛出异常.cpp : 定义控制台应用程序的入口点。
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

#pragma region 原始版本
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name), theAddress(addr), theImage(0), theAudioClip(0)
	{
		if (imageFilleName != "")
			theImage = new Image(imageFilleName);//这个版本最简单
		if (audioFileName != "")
			theAudioClip = new AudioClip(audioFileName);//但是如果这里new AudioClip抛出异常了，那么theImage不能被正确释放，因为BookEntry没有构造完全，它的析构函数不会被调用。
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

//一种调用方式
void TestBookEntryClass()
{
	BookEntry *pb = 0;
	try
	{
		pb = new BookEntry("aa", "bb", "cc", "dd");
	}
	catch (...) { delete pb; throw; } //但是其实这里是没有用的，因为new的时候抛出异常，new返回的是NULL,delete也没用。
	delete pb;
}

//另一种方式
#include <memory>
void TestBookEntryClass1()
{
	unique_ptr<BookEntry> pb = 0;

	pb.reset(new BookEntry("aa", "bb", "cc", "dd")); //这样也是没有用的，new成功之前，都没有对pb赋值

}

#pragma endregion

#pragma region 修改1,使用try catch防止内存泄露，但是不能用于const成员的情况
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name), theAddress(addr), theImage(0), theAudioClip(0)
	{
		try //修改成这样，的确能够避免内存泄漏，但是如果是两个成员是const指针则不能，因为const指针只能在成员初始化列表中进行初始化。而初始化列表中只允许存在表达式，不能存在语句
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

#pragma region 修改2,const成员的示例
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name),
		theAddress(addr),
		theImage(imageFilleName != "" ? new Image(imageFilleName) : 0), //const成员只能这样来初始化，但是就不能避免内存泄漏了
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
	const Image* theImage; //现在是const指针了
	const AudioClip *theAudioClip;

};
#pragma endregion

#pragma region 修改3,较为繁琐的解决办法
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name),
		theAddress(addr),
		theImage(initImage(imageFilleName)), //现在这样来调用,但是这样的缺点是构造函数被分成了好几部分，不利于维护
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
	//第二个函数必须确保theImage在失败的时候被释放
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
	const Image* theImage; //现在是const指针了
	const AudioClip *theAudioClip;

};
#pragma endregion

#pragma region 修改4,使用auto_ptr的最终版本
class BookEntry
{
public:
	BookEntry(const string&name, const string&addr, const string& imageFilleName, const string& audioFileName)
		:theName(name),
		theAddress(addr),
		theImage(imageFilleName != "" ? new Image(imageFilleName) : 0), //现在直接和往常一样进行构造函数的操作即可。
		theAudioClip(audioFileName != "" ? new AudioClip(audioFileName) : 0)//但是这里就算失败了，theImage是一个构造完成的对象，因此会调用theImage的析构函数，因此不会出现内存泄漏。
	{

	}

	//~BookEntry() //现在不需要析构函数了
	//{
	//	
	//}
private:
	string theName;
	string theAddress;
	const unique_ptr<Image> theImage; //改成使用智能指针
	const unique_ptr<AudioClip> theAudioClip;

};
#pragma endregion


int main()
{
	return 0;
}

