//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-27 PanQingyun. All rights reserved. *************************//

#ifndef AnimationClip_hpp
#define AnimationClip_hpp

#include "../Object/E3DComponent.hpp"
#include "../Mesh/E3DBone.hpp"

namespace E3DEngine
{
	class EX_PORT AnimationClip : public Component
	{
	public:
		std::string		mName;
		double			TimeLong;
		int				Index;
	private:

#ifndef __EDITOR__
		aiAnimation		* m_aiAnimation;
#endif
	};
}

#endif /* AnimationClip_hpp */
