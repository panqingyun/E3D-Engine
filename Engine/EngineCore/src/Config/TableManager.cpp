#include "TableManager.h"
#include "TableBase.h"

namespace E3DEngine
{
    //NumericalFormula* TableManager::numerical = nullptr;
    void TableManager::RegisterTable(TiXmlNode * node,string name, TableBase * table)
    {
        if(table == nullptr)
		{
            return;
        }
        if(m_tabmap.find(name) != m_tabmap.end())
		{
            return;
        }
        table->Loaded(node);
        m_tabmap.insert(pair<string, TableBase*>(name, table));
    }
	
	TableManager::TableManager()
	{

	}

	TableManager::~TableManager()
	{
		DeleteAllTable();
	}

	E3DEngine::TableBase * TableManager::Select(string tableName, int ID)
	{
		if (tableName == "")
		{
			return nullptr;
		}
		tableName = ClassFactory::GetInstance().getTypeNameByClassName(tableName);
		if (m_tabmap.find(tableName) == m_tabmap.end())
		{
			return nullptr;
		}
		return m_tabmap[tableName]->Select(ID);
	}

	E3DEngine::TableBase * TableManager::Select(string tableName, int ID1, int ID2)
	{
		if (tableName == "")
		{
			return nullptr;
		}
		tableName = ClassFactory::GetInstance().getTypeNameByClassName(tableName);
		if (m_tabmap.find(tableName) == m_tabmap.end())
		{
			return nullptr;
		}
		return m_tabmap[tableName]->Select(ID1, ID2);
	}

	void TableManager::DeleteAllTable()
	{
		for(ittableMap it = m_tabmap.begin(); it != m_tabmap.end(); ++it)
		{
			TableBase* tbl = it->second;
			SAFE_DELETE(tbl);
		}
		m_tabmap.clear();
	}
}
