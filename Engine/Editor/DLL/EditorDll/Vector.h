#pragma once
#include <Source/vmath.h>

#pragma managed
using namespace System;
namespace E3DEngine
{
	public ref class Vector2
	{
	public:
		Vector2(vvision::vec2f *vec);
		void SetValue(vvision::vec2f *vec);
		String^ ToString() override;
	public:
		float x;
		float y;

	private:
		vvision::vec2f *mVec;
	};

	public ref class Vector3
	{
	public:
		Vector3(vvision::vec3f * vec);
		void SetValue(vvision::vec3f *vec);
		String^ ToString() override;
	public: 
		float x;
		float y;
		float z;

	private:
		vvision::vec3f *mVec;
	};

	public ref class Vector4
	{
	public:
		Vector4(vvision::vec4f *vec);
		void SetValue(vvision::vec4f *vec);

		String^ ToString() override;
	public:
		float x;
		float y;
		float z;
		float w;

	private: 
		vvision::vec4f *mVec;
	};
}
#pragma unmanaged