//
//  Light.hpp
//
//  Created by 潘庆云 on 2017/3/21.
//

#ifndef E3DLight_hpp
#define E3DLight_hpp

#include "../Object/E3DGameObject.h"

#include <iostream>

namespace E3DEngine
{
	class Light extends GameObject
	{
	public:
		DWORD		LightType;
		vec4f		Color;				// 颜色
		float		Intensity;			// 强度
		vec4f		FadeFactors;
	};

	class PointLight : public Light
	{
	public:
		float Range;
	};

	class DirectionLight : public Light
	{
	public:
		vec3f		Direction;			// 方向
	};

	class SpotLight : public Light
	{
	public:
		float Range;
		int   SpotAngle;
		vec4f Position;
	};
	
}
#endif /* Light_hpp */
