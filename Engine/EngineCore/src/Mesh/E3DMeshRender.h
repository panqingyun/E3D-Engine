
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-5-24 PanQingyun. All rights reserved. *************************//

#ifndef _SKINNED_MESH_H_
#define	_SKINNED_MESH_H_

#include "E3DBone.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Component/E3DComponent.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "../Source/ClassFactory.h"

using namespace std;

class aiScene;
namespace E3DEngine
{
	class E3D_EXPORT_DLL MeshRender : public BatchRenderer
	{
		DECLARE_CLASS(MeshRender)
	public:
		~MeshRender();
		//virtual void SetAiScene(const aiScene* scene);
		virtual void SetBoneVector(vector<mat4f*> vecBones);
		//virtual const aiScene *GetAiScene() const;
		virtual vector<mat4f*> &GetBoneMatrixs();
		virtual Camera *GetCamera() override;
		virtual RenderObject *Get() override;
	private:
		const aiScene*				pScene;
		vector<mat4f*>				VecBoneMatrix;
	protected:
		BatchRenderer				*pRender;
		
	};

}
#endif	/* SKINNED_MESH_H */

