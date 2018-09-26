//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-21 PanQingyun. All rights reserved. *************************//

#ifndef E3DLight_hpp
#define E3DLight_hpp

#include "../Object/E3DGameObject.h"

#include <iostream>

namespace E3DEngine
{
	enum LightType
	{
		eDIRECTION_LIGHT = 1,
		ePOINT_LIGHT,
		eSPOT_LIGHT,
	};

	class E3D_EXPORT_DLL Light : public GameObject
	{
	public:
		static Light * Create(LightType type);
	public:
		LightType   Type;
		vec4f		Color;				// 颜色
		float		Intensity;			// 强度

	public:
		virtual void setBehaviourDefaultValue() override;

	public:
		virtual void CreateShadow() { }
		Light()
		{
			shadowCamera = nullptr;
		}
		virtual ~Light()
		{
			if (shadowCamera != nullptr)
			{
				SAFE_DELETE(shadowCamera);
			}
		}

	protected:
		Camera * shadowCamera;
	};

	class E3D_EXPORT_DLL PointLight : public Light
	{
	public:
		PointLight();
		float Range;

	public:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue();
		virtual void CreateShadow() override;
	};

	class E3D_EXPORT_DLL DirectionLight : public Light
	{
	public:
		DirectionLight();

	public:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue();
		virtual void CreateShadow() override;
	};

	class E3D_EXPORT_DLL SpotLight : public Light
	{
	public:
		SpotLight();
		float Range;
		int   SpotAngle;

	public:
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue();
		virtual void CreateShadow() override;
	};
	
}
#endif /* Light_hpp */
