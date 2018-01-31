#pragma once

class RCObject
{
public:
	RCObject() : ref_count_(0), shareable_(true) {}
	RCObject(const RCObject&rhs) : ref_count_(0), shareable_(true) {} //可以看到所有的地方都是置为0，具体值的设置，这都是需要调用者自己来做的事情
	RCObject& operator= (const RCObject&rhs) { return *this; }
	virtual ~RCObject() = 0 {} //纯虚析构函数，表明只能用做基类
	void addReference() { ++ref_count_; }
	void removeReference() { if (--ref_count_ == 0) delete this; }
	void markUnshareable() { shareable_ = false; }
	bool isShareable() const { return shareable_; }
	bool isShared() const { return ref_count_ > 1; }
private:
	int ref_count_;
	bool shareable_;
};
