//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-7-7  PanQingyun. All rights reserved. *************************//
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
