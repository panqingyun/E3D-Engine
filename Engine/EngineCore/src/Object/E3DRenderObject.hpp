//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-17  PanQingyun. All rights reserved. *************************//

#ifndef Object_hpp
#define Object_hpp

#include "../Component/E3DComponent.hpp"
#include "../RenderSystem/Material/E3DMaterial.hpp"
#include "../Source/E3DVertex.h"
#include "../Source/vmath.h"
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	typedef enum
	{
		eRI_None,
		eRI_LowMost,
		eRI_Normal,
		eRI_Transparent,
		eRI_TopMost,
	} eRenderIndex;

	class MinMaxAABB : public Object
	{
	private:
		vec3f    m_Min;
		vec3f    m_Max;

	public:
		MinMaxAABB() 
		{
			Init(); 
		}
		MinMaxAABB(const vec3f& _min, const vec3f& _max) : m_Min(_min), m_Max(_max) {}

		void Init();

		vec3f CalculateCenter() const { return (m_Max + m_Min) * 0.5f; }
		vec3f CalculateExtent() const { return (m_Max - m_Min) * 0.5f; }
		vec3f CalculateSize() const { return (m_Max - m_Min); }

		void Expand(float inValue);
		void Expand(const vec3f& inOffset);

		void Encapsulate(const vec3f& inPoint);
		void Encapsulate(const MinMaxAABB& other);

		bool IsInside(const vec3f& inPoint) const;
		void CalculateVertices(vec3f outVertices[8]) const;
		bool IsValid() const;

		const vec3f& GetMin() const { return m_Min; }
		const vec3f& GetMax() const { return m_Max; }
	};

	inline void MinMaxAABB::Expand(float inValue)
	{
		vec3f offset = vec3f(inValue, inValue, inValue);
		m_Min -= offset;
		m_Max += offset;
	}

	inline void MinMaxAABB::Expand(const vec3f& inOffset)
	{
		m_Min -= inOffset;
		m_Max += inOffset;
	}

	inline void MinMaxAABB::Encapsulate(const MinMaxAABB& other)
	{
		m_Min = min(m_Min, other.m_Min);
		m_Max = max(m_Max, other.m_Max);
	}

	inline void MinMaxAABB::Encapsulate(const vec3f& inPoint)
	{
		m_Min = min(m_Min, inPoint);
		m_Max = max(m_Max, inPoint);
	}


    class CTransform;
    class E3D_EXPORT_DLL RenderObject : public Object
    {
    public:
        RenderObject();
		virtual ~RenderObject() override;
	public:
		int		nMaterialID;
		
	public:
		virtual void PrepareUpdate()
		{
		}
		virtual void AfterUpdate()
		{
		}
		virtual void Render();
		virtual void Destory(RenderObject *obj);
		virtual void SetMaterialID(int ID);
		virtual void SetMaterial(Material *material);
		virtual void TransformChange() { }
		virtual void SetCamera(Camera * camera);
		virtual void SetDrawModule(DWORD module);
		virtual void ClearVertexIndexBuffer() { }
		virtual RenderObject *Get() { return this; }
	public:
		virtual UINT GetDrawModule();
		virtual CTransform * GetTransform();
		virtual void SetTransform(CTransform *_transform);
		virtual void CreateNewTransform();
		virtual void SetRenderIndex(DWORD index);
		virtual Material* GetMaterial();
		virtual void SetNeedSortVertex(bool bNeed);
		virtual void SetLayerMask(DWORD layer);
		virtual DWORD GetLayerMask();
		virtual Camera *GetCamera();
		virtual void ChangeColor(Color4 color) { }
		void SetActive(bool isActive);
		MinMaxAABB GetBounds()
		{
			return m_AABB;
		}
#ifdef __E3D_EDITOR__
		virtual void Selected(bool select);
#endif
    protected:
        long	m_nColor;
        bool	m_bIsBillboard;
		DWORD   m_nDrawModule;
		bool	m_bIsBufferData;
		CTransform * transform;
		MinMaxAABB   m_AABB;
		// 材质
		Material	* pMaterial;
		bool		m_bNeedSortVertex;
		DWORD		m_layer;
		bool		m_IsActive;
		bool		m_IsSelected;
    public:
		// 索引数目
		DWORD							m_nIndexSize;
		// 顶点数组
		std::vector<Vertex>				Vertices;
		// 索引数组
		std::vector<unsigned int>		Indices;
		// 渲染层级
		eRenderIndex					RenderIndex;
		// 静态绘制表示这个BatchRenderer 是给合并批次的object使用
		bool							IsStaticDraw;
		Camera *						pCamera;
    };

}
    #endif /* Object_hpp */
