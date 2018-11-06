#pragma once
#include "Interface.h"

namespace E3DEngine
{
	using ThreadInvokeFun = void(*)(void*, void*);

	using OpThreadFun = void(*)(int id, int type);

	struct ThreadInfo
	{
		int ID;
		ThreadInvokeFun Func;
		void *Param1;
		void *Param2;
		ThreadInfo(int id, ThreadInvokeFun func, void* p1, void *p2)
			:ID(id), Func(func), Param1(p1), Param2(p2)
		{

		}
	};

	const int LOGIC_THREAD_ID = 0;
	const int PHYSIC_THREAD_ID = 1;
	const int RENDER_THREAD_ID = 2;
	const int SUSPEND_THREAD = 0;
	const int RESUME_THREAD = 1;
	const int LOCK_THREAD = 2;
	const int LOCK_END = 3;

	class ThreadTool : IObject
	{
		ThreadTool();
	public:
		static ThreadTool &GetInstance()
		{
			static ThreadTool _ins;
			return _ins;
		}
	public:
		void AddInvoke(int cur_thread_id, int dist_thread_id, ThreadInvokeFun func, void *  param1 = nullptr, void *param2 = nullptr);
		void RunInvokeFun(int thread_id);
		void RegisterThreadFunc(OpThreadFun func);
		void SetThreadState(int thread_id, int state);

	private:
		ThreadInfo *mRenderThreadInvoke;
		ThreadInfo *mLogicThreadInvoke;
		ThreadInfo *mPhysicThreadInvoke;
		OpThreadFun mOpFunc;
	};
}
