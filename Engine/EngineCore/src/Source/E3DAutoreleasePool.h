#ifndef __E3D_REF_MANAGER_H__
#define __E3D_REF_MANAGER_H__
#include <vector>

namespace E3DEngine
{
	class Ref;
	class __declspec(dllexport) AutoreleasePool
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