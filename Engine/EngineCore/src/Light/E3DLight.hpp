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
		float		Intensity;			// 强度

	public:
		virtual void setBehaviourDefaultValue() override;

	public:
		virtual void CreateShadow() { }
		Light()
		{
			mCreateShadow = false;
			shadowCamera = nullptr;
		}
		virtual ~Light()
		{
		}

		bool GetCreateShadow() { return mCreateShadow; }
		Camera * GetShadowCamera();
	protected:
		Camera * shadowCamera;
		bool	mCreateShadow;
	};

	class E3D_EXPORT_DLL PointLight : public Light
	{
	public:
		PointLight();
		float Range;

	public:
		virtual void CreateShadow() override;
	};

	class E3D_EXPORT_DLL DirectionLight : public Light
	{
	public:
		DirectionLight();

	public:
		virtual void CreateShadow() override;
		virtual void CreateComplete() override;
		virtual void TransformChange() override;

		void SetDirection(vec3f dir);
		vec3f &GetDirection();
	private:
		vec3f mDirection;
	};

	class E3D_EXPORT_DLL SpotLight : public Light
	{
	public:
		SpotLight();
		float Range;
		int   SpotAngle;

	public:
		virtual void CreateShadow() override;
	};
	
}
#endif /* Light_hpp */
