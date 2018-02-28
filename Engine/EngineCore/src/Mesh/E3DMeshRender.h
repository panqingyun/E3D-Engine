/*
 * Create 2017 Pan Qingyun.
 */

#ifndef _SKINNED_MESH_H_
#define	_SKINNED_MESH_H_

#include "E3DBone.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DComponent.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"

using namespace std;

namespace E3DEngine
{
	class MeshRender : public Renderer
	{
	public:
		~MeshRender();
		
	public:
		const aiScene*				pScene;
		map<string,Bone*>			BoneMapping;
		
	};

}
#endif	/* SKINNED_MESH_H */

