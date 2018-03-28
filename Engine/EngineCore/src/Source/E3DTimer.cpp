//
//  E3DTimer.cpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#include "E3DTimer.hpp"

namespace E3DEngine
{
	float Time::deltaTime = 0.0f;

	unsigned int Timer::AddTimer(float timeInSec, EventHandleFunction * timerTickCallBack, EventArgs * param, bool isRepeat)
	{
		getInstance().m_nTimerID++;
		stTimer * timer = new stTimer;
		timer->isRepeat = isRepeat;
		timer->isPause = true;
		timer->tickTime = 0;
		timer->timeInterval = timeInSec;
		timer->timerCallBack += timerTickCallBack;
		timer->param = param;
		getInstance().timerMap[getInstance().m_nTimerID] = timer;
		return getInstance().m_nTimerID;
	}

	void Timer::StartTimer(unsigned int timerID)
	{
		if (getInstance().timerMap.find(timerID) == getInstance().timerMap.end())
		{
			return;
		}
		getInstance().timerMap[timerID]->isPause = false;
	}

	void Timer::Update(float deltaTime)
	{
		Timer &t = getInstance();
		std::map<unsigned int, stTimer*> temp;
		std::copy(t.timerMap.begin(), t.timerMap.end(), std::inserter(temp, temp.begin()));
		for (auto & it : temp)
		{
			if (it.second->isPause)
			{
				continue;
			}
			it.second->tickTime += deltaTime;
			if (it.second->tickTime >= it.second->timeInterval)
			{
				if (!it.second->timerCallBack.empty())
				{
					it.second->timerCallBack(nullptr, it.second->param);
				}
				if (it.second->isRepeat == false)
				{
					StopTimer(it.first);
				}
				it.second->tickTime = 0;
			}
		}
	}

	void Timer::Init()
	{
		getInstance().m_nTimerID = 0;
	}

	void Timer::PauseTimer(unsigned int timerID)
	{
		std::map<unsigned int, stTimer*>::iterator it = getInstance().timerMap.find(timerID);
		if (it == getInstance().timerMap.end())
		{
			return;
		}
		it->second->isPause = true;
	}

	void Timer::StopTimer(unsigned int timerID)
	{
		std::map<unsigned int, stTimer*>::iterator it = getInstance().timerMap.find(timerID);
		if (it == getInstance().timerMap.end())
		{
			return;
		}
		if (it->second == nullptr)
		{
			return;
		}
		SAFE_DELETE(it->second);
		getInstance().timerMap.erase(it);
	}

	void Timer::StopAllTimer()
	{
		for (std::map<unsigned int, stTimer *>::iterator it = getInstance().timerMap.begin(); it != getInstance().timerMap.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		getInstance().timerMap.clear();
		getInstance().m_nTimerID = 0;
	}
}
