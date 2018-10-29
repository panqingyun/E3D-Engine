//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-12-7  PanQingyun. All rights reserved. *************************//
#pragma once

#include "E3DBox.h"
#include "../Config/Table.h"

namespace E3DEngine
{
	class E3D_EXPORT_DLL SkyBox : public Box
	{
	public:
		virtual void Create(float l, float w, float h) override;
		virtual void TransferRender() override;
		virtual void PrepareUpdate(float deltaTime) override;
	private:
		void setTextureCoord();
		void getCoord(int index, vec2f &leftTop, vec2f &rightTop, vec2f &leftDown, vec2f &rightDown);
	private:
		std::vector<TextureAtlasConfig*> textures;
	};

	class SkyDome : public GameObject
	{
	public:
		SkyDome();
		virtual void Create(float R);

		void fillVertex(float R);
		virtual void PrepareUpdate(float deltaTime) override;

	};
}