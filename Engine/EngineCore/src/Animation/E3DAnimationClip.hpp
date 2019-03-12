//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-27 PanQingyun. All rights reserved. *************************//

#ifndef AnimationClip_hpp
#define AnimationClip_hpp

#include "../Mesh/E3DBone.hpp"

#ifndef __IGNORED_INCLUDE__
#include <assimp/mesh.h> 
#include <assimp/scene.h>
#include <assimp/texture.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#endif

namespace E3DEngine
{
	class E3D_EXPORT_DLL AnimationClip : public Component
	{
	public:
		std::string		mName;
		double			TimeLong;
		int				Index;
	private:

#ifndef __IGNORED_INCLUDE__
		aiAnimation		* m_aiAnimation;
#endif
	};
}

#endif /* AnimationClip_hpp */
