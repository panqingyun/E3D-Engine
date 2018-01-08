//
//  FBXMeshFactory.cpp
//
//  Created by 潘庆云 on 2017/3/22.
//

#include "E3DMeshFactory.hpp"
#include "E3DMesh.h"
#include "E3DMeshBuffer.hpp"
#include "../Source/EngineDelegate.h"

namespace E3DEngine
{
	MeshRender* MeshFactory::GetMesh(const char * path,const char * meshName, bool &bCreateSuccess)
	{
		MeshRender * mesh = nullptr;
		if (m_mapMeshs.find(meshName) == m_mapMeshs.end())
		{
			MeshBuffer * buffer = new MeshBuffer(path, meshName, bCreateSuccess);
			mesh = new MeshRender(buffer);
			m_mapMeshs[meshName] = buffer;
		}
		else
		{
			bCreateSuccess = true;
			mesh = new MeshRender(m_mapMeshs[meshName]);
		}
		
		mesh->Name = meshName;
		if (!bCreateSuccess)
		{
			//EngineDelegate::GetInstance().GetSystem<RenderSystem>()->RemoveFromRenderQueue(mesh);
		}
		return mesh;
	}
	
	MeshFactory::MeshFactory()
	{

	}

	E3DEngine::MeshFactory& MeshFactory::GetInstance()
	{
		static MeshFactory _ins;
		return _ins;
	}

	MeshFactory::~MeshFactory()
	{
		m_mapMeshs.clear();
	}

	void MeshFactory::Initilize()
	{

	}

	void MeshFactory::Destory()
	{
		for(std::map<std::string, MeshBuffer*>::iterator it = m_mapMeshs.begin(); it != m_mapMeshs.end(); ++ it)
		{
			it->second->Destory();
			SAFE_DELETE(it->second);
		}
		m_mapMeshs.clear();
	}
}
