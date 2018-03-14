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
		UINT ObjectID;
		uint VertextStartIndex;
		uint VertextNumber;
		uint IndexStartIndex;
		uint IndexNumber;
	};

	enum RENDER_TYPE
	{
		NORMAL,
		MESH,
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
		virtual DWORD RecordCurrentVextexStartIndex(UINT objId);

		virtual DWORD RecordCurrentIndexStartIndex(UINT objId);
		virtual void VertexCountAdd(UINT objId, uint vertexCount);
		virtual void IndexCountAdd(UINT objId, uint indexCount);
		virtual void RemoveInRenderer(UINT objId);
		virtual RendererBuffer* GetRendererBuffer(UINT objID);

		virtual void TransformChange() override;
	protected:
		virtual void CreateBehaviour();
		virtual void setBehaviourDefaultValue();

	protected:
		DWORD m_vertexCount;
		DWORD m_indexCount;
		std::map<UINT, RendererBuffer> m_objRendererBuffers;
		bool	bLock;
	};

	class RendererManager : public IObject
	{
	public:
		virtual Renderer * CreateVertexRender(int materialID);
		virtual Renderer * GetRenderer(int materialID, RENDER_TYPE type = NORMAL);
		virtual Renderer * GenRender();
		virtual void AddRenderer(int materialID, Renderer * rd);
		virtual void Destory();
	protected:
		std::map<int, Renderer*> m_mapVertexBuffers;
	};
}

#endif /* E3DVertexBufferManager_hpp */
