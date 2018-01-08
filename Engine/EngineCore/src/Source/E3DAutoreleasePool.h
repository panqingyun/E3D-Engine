#ifndef __REF_MANAGER_H__
#define __REF_MANAGER_H__

#include "../Utils/E3DUtil.hpp"

namespace E3DEngine
{
	class Ref;
	class AutoreleasePool
	{
	private:
		AutoreleasePool();
	public:
		~AutoreleasePool();
		static AutoreleasePool & GetInstance()
		{
			static AutoreleasePool _ins;
			return _ins;
		}

		void Update();
		void AddDeletePointer(Ref * ptr);
	private:
		std::vector<Ref*> willDeleteObjectMap;
	};

}

#endif