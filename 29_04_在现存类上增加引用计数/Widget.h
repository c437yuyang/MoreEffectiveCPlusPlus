#pragma once

#include <iostream>

class Widget //对于一个现存类，不可能像StringValue一样让它去继承自RCObjcet
{
public:
	Widget(int size) :size_(size) {}
	Widget(const Widget& rhs):size_(rhs.size_) { std::cout << "Widget::copy ctor" << std::endl; }
	~Widget() { std::cout << "Widget::dtor" << std::endl; }
	Widget& operator=(const Widget&rhs) { std::cout << "Widget::operator=()" << std::endl; size_ = rhs.size_; }
	void do_something() { std::cout << "size_+=1" << std::endl; size_ += 1; }
	int size() const { return size_; }
private:
	int size_;
};