/*
 * Create 2017 Pan Qingyun.
 */

#ifndef _SKINNED_MESH_H_
#define	_SKINNED_MESH_H_

#include "E3DBone.hpp"
#include "../Object/E3DRenderObject.hpp"
#include "../Object/E3DComponent.hpp"

using namespace std;

namespace E3DEngine
{
	class MeshBuffer;
	class MeshRender : public RenderObject
	{
	public:
		MeshRender(MeshBuffer * buffer);
		~MeshRender();
		
	private:
		virtual void prepareRender(float deltaTime);		
		virtual void update(float deltaTime) { }		
		void		 initBoneMatrix();
		
	public:
		vector<mat4f*>				VecBoneMatrix;
		const aiScene*				pScene;
		map<string,Bone*>			BoneMapping;
		
	private:
		MeshBuffer * m_pMeshBuffer;
		
	};

}
#endif	/* SKINNED_MESH_H */

