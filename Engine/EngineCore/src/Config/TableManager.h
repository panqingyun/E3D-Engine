//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-10 PanQingyun. All rights reserved. *************************//
#ifndef _TABLEMANAGER_H_
#define _TABLEMANAGER_H_

#include "TableBase.h"

namespace E3DEngine
{

    class TableManager : public Ref
    {
    public:
        TableManager(); 
        virtual ~TableManager() override;

        using tableMap		= std::map<const std::string, TableBase*>;
        using ittableMap	= std::map<const std::string, TableBase*>::const_iterator;

    public:
        template<typename T> T * GetTableInstance(string tableName)
        {
            if (m_tabmap.find(tableName) != m_tabmap.end())
			{
                return static_cast<T*>(m_tabmap[tableName]);
            }
            return nullptr;
        }

        template<typename T> T*  Select(int ID)
        {
            string name = GetClassName<T>();
            if(name == "")
			{
                return nullptr;
            }
            if(m_tabmap.find(name) == m_tabmap.end())
			{
                return nullptr;
            }
            return m_tabmap[name]->Select<T>(ID);
        }
        template<typename T> T*  Select(int ID1, int ID2)
        {
            string name = GetClassName<T>();
            if(name == "")
			{
                return nullptr;
            }
            if(m_tabmap.find(name) == m_tabmap.end())
			{
                return nullptr;
            }
            return m_tabmap[name]->Select<T>(ID1, ID2);
        }
        
        template<typename T> vector<T*>* GetTable()
        {
            string name = GetClassName<T>();
            if(name == "")
			{
                return nullptr;
            }
            if(m_tabmap.find(name) == m_tabmap.end())
			{
                return nullptr;
            }
            return m_tabmap[name]->GetTable<T>();
        }

	public:
		void		DeleteAllTable();
        TableBase * Select(string tableName, int ID);        
		TableBase * Select(string tableName, int ID1, int ID2);
		void		RegisterTable(TiXmlNode * node, const std::string name, TableBase* p);
        
    private:
        tableMap m_tabmap;
    };

}

#endif
