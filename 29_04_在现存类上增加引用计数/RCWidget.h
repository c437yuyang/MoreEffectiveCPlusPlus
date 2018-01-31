#pragma once

//现在实现一个Widget类的引用计数版本

#include "Widget.h"
#include "RCIPtr.h"
class RCWidget
{
public:
	RCWidget(int size) :value_(new Widget(size)) {}
	void do_something() { value_->do_something(); }
	int size() { return value_->size(); }
private:
	RCIPtr<Widget> value_;
};