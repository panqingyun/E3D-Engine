//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2018-9-29  PanQingyun. All rights reserved. ************************//
#pragma once
#include "..\Utils\E3DUtil.hpp"

namespace E3DEngine
{
	class Prefab;
	class GameObject;
	/*
		加载预设
	*/
	E3D_EXPORT_DLL GameObject * LoadPrefab(std::string path);

	/*
		加载场景
	*/
	E3D_EXPORT_DLL void LoadSceneObjects(std::string sceneFilePath);

	/*
		注册解析函数
	*/
	void RegistScnObjCreateFunc();

	/*
		保存当前场景
	*/
	E3D_EXPORT_DLL void SaveCurrentScene();

	/*
		保存预设
	*/
	E3D_EXPORT_DLL void SavePrefab(Prefab *prefab);

	/*
		获取当前加载根路径
	*/
	E3D_EXPORT_DLL std::string GetCurLoadRootPath();
}