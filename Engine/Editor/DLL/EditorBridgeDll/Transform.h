#pragma once
#include <Source/EngineDelegate.h>
#include "Vector.h"

#pragma managed
namespace E3DEngine
{
	public ref class TransformRef
	{
	public:
		TransformRef(CTransform *transform);
	public:
		property Vector3^ Position
		{
			Vector3^ get()
			{
				mPosition->SetValue(&mTransform->Position);
				return mPosition;
			}
			void set(Vector3^ vec)
			{
				mPosition = vec;
				mTransform->SetPosition(vec->x, vec->y, vec->z);
			}
		}
		property Vector3^ Scale
		{
			Vector3^ get()
			{
				mScale->SetValue(&mTransform->Scale);
				return mScale;
			}
			void set(Vector3^ value)
			{
				mScale = value;
				mTransform->SetScale(value->x, value->y, value->z);
			}
		}
		property Vector3^ Rotation
		{
			Vector3^ get()
			{
				mRotation->SetValue(&mTransform->RotationEuler);
				return mRotation;
			}
			void set(Vector3^ value)
			{
				mRotation = value;
				mTransform->SetRotation(value->x, value->y, value->z);
			}
		}
	private:
		CTransform * mTransform;
		Vector3^ mPosition;
		Vector3^ mScale;
		Vector3^ mRotation;
	};
}

#pragma unmanaged