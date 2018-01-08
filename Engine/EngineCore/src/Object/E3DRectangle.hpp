//
//  E3DRectangle.hpp
//
//  Created by 潘庆云 on 2017/7/6.
//

#ifndef E3Drectangle_hpp
#define E3Drectangle_hpp

#include <stdio.h>
#include "E3DRenderObject.hpp"

namespace E3DEngine
{
	class Rectangle extends GameObject
	{
	public:
		void CreateShape(float width, float height, bool up2down = false);
		void SetBlendType(DWORD type);
		void SetZWriteEnable(bool bEnable);

	private: 
		DWORD					m_BlendType;
		bool					m_ZWriteEnable;
	};
}

#endif /* E3Drectangle_hpp */
