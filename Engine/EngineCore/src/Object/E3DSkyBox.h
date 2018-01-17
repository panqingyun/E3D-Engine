#pragma once

#include "E3DBox.h"
#include "../Config/Table.h"

namespace E3DEngine
{
	class SkyBox : public Box
	{
	public:
		virtual void Create(float l, float w, float h) override;
		virtual void SetMaterial(Material * material) override;
		virtual void PrepareUpdate(float deltaTime) override;
	private:
		void setTextureCoord();
		void getCoord(int index, vec2f &leftTop, vec2f &rightTop, vec2f &leftDown, vec2f &rightDown);
	private:
		std::vector<TextureAtlas*> textures;
	};

	class SkyDome : public GameObject
	{
	public:
		virtual void Create(float R);
		virtual void SetMaterial(Material * material) override;
		virtual void PrepareUpdate(float deltaTime) override;
	private:
		void setTextureCoord();
		void getCoord(int index, vec2f &leftTop, vec2f &rightTop, vec2f &leftDown, vec2f &rightDown);
	private:
		std::vector<TextureAtlas*> textures;
	};
}