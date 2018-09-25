#include "Transform.h"

#pragma managed

namespace E3DEngine
{

	TransformRef::TransformRef(CTransform *transform)
	{
		mTransform = transform;
		mPosition = gcnew Vector3(&mTransform->Position);
		mRotation = gcnew Vector3(&mTransform->RotationEuler);
		mScale = gcnew Vector3(&mTransform->Scale);
	}

}

#pragma unmanaged