#pragma once

#include <Source/EngineDelegate.h>

#pragma managed
namespace E3DEngine
{
	public ref class Matrix3x3
	{
	public:
		Matrix3x3(vvision::mat3f *mat);
	public:
		float m11, m12, m13;
		float m21, m22, m23;
		float m31, m32, m33;

	private:
		vvision::mat3f *mMat;
	};

	public ref class Matrix4x4
	{
	public:
		Matrix4x4(vvision::mat4f *mat);
	public:
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;

	private:
		vvision::mat4f *mMat;
	};
}

#pragma unmanaged