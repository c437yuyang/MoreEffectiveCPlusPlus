// 19_临时对象.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{

	size_t countChar(const string & str, char ch);
	countChar("aa",'a'); //对于常量引用，会建立临时对象(隐式类型转换)并用str来初始化临时对象
	void uppercasify(string &str);

	char subBookPlug[] = "aaa";
	
	//uppercasify(subBookPlug); //报错，非常量引用，不会建立临时对象。
	//因为如果建立了临时对象的话，修改的也是临时对象的值，没用，所以直接就禁止这样做了编译器
	uppercasify(string("aaa")); //直接传对象不会受影响，只出现在可能发生隐式类型转换的时候

    return 0;

}

