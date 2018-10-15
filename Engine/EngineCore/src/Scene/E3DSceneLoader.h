//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2018-9-29  PanQingyun. All rights reserved. ************************//
#pragma once
#include "../Config/TableRegister.h"

namespace E3DEngine
{
	class Prefab;
	/*
		加载预设
	*/
	GameObject * LoadPrefab(std::string path);

	/*
		加载场景
	*/
	void LoadSceneObjects(string sceneFilePath);

	/*
		注册解析函数
	*/
	void RegistScnObjCreateFunc();

	/*
		保存当前场景
	*/
	void SaveCurrentScene();

	/*
		保存预设
	*/
	void SavePrefab(Prefab *prefab);
}