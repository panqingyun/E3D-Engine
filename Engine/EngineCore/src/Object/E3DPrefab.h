#pragma once

#include "E3DGameObject.h"

namespace E3DEngine
{
	class Prefab : public GameObject
	{
	public:
		Prefab();
		void SetFilePath(std::string path);
		std::string GetFilePath();
		virtual void CreateBehaviour() override;
		static Prefab *LoadPrefab(std::string path);
	private:
		std::string mFilePath;
	};
}