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
		timer->isStop = false;
		timer->tickTime = 0;
		timer->timeInterval = timeInSec;
		timer->timerCallBack += timerTickCallBack;
		timer->param = param;
		timer->ID = getInstance().m_nTimerID;
		getInstance().mTimerMap[getInstance().m_nTimerID] = timer;
		std::vector<std::list<stTimer*>> &timeList = getInstance().mTimerList;
		int n = timeInSec / getInstance().deltaTime;
		timeList[n].emplace_back(timer);
		return getInstance().m_nTimerID;
	}

	void Timer::StartTimer(unsigned int timerID)
	{
		if (getInstance().mTimerMap.find(timerID) == getInstance().mTimerMap.end())
		{
			return;
		}
		getInstance().mTimerMap[timerID]->isStop = false;
	}

	void Timer::Update(float deltaTime)
	{
		Timer &t = getInstance();
		t.deltaTime = deltaTime;
		if (t.mTimerList.size() == 0)
		{
			return;
		}
		int &index = t.mIndex;
		if (index >= t.mTimerList.size())
		{
			index = 0;
		}
		std::list<stTimer*> &timerList = t.mTimerList[index];
		std::list<stTimer*> temp;

		std::copy(t.mTimerList[index].begin(), t.mTimerList[index].end(), std::inserter(temp, temp.begin()));

		for (auto itimer : temp)
		{
			itimer->tickTime += deltaTime;
			if (itimer->tickTime >= itimer->timeInterval)
			{
				if (!itimer->timerCallBack.empty() && !itimer->isStop)
				{
					itimer->timerCallBack(nullptr, itimer->param);
					if (itimer->isRepeat)
					{
						// 循环执行的加入下一个周期链表中
						int n = itimer->timeInterval / t.deltaTime + index;
						t.mTimerList[n].emplace_back(itimer);
						timerList.remove(itimer);
					}
				}
			}
		}

		// 舍弃这一时间片
		for (std::list<stTimer*>::iterator itimer = timerList.begin(); itimer != timerList.end(); ++itimer)
		{
			getInstance().mTimerMap.erase((*itimer)->ID);
			SAFE_DELETE((*itimer));
		}

		timerList.clear();
		index++;
		//t.mTimerList.erase(t.mTimerList.begin());
	}

	void Timer::Init()
	{
		getInstance().m_nTimerID = 0;
		getInstance().deltaTime = 0;
		getInstance().mIndex = 0;
		getInstance().mTimerList.resize(1440);
	}

	void Timer::PauseTimer(unsigned int timerID)
	{
		std::map<unsigned int, stTimer*>::iterator it = getInstance().mTimerMap.find(timerID);
		if (it == getInstance().mTimerMap.end())
		{
			return;
		}
		it->second->isStop = true;
	}

	void Timer::StopTimer(unsigned int timerID)
	{
		std::map<unsigned int, stTimer*>::iterator it = getInstance().mTimerMap.find(timerID);
		if (it == getInstance().mTimerMap.end())
		{
			return;
		}
		if (it->second == nullptr)
		{
			return;
		}


		getInstance().mTimerMap.erase(it);
	}

	void Timer::StopAllTimer()
	{
		for (std::map<unsigned int, stTimer *>::iterator it = getInstance().mTimerMap.begin(); it != getInstance().mTimerMap.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		getInstance().mTimerMap.clear();
		getInstance().m_nTimerID = 0;
	}
}
