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
		void Add(RenderObject * rb);
		bool Remove(RenderObject * rb);
		void AddSubQueue(unsigned int id, RenderQueue * sub);
		void Clear();
		void SetCamera(Camera * pCamera);
		bool ChangeRenderQueue(UINT id, eRenderIndex index);

		void Render(float deltaTime);

		unsigned int GetID();
		bool FindInRenderQueue(RenderObject *rb);

	private:
		void changeNormalQueue(RenderObject * rb);
		void changeTransparentQueue(RenderObject * rb);

	private:
		std::vector<RenderObject*> _renderQueue;
		std::map<unsigned int, RenderQueue*> mapRenderQueue; // 场景子渲染队列 其他RenderTarget 需要FBO
		unsigned int queueId;
		Camera * m_pCamera;
	};
}

#endif
