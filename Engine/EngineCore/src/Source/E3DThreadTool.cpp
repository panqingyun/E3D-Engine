#include "E3DThreadTool.h"
#include "..\..\include\EngineAPI.h"

E3DEngine::ThreadTool::ThreadTool()
{
	mOpFunc = nullptr;
	mRenderThreadInvoke = nullptr;
	mPhysicThreadInvoke = nullptr;
	mLogicThreadInvoke = nullptr;
}

void E3DEngine::ThreadTool::AddInvoke(int cur_thread_id, int dist_thread_id, ThreadInvokeFun func, void * param1 /*= nullptr*/, void *param2 /*= nullptr*/)
{
	if (dist_thread_id == LOGIC_THREAD_ID)
	{
		mLogicThreadInvoke = new ThreadInfo(cur_thread_id, func, param1, param2);
	}
	else if (dist_thread_id == RENDER_THREAD_ID)
	{
		mRenderThreadInvoke = new ThreadInfo(cur_thread_id, func, param1, param2);
	}
	else if (dist_thread_id == PHYSIC_THREAD_ID)
	{
		mPhysicThreadInvoke = new ThreadInfo(cur_thread_id, func, param1, param2);
	}
	if (mOpFunc != nullptr)
	{
		mOpFunc(cur_thread_id, SUSPEND_THREAD);
	}
}

void E3DEngine::ThreadTool::RunInvokeFun(int thread_id)
{
	ThreadInfo *pInfo = nullptr;
	switch (thread_id)
	{
	case RENDER_THREAD_ID:
		pInfo = mRenderThreadInvoke;
		mRenderThreadInvoke = nullptr;
		break;
	case LOGIC_THREAD_ID:
		pInfo = mLogicThreadInvoke;
		mLogicThreadInvoke = nullptr;
		break;
	case PHYSIC_THREAD_ID:
		pInfo = mPhysicThreadInvoke;
		mPhysicThreadInvoke = nullptr;
		break;
	default:
		break;
	}

	if (pInfo != nullptr)
	{
		if (pInfo->Func != nullptr)
		{
			pInfo->Func(pInfo->Param1, pInfo->Param2);
		}
		if (mOpFunc != nullptr)
		{
			mOpFunc(pInfo->ID, RESUME_THREAD);
		}
		SAFE_DELETE(pInfo);
	}
}

void E3DEngine::ThreadTool::RegisterThreadFunc(OpThreadFun func)
{
	mOpFunc = func;
}

void E3DEngine::ThreadTool::SetThreadState(int thread_id, int state)
{
	if (mOpFunc != nullptr)
	{
		mOpFunc(thread_id, state);
	}
}

