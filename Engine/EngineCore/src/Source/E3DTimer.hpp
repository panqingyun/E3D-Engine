//
//  E3DTimer.hpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#ifndef E3DTimer_hpp
#define E3DTimer_hpp

#include <stdio.h>
#include "Interface.h"
#include "E3DDelegate.h"

namespace E3DEngine
{
	class Time
	{
	public:
		static float deltaTime;
	};

	struct stTimer
	{
		stTimer()
		{
			param = nullptr;
		}
		~stTimer()
		{
			timerCallBack.Cleanup();
		}
		event EventDelegates timerCallBack;
		bool isRepeat;
		float timeInterval;
		float tickTime;
		bool isPause;
		IObject * handleClass;
		EventArgs * param;
	};
	
	class Timer : public IObject
	{
	private:
		static Timer & getInstance()
		{
			static Timer timer;
			return timer;
		}
	public:
		static unsigned int	AddTimer(float timeInSec, EventHandleFunction * timerTickCallBack,EventArgs * param, bool isRepeat = false);
		static void StartTimer(unsigned int timerID);
		static void StopAllTimer();
		static void PauseTimer(unsigned int timerID);
		static void StopTimer(unsigned int timerID);
		static void Update(float deltaTime);
		static void Init();
		static void Destory()
		{
			StopAllTimer();
		}
	private:
		std::map<unsigned int, stTimer*> timerMap;
		unsigned int m_nTimerID;
	};
}

#endif /* E3DTimer_hpp */
