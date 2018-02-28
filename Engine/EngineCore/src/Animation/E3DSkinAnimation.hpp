//
//  SkinAnimation.hpp
//
//  Created by 潘庆云 on 2017/3/28.
//

#ifndef SkinAnimation_hpp
#define SkinAnimation_hpp

#include "E3DAnimation.hpp"
#include "../Mesh/E3DMeshRender.h"

namespace E3DEngine
{
	class SkinAnimation : public Animation
	{
	public:
		virtual void Start();
		virtual void Destory();
	private:
		MeshRender * m_pMesh;
	};
}

#endif /* SkinAnimation_hpp */
