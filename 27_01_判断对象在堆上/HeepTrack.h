#pragma once
#include <list>
using std::list;
class HeapTrack
{
public:
	class MissingAddress {}; //异常类，用于抛出异常
	virtual ~HeapTrack() = 0; //使之成为虚基类
	static void *operator new(size_t size);
	static void operator delete(void *ptr);
	bool isOnHeap() const;
private:
	typedef const void * RawAddress;
	static list<RawAddress> addresses;
};
list<const void *> HeapTrack::addresses; //定义static成员

HeapTrack::~HeapTrack() {}//子类会用到，必须实现，因为子类并不要求去实现(这里只是为了使之成为抽象类)
							//所以这里给一个空的实现体子类就不用去实现了

void *HeapTrack::operator new(size_t size)
{
	void * memPtr = ::operator new(size);
	addresses.push_front(memPtr); //推入前段，后面find效率更高
	return memPtr;
}

void HeapTrack::operator delete(void * ptr)
{
	auto it = find(addresses.begin(), addresses.end(), ptr);
	if (it == addresses.end())
	{
		throw MissingAddress();
	}
	else
	{
		addresses.erase(it);
		::operator delete(ptr);
	}
}

bool HeapTrack::isOnHeap() const
{
	RawAddress rawAddr = dynamic_cast<RawAddress>(this);
	auto it = find(addresses.begin(), addresses.end(), rawAddr);
	return it != addresses.end();
}