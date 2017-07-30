#pragma once
#include <list>
using std::list;
class HeapTrack
{
public:
	class MissingAddress {}; //�쳣�࣬�����׳��쳣
	virtual ~HeapTrack() = 0; //ʹ֮��Ϊ�����
	static void *operator new(size_t size);
	static void operator delete(void *ptr);
	bool isOnHeap() const;
private:
	typedef const void * RawAddress;
	static list<RawAddress> addresses;
};
list<const void *> HeapTrack::addresses; //����static��Ա

HeapTrack::~HeapTrack() {}//������õ�������ʵ�֣���Ϊ���ಢ��Ҫ��ȥʵ��(����ֻ��Ϊ��ʹ֮��Ϊ������)
							//���������һ���յ�ʵ��������Ͳ���ȥʵ����

void *HeapTrack::operator new(size_t size)
{
	void * memPtr = ::operator new(size);
	addresses.push_front(memPtr); //����ǰ�Σ�����findЧ�ʸ���
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