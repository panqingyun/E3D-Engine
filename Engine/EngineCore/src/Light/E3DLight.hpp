//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-21 PanQingyun. All rights reserved. *************************//

#ifndef E3DLight_hpp
#define E3DLight_hpp

#include "../Component/E3DComponent.hpp"

#include <iostream>
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	enum LightType
	{
		eDIRECTION_LIGHT = 1,
		ePOINT_LIGHT,
		eSPOT_LIGHT,
	};

	class E3D_EXPORT_DLL Light : public Component
	{
	public:
		LightType   Type;
		float		Intensity;			// 强度

	public:
		virtual void setBehaviourDefaultValue() override;
		virtual void OnCreateComplete() override;
	public:
		virtual void MakeShadow() { }
		Light()
		{
			
		}
		virtual ~Light()
		{
		}

		Camera * GetShadowCamera();
	public:
		DECLARE_METHOD(Light, bool, CreateShadow);
		virtual void registProperty() override
		{
			SAVE_METHOD(CreateShadow, FT_BOOLEAN);
		}

	protected:
		Camera * shadowCamera;
	};

	class E3D_EXPORT_DLL PointLight : public Light
	{
		DECLARE_CLASS(PointLight)
	public:
		PointLight();
		float Range;

	public:
		virtual void MakeShadow() override;
	};

	class E3D_EXPORT_DLL DirectionLight : public Light
	{
		DECLARE_CLASS(DirectionLight)
	public:
		DirectionLight();

		DECLARE_METHOD(DirectionLight, vec3f, CenterPosition);
		DECLARE_METHOD(DirectionLight, vec2f, Range);
		virtual void registProperty()
		{
			Light::registProperty();
			SAVE_METHOD(CenterPosition, FT_VECTOR3);
			SAVE_METHOD(Range, FT_VECTOR2);
		}
	public:
		virtual void MakeShadow() override;
		virtual void OnCreateComplete() override;
		void SetDirection(vec3f dir);
		vec3f &GetDirection();
	private:
		vec3f mDirection;
	};

	class E3D_EXPORT_DLL SpotLight : public Light
	{
		DECLARE_CLASS(SpotLight)
	public:
		SpotLight();
		float Range;
		int   SpotAngle;

	public:
		virtual void MakeShadow() override;
	};
	
}
#endif /* Light_hpp */
