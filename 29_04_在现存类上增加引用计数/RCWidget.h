#pragma once

//����ʵ��һ��Widget������ü����汾

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