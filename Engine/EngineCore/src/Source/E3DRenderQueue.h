#ifndef __RENDER_QUEUE_H__
#define __RENDER_QUEUE_H__

#include "Interface.h"
#include "src/Object/E3DRenderObject.hpp"

namespace E3DEngine
{
	class RenderQueue extends Ref
	{
	public:
		RenderQueue();
		RenderQueue * CreateSubQueue(uint id);
	public:
		void Add(GameObject * go);
		bool Remove(GameObject * go);
		void AddSubQueue(unsigned int id, RenderQueue * sub);
		void Clear();
		void SetCamera(Camera * pCamera);
		bool ChangeRenderQueue(QWORD id, eRenderIndex index);

		void Render(float deltaTime);

		unsigned int GetID();
		bool FindInRenderQueue(GameObject *go);

	private:
		void changeNormalQueue(GameObject * go);
		void changeTransparentQueue(GameObject * go);

	private:
		std::vector<GameObject*> _renderQueue;
		std::map<unsigned int, RenderQueue*> mapRenderQueue; // 场景子渲染队列 其他RenderTarget 需要FBO
		unsigned int queueId;
		Camera * m_pCamera;
	};
}

#endif
