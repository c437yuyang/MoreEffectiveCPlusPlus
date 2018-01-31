#pragma once

#include <vector>

template<class T>
class Array2D
{
	class Array1D;
public:
	Array2D(int dim1, int dim2) :_dim1(dim1), _dim2(dim2), _data(std::vector<Array1D>(dim1, dim2)) {}
	Array1D& operator[](int index) { return _data[index]; } //这样用户使用的时候就可以[][]了
	const Array1D& operator[](int index) const { return _data[index]; }

public:
	class Array1D
	{
	public:
		//Array1D() {} //必须提供默认构造函数
		Array1D(int size) :_size(size), _1d_data(std::vector<T>(size)) {}
		T & operator[](int index) { return _1d_data[index]; }
		const T& operator[](int index) const { return _1d_data[index]; }
	private:
		std::vector<T> _1d_data; //这里选择用vector实现，简单一点
		int _size;
	};

private:
	std::vector<Array1D> _data;
	int _dim1, _dim2;
};