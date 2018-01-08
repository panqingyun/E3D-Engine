#include "TableBase.h"

namespace E3DEngine
{
    TableQuery * TableQuery::query = nullptr;
	std::string TableQuery::selectKey = "";

	E3DEngine::TableQuery * TableQuery::getInstance()
	{
		if (query == nullptr)
		{
			query = new TableQuery;
		}
		return query;
	}

	E3DEngine::TableQuery * TableQuery::Select(std::string key)
	{
		query = getInstance();
		query->selectKey = key;
		return query;
	}

	E3DEngine::TableQuery * TableQuery::From(map<int, map<string, string>> table)
	{
		query->table = table;
		return query;
	}

	std::string TableQuery::Where(string key, _Equal_ int value)
	{
		map<string, string> newMap;
		newMap = *selectMap(key, value);
		return newMap[selectKey];
	}

	std::string TableQuery::Where(string key1, _Equal_ int value1, string key2, _Equal_ int value2)
	{
		map<string, string> newMap;
		int keyhash = value1 * 10000 + value2;
		if (table.find(keyhash) != table.end() && table[keyhash].find(key1) != table[keyhash].end())
		{
			if (table[keyhash].find(key2) != table[keyhash].end() && Convert::ToInt(table[keyhash][key2]) == value2)
			{
				newMap = table[keyhash];
			}
		}
		return newMap[selectKey];
	}

	std::map<std::string, std::string> * TableQuery::selectMap(string key, int value)
	{
		map<string, string> * newMap = nullptr;
		if (table.find(value) != table.end() && table[value].find(key) != table[value].end())
		{
			if (Convert::ToInt(table[value][key]) == value)
			{
				newMap = &table[value];
			}
		}
		return newMap;
	}

	TableBase::~TableBase()
	{
		for (std::map<int, TableBase*>::iterator it = tablePointerMap.begin();
			it != tablePointerMap.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		tablePointerMap.clear();
		m_methodMap.clear();
		m_propertyTypeMap.clear();
	}

	void TableBase::Loaded(TiXmlNode * node)
	{
        std::map<int, std::map<std::string, std::string>> tableMap;
        for(TiXmlNode *item = node->FirstChild("Item"); item != nullptr; item = item->NextSibling("Item")){
            map<string, string> node_map;
            for(TiXmlAttribute * attr = item->ToElement()->FirstAttribute(); attr != nullptr; attr = attr->Next()){
                string _name(attr->Name());
                string _value(attr->Value());
                node_map.insert(pair<string, string>(_name, _value));
            }
            int key = Convert::ToInt(node_map[GetKey1()]);
            if(GetKey1() != GetKey2()){
                key = Convert::ToInt(node_map[GetKey1()]) * 10000 + Convert::ToInt(node_map[GetKey2()]);
            }
            tableMap.insert(pair<int, map<string, string>>(key, node_map));
        }
        LoadTable(node->Value(), tableMap);
    }

	E3DEngine::TableBase * TableBase::Select(int key1, int key2)
	{
		int keyhash = key1 * 10000 + key2;
		return Select(keyhash);
	}

	E3DEngine::TableBase * TableBase::Select(int key)
	{
		if (tablePointerMap.empty() == true){
			return nullptr;
		}
		map<int, TableBase*>::const_iterator it = tablePointerMap.find(key);
		if (it == tablePointerMap.end()){
			return nullptr;
		}
		return it->second;
	}

	void TableBase::LoadTable(std::string tableName, std::map<int, std::map<std::string, std::string>> tableMap)
	{
		string name = ClassFactory::GetInstance().getTypeNameByClassName(tableName);

		for (map<int, map<string, string>>::const_iterator it = tableMap.begin(); it != tableMap.end(); ++it){
			map<string, string> element = it->second;
			TableBase *sourceObj = (TableBase*)ClassFactory::GetInstance().CreateClass(name);
			sourceObj->registProperty();
			for (auto & itr : m_propertyTypeMap)
			{
				if (element.find(itr.first) == element.end())
				{
					continue;
				}
				sourceObj->convertTypeSetValue(sourceObj->m_methodMap[itr.first], element[itr.first], itr.second);
			}
			tablePointerMap.insert(std::pair<int, TableBase*>(it->first, sourceObj));
		}
	}

	void TableBase::convertTypeSetValue(setValue & set, string value, string type)
    {
        if(type == stringType){
            set(this,value);
        }
        else if(type == intType){
            set(this, Convert::ToInt(value));
        }
        else if(type == floatType){
            set(this, Convert::ToFloat(value));
        }
        else if(type == doubleType){
            set(this, Convert::ToDouble(value));
		}
        else{
            //NumericalFormula * spClass =  (NumericalFormula*)ClassFactory::GetInstance().CreateInstance(type,value);
            //NumericalFormula spClass(type,value);
            //set(this, *spClass);
        }
    }

    void TableBase::processSelectResult(map<string, string> *configItem)
    {
        for(auto & it : m_propertyTypeMap){
            if(configItem->find(it.first) == configItem->end()){
                continue;
            }
            if(m_methodMap.find(it.first) == m_methodMap.end()){
                continue;
            }
            convertTypeSetValue(m_methodMap[it.first], (*configItem)[it.first], it.second);
        }
    }
}
