
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-5-24 PanQingyun. All rights reserved. *************************//

#ifndef _SKINNED_MESH_H_
#define	_SKINNED_MESH_H_

#include "E3DBone.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DComponent.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"

using namespace std;

namespace E3DEngine
{
	class EX_PORT MeshRender : public Renderer
	{
	public:
		~MeshRender();
		virtual void SetAiScene(const aiScene* scene);
		virtual void SetBoneVector(vector<mat4f*> vecBones);
		virtual const aiScene *GetAiScene() const;
		virtual vector<mat4f*> &GetBoneMatrixs();

	private:
		const aiScene*				pScene;
		vector<mat4f*>				VecBoneMatrix;
		
	};

}
#endif	/* SKINNED_MESH_H */

