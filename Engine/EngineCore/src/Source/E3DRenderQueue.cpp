#include "E3DRenderQueue.h"
#include "EngineDelegate.h"

namespace E3DEngine
{

	RenderQueue::RenderQueue()
	{
		queueId = 0;
	}

	RenderQueue * RenderQueue::CreateSubQueue(uint id)
	{
		RenderQueue * queue = new RenderQueue();
		queue->queueId = id;
		mapRenderQueue[queue->queueId] = queue;
		return queue;
	}

	void RenderQueue::Add(GameObject * go)
	{
		if (go == nullptr)
		{
			return;
		}
		if (FindInRenderQueue(go))
		{
			return;
		}
		if (_renderQueue.empty())
		{
			_renderQueue.push_back(static_cast<GameObject*>(go));
			return;
		}
		for (int i = _renderQueue.size() - 1; i >= 0; i--)
		{
			if (_renderQueue[i]->RenderIndex >= eRI_Normal || i == 0)
			{
				_renderQueue.insert(_renderQueue.begin() + i + 1, go);
				return;
			}
		}
		_renderQueue.emplace_back(go);
	}

	bool RenderQueue::Remove(GameObject * go)
	{
		if (go == nullptr)
		{
			return false;
		}
		int renderIndex = -1;
		for (int i = 0; i < _renderQueue.size(); i++)
		{
			if (_renderQueue[i]->ID == go->ID)
			{
				renderIndex = i;
				break;
			}
		}

		if (renderIndex == -1)
		{
			bool bRemove = false;
			for (auto &rederQueue : mapRenderQueue )
			{
				if (rederQueue.second->Remove(go))
				{
					bRemove = true;
					break;
				}
			}
			return bRemove;
		}

		_renderQueue.erase(_renderQueue.begin() + renderIndex);
		return true;
	}

	void RenderQueue::AddSubQueue(unsigned int id, RenderQueue * sub)
	{
		if (mapRenderQueue.find(id) != mapRenderQueue.end())
		{
			return;
		}

		mapRenderQueue[id] = sub;
	}

	void RenderQueue::changeTransparentQueue(GameObject * go)
	{
		bool bInsert = false;
		for (int i = _renderQueue.size() - 1; i >= 0;)
		{
			go = static_cast<GameObject*>(_renderQueue[i]);
			if (go->RenderIndex != eRI_TopMost || i == 0)
			{
				_renderQueue.insert(_renderQueue.begin() + i + 1, go);
				bInsert = true;
				break;
			}
			else
			{
				i--;
			}
		}
		if (!bInsert)
		{
			_renderQueue.push_back(go);
		}
	}

	void RenderQueue::changeNormalQueue(GameObject * go)
	{
		bool bInsert = false;
		for (int i = _renderQueue.size() - 1; i >= 0;)
		{
			go = static_cast<GameObject*>(_renderQueue[i]);
			if (go->RenderIndex == eRI_Normal || go->RenderIndex == eRI_LowMost || i == 0)
			{
				_renderQueue.insert(_renderQueue.begin() + i + 1, go);
				bInsert = true;
				break;
			}
			else
			{
				i--;
			}
		}
		if (!bInsert)
		{
			_renderQueue.push_back(go);
		}
	}

	bool RenderQueue::FindInRenderQueue(GameObject *go)
	{
		bool bFind = false;
		for (auto & render : _renderQueue)
		{
			if (render->ID == go->ID)
			{
				bFind = true;
				break;
			}
			else if (render->GetRenderer() == go->GetRenderer())
			{
				bFind = true;
				break;
			}
		}
		return bFind;
	}

	bool RenderQueue::ChangeRenderQueue(QWORD id, eRenderIndex index)
	{
		int renderIndex = -1;
		bool retValue  = true;
		for (int i = 0; i < _renderQueue.size(); i++)
		{
			if (_renderQueue[i]->ID == id)
			{
				renderIndex = i;
				break;
			}
		}

		if (renderIndex == -1)
		{
			retValue = false;
			for (auto &re : mapRenderQueue)
			{
				if (re.second->ChangeRenderQueue(id, index))
				{
					retValue = true;
					break;
				}
			}
			return retValue;
		}
		GameObject * render = static_cast<GameObject*>(_renderQueue[renderIndex]);
		_renderQueue.erase(_renderQueue.begin() + renderIndex);
		if (render->RenderIndex == eRI_LowMost)
		{
			_renderQueue.insert(_renderQueue.begin(), render);
		}
		else if (render->RenderIndex == eRI_TopMost)
		{
			_renderQueue.push_back(render);
		}
		else if (render->RenderIndex == eRI_Transparent)
		{
			changeTransparentQueue(render);
		}
		else
		{
			changeNormalQueue(render);
		}
		return retValue;
	}

	void RenderQueue::Render(float deltaTime)
	{
		for (auto & render : _renderQueue)
		{
			if (render == nullptr)
			{
				Debug::Log(ell_Error, " Not render object in renderQueue ");
				continue;
			}
			if (!render->IsActive)
			{
				continue;
			}
			render->SetCamera(m_pCamera);
			render->Render(deltaTime);
		}
		for (auto &renderQueue : mapRenderQueue)
		{
			renderQueue.second->Render(deltaTime);
		}
	}

	unsigned int RenderQueue::GetID()
	{
		return queueId;
	}

	void RenderQueue::Clear()
	{
		_renderQueue.clear();
		for (auto & queue : mapRenderQueue)
		{
			queue.second->Clear();
		}
		mapRenderQueue.clear();
	}

	void RenderQueue::SetCamera(Camera * pCamera)
	{
		m_pCamera = pCamera;
	}

}
