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
	class Rectangle : public GameObject
	{
	public:
		void CreateShape(float width, float height, bool up2down = false);
		void SetZWriteEnable(bool bEnable);

	private: 
		bool					m_ZWriteEnable;
	};
}

#endif /* E3Drectangle_hpp */
