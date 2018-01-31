#pragma once

class RCObject
{
public:
	RCObject() : ref_count_(0), shareable_(true) {}
	RCObject(const RCObject&rhs) : ref_count_(0), shareable_(true) {} //���Կ������еĵط�������Ϊ0������ֵ�����ã��ⶼ����Ҫ�������Լ�����������
	RCObject& operator= (const RCObject&rhs) { return *this; }
	virtual ~RCObject() = 0 {} //������������������ֻ����������
	void addReference() { ++ref_count_; }
	void removeReference() { if (--ref_count_ == 0) delete this; }
	void markUnshareable() { shareable_ = false; }
	bool isShareable() const { return shareable_; }
	bool isShared() const { return ref_count_ > 1; }
private:
	int ref_count_;
	bool shareable_;
};
