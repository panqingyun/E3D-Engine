//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//
#pragma once

#include "E3DBox.h"
#include "../Config/Table.h"
#include "../Source/ClassFactory.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL SkyBox : public Box
	{
		DECLARE_CLASS(SkyBox)
	public:
		SkyBox();
		virtual void Update(float deltaTime) override;
		virtual void Awake() override;
	};

	class SkyDome : public Component
	{
		DECLARE_CLASS(SkyDome)
	public:
		SkyDome();
		virtual void Awake() override;
		virtual void Update(float deltaTime) override;

	private:
		void fillVertex(float R);

	};
}