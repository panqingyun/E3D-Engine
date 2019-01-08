//
//  E3DRenderer.hpp
//	多个物体可以共用, 目的：动态渲染合批
//  Created by 潘庆云 on 2017/7/17.
//

#ifndef __E3D_RENDERER_HPP__
#define __E3D_RENDERER_HPP__

#include "../../Object/E3DRenderObject.hpp"
#include "../../Source/ClassFactory.h"

namespace E3DEngine
{
#if (defined __E3D_EDITOR__) || (defined WIN32)
	#define MAX_VERTEX_NUMBER 4294967295
#else
	#define MAX_VERTEX_NUMBER 65535
#endif

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

	class E3D_EXPORT_DLL Renderer : public Component
	{
		DECLARE_CLASS(Renderer)
	public:
		DECLARE_PROPERTY(Renderer, std::string, MaterialPath)
		DECLARE_PROPERTY(Renderer, int, MaterialID)
		DECLARE_PROPERTY(Renderer, int, RendererType)
		virtual void registProperty()
		{
			SAVE_PROPERTY(MaterialPath, FT_STRING);
			SAVE_PROPERTY(MaterialID, FT_INT | FT_READONLY);
			SAVE_PROPERTY(RendererType, FT_INT | FT_READONLY);
		}
	public:
		virtual void OnCreateComplete() override;
		virtual Object *Get();
	protected:
		RenderObject *pRenderer;
	};

	class E3D_EXPORT_DLL BatchRenderer : public RenderObject
	{
	public:
		BatchRenderer();
		virtual ~BatchRenderer() override;
	public:
		virtual void FillBegin(UINT objId);
		virtual void FillVertex(std::vector<Vertex>& vb);
		virtual void FillVertex(Vertex vb);
		virtual void FillBatchVertex(BatchVertex bv);
		virtual void FillIndex(uint ib);
		virtual void FillEnd(UINT objId, uint vertexCount, uint indexCount);
		virtual void RemoveInRenderer(UINT objId);
		virtual RendererBuffer* GetRendererBuffer(UINT objID);

		virtual void TransformChange() override;
		DWORD GetVertextCount() { return m_vertexCount; }
	public:
		std::vector<BatchVertex> mBatchVertex;

	protected:
		virtual void CreateBehaviour();
		virtual void setBehaviourDefaultValue();
		virtual DWORD RecordCurrentVextexStartIndex(UINT objId);

		virtual DWORD RecordCurrentIndexStartIndex(UINT objId);
		virtual void VertexCountAdd(UINT objId, uint vertexCount);
		virtual void IndexCountAdd(UINT objId, uint indexCount);

	protected:
		DWORD m_vertexCount;
		DWORD m_indexCount;
		std::map<UINT, RendererBuffer> m_objRendererBuffers;
		bool	bNeedUpdateVertex;
	};

}

#endif /* E3DVertexBuffer_hpp */
