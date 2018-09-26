//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-28 PanQingyun. All rights reserved. *************************//

#ifndef SkinAnimation_hpp
#define SkinAnimation_hpp

#include "E3DAnimation.hpp"
#include "../Mesh/E3DMeshRender.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL SkinAnimation : public Animation
	{
	public:
		virtual void Start();
		virtual void Destory();
	private:
		MeshRender * m_pMesh;
	};
}

#endif /* SkinAnimation_hpp */
