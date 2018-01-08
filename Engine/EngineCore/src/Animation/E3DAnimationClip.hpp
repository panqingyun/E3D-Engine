//
//  AnimationClip.hpp
//  Created by 潘庆云 on 2017/3/27.
//

#ifndef AnimationClip_hpp
#define AnimationClip_hpp

#include "../Object/E3DComponent.hpp"
#include "../Mesh/E3DBone.hpp"

namespace E3DEngine
{
	class AnimationClip : public Component
	{
	public:
		std::string		Name;
		double			TimeLong;
		int				Index;
	private:
		aiAnimation		* m_aiAnimation;
	};
}

#endif /* AnimationClip_hpp */
