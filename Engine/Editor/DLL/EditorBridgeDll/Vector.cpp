#include "Vector.h"

#pragma managed

namespace E3DEngine
{
	Vector2::Vector2(vvision::vec2f *vec)
	{
		SetValue(vec);
	}

	Vector2::Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2::Vector2(float _x, float _y)
	{
		SetValue(_x, _y);
	}

	void Vector2::SetValue(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	void Vector2::SetValue(vvision::vec2f *vec)
	{
		mVec = vec;
		x = vec->x;
		y = vec->y;
	}

	System::String^ Vector2::ToString()
	{
		return "" + x.ToString() + "," + y.ToString();
	}

	Vector3::Vector3(vvision::vec3f * vec)
	{
		SetValue(vec);
	}

	Vector3::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3::Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void Vector3::SetValue(vvision::vec3f *vec)
	{
		mVec = vec;
		x = vec->x;
		y = vec->y;
		z = vec->z;
	}

	System::String^ Vector3::ToString()
	{
		return "" + x.ToString() + "," + y.ToString() + "," + z.ToString();
	}

	Vector4::Vector4(vvision::vec4f *vec)
	{
		SetValue(vec);
	}

	Vector4::Vector4(float _x, float _y, float _z, float _w)
	{
		SetValue(_x, _y, _z, _w);
	}

	void Vector4::SetValue(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Vector4::SetValue(vvision::vec4f *vec)
	{
		mVec = vec;
		x = vec->x;
		y = vec->y;
		z = vec->z;
		w = vec->w;
	}

	System::String^ Vector4::ToString()
	{
		return "" + x.ToString() + "," + y.ToString() + "," + z.ToString() + "," + w.ToString();
	}

}

#pragma unmanaged