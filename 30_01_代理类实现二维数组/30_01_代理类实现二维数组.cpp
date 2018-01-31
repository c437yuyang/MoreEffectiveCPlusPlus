// 30_01_代理类实现二维数组.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Array2D.h"
#include <iostream>

int main()
{

	Array2D<float> arr2d(10, 20);
	std::cout << arr2d[0][1] << std::endl;

    return 0;
}

