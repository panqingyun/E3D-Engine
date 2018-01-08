#include "E3DAutoreleasePool.h"
#include "Interface.h"

namespace E3DEngine
{
	AutoreleasePool::AutoreleasePool()
	{
	}

	AutoreleasePool::~AutoreleasePool()	= default;

	void AutoreleasePool::Update()
	{
		std::vector<Ref*> temp;
		std::copy(willDeleteObjectMap.begin(), willDeleteObjectMap.end(), std::back_inserter(temp));
		for (int i = 0; i < temp.size(); i++)
		{
			SAFE_DELETE(willDeleteObjectMap[0]);
			willDeleteObjectMap.erase(willDeleteObjectMap.begin());
		}
	}

	void AutoreleasePool::AddDeletePointer(Ref * ptr)
	{
		willDeleteObjectMap.emplace_back(ptr);
	}
}
