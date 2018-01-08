//
//  E3DVertexBufferManager.hpp
//	按照材质ID 索引顶点缓存，同一材质ID的物体顶点都输出到同一个顶点缓存中，然后统一绘制
//  Created by 潘庆云 on 2017/7/19.
//

#ifndef E3DVertexBufferManager_hpp
#define E3DVertexBufferManager_hpp

#include "src/Source/Interface.h"
#include "src/Object/E3DRenderObject.hpp"

namespace E3DEngine
{
	struct RendererBuffer
	{
		QWORD ObjectID;
		uint VertextStartIndex;
		uint VertextNumber;
		uint IndexStartIndex;
		uint IndexNumber;
	};

	class Renderer : public RenderObject
	{
	public:
		Renderer();
		virtual ~Renderer() override;
	public:
		virtual void prepareRender(float deltaTime) override;
		virtual void FillVertex(Vertex vb);
		virtual void FillIndex(uint ib);
		virtual void FillEnd();
		virtual DWORD RecordCurrentVextexStartIndex(QWORD objId);

		virtual DWORD RecordCurrentIndexStartIndex(QWORD objId);
		virtual void VertexCountAdd(QWORD objId, uint vertexCount);
		virtual void IndexCountAdd(QWORD objId, uint indexCount);
		virtual void SetBlendType(DWORD blendType);
		virtual void RemoveInRenderer(QWORD objId);
		virtual RendererBuffer* GetRendererBuffer(QWORD objID);

		virtual void TransformChange() override;
	protected:
		virtual void CreateBehaviour();
		virtual void setBehaviourDefaultValue();

	protected:
		DWORD glBlendType;
		DWORD m_vertexCount;
		DWORD m_indexCount;
		std::map<QWORD, RendererBuffer> m_objRendererBuffers;
		bool	bLock;
	};

	class RendererManager : public IObject
	{
	public:
		virtual Renderer * CreateVertexRender(int materialID);
		virtual Renderer * GetRenderer(int materialID);
		virtual Renderer * GenRender();
		virtual void Destory();
	protected:
		std::map<int, Renderer*> m_mapVertexBuffers;
	};
}

#endif /* E3DVertexBufferManager_hpp */
