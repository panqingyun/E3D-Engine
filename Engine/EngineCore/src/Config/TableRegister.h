#ifndef _TABLEREGISTER_H_
#define _TABLEREGISTER_H_

#include "TableBase.h"
#include "TableManager.h"
#include "Table.h"

class TableRegister
{
public:
	static E3DEngine::TableManager * RegisterAllTable(const char * filePath)
    {
		std::string configName = std::string(filePath);
		TiXmlDocument * doc = nullptr;
		if (instance().xmlConfigMap.find(configName) == instance().xmlConfigMap.end())
		{
			doc = new TiXmlDocument(configName.c_str());
			instance().xmlConfigMap[configName] = doc;  
			bool loadOkay = doc->LoadFile();
			if (!loadOkay)
			{
				return nullptr;
			}
		}
		else
		{
			doc = instance().xmlConfigMap[configName];
		}
      
		E3DEngine::TableManager * tableManager = new E3DEngine::TableManager;
        E3DEngine::RegisterTableCreateInstance();
        TiXmlElement* rootElem = nullptr;
        rootElem = doc->RootElement();
        bool needContinue = false;
        for(TiXmlNode * item = rootElem->FirstChild(); item != nullptr; item = item->NextSibling())
        {
            std::string tableName = item->Value();
            if(needContinue == true){
                needContinue = false;
                continue;
            }
			tableName = ClassFactory::GetInstance().getTypeNameByClassName(tableName);
            E3DEngine::TableBase * table = (E3DEngine::TableBase*)ClassFactory::GetInstance().CreateClass(tableName);
            if(table == nullptr){
                continue;
            }
            table->registProperty();
            tableManager->RegisterTable(item, tableName, table);
            if(table->initTableParam() == false)
            {
                continue;
            }
        }
        return tableManager;
    }
	
	static void DeleteAllTable()
	{
		
	}

	static void Destory()
	{
		for (auto &xmlDoc : instance().xmlConfigMap)
		{
			SAFE_DELETE(xmlDoc.second);
		}
		instance().xmlConfigMap.clear();
	}
private:
	std::map<std::string, TiXmlDocument*> xmlConfigMap;
private:
	static TableRegister &instance()
	{
		static TableRegister _ins;
		return _ins;
	}
};

#endif
