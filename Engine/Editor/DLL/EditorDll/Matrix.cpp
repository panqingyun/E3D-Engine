#include "Matrix.h"

#pragma managed

namespace E3DEngine
{

	Matrix3x3::Matrix3x3(vvision::mat3f *mat)
	{
		mMat = mat;
	}

	Matrix4x4::Matrix4x4(vvision::mat4f *mat)
	{
		mMat = mat;
	}

}

#pragma unmanaged