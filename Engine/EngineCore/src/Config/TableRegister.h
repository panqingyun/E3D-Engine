//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-10 PanQingyun. All rights reserved. *************************//
#ifndef _TABLEREGISTER_H_
#define _TABLEREGISTER_H_

#include "TableBase.h"
#include "TableManager.h"
#include "Table.h"

class E3D_EXPORT_DLL TableRegister
{
public:
	static E3DEngine::TableManager * GetTableManager(const char * filePath)
    {
		std::string configName = std::string(filePath);
		TiXmlDocument * doc = nullptr;
		if (instance().mTableManagerMap.find(configName) == instance().mTableManagerMap.end())
		{
			doc = new TiXmlDocument(configName.c_str());
			bool loadOkay = doc->LoadFile();
			if (!loadOkay)
			{
				return nullptr;
			}

			E3DEngine::TableManager * tableManager = new E3DEngine::TableManager;
			instance().mTableManagerMap[configName] = tableManager;
			E3DEngine::RegisterTableCreateInstance();
			TiXmlElement* rootElem = nullptr;
			rootElem = doc->RootElement();
			bool needContinue = false;
			for (TiXmlNode * item = rootElem->FirstChild(); item != nullptr; item = item->NextSibling())
			{
				std::string tableName = item->Value();
				if (needContinue == true) {
					needContinue = false;
					continue;
				}
				tableName = ClassFactory::GetInstance().getTypeNameByClassName(tableName);
				E3DEngine::TableBase * table = (E3DEngine::TableBase*)ClassFactory::GetInstance().CreateClass(tableName);
				if (table == nullptr) {
					continue;
				}
				table->registProperty();
				tableManager->RegisterTable(item, tableName, table);
				if (table->initTableParam() == false)
				{
					continue;
				}
			}
			return tableManager;
		}
		else
		{
			return instance().mTableManagerMap[configName];
		}
      
    }
	
	static void DeleteAllTable()
	{
		
	}

	static void Destory()
	{
		for (auto &tbManager : instance().mTableManagerMap)
		{
			SAFE_DELETE(tbManager.second);
		}
		instance().mTableManagerMap.clear();
	}
private:
	std::map<std::string, E3DEngine::TableManager*> mTableManagerMap;
private:
	static TableRegister &instance()
	{
		static TableRegister _ins;
		return _ins;
	}
};

#endif
