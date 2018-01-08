//
//  FBXMeshFactory.hpp
//
//  Created by 潘庆云 on 2017/3/22.
//

#ifndef FBXMeshFactory_hpp
#define FBXMeshFactory_hpp

#include "../Object/E3DGameObject.h"

namespace E3DEngine
{
	class MeshRender;
	class MeshBuffer;
	class MeshFactory implement IFactory
	{
	public:
		static MeshFactory& GetInstance();
		virtual ~MeshFactory() override;
		virtual void Initilize() override;
		virtual void Destory() override;
		
		MeshRender * GetMesh(const char * path, const char * meshName, bool& bCreateSuccess);
	private:
		MeshFactory();
	private:
		std::map<std::string, MeshBuffer*> m_mapMeshs;
	};
}

#endif /* FBXMeshFactory_hpp */
