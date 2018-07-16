//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-27 PanQingyun. All rights reserved. *************************//

#ifndef AnimationClip_hpp
#define AnimationClip_hpp

#include "../Object/E3DComponent.hpp"
#include "../Mesh/E3DBone.hpp"

namespace E3DEngine
{
	class AnimationClip : public Component
	{
	public:
		std::string		mName;
		double			TimeLong;
		int				Index;
	private:
		aiAnimation		* m_aiAnimation;
	};
}

#endif /* AnimationClip_hpp */
