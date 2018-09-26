//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-1-10 PanQingyun. All rights reserved. *************************//
#ifndef _TABLE_BASE_H_
#define _TABLE_BASE_H_
#include "../Object/E3DGameObject.h"
#include "../Source/ClassFactory.h"

#ifndef __IGNORED_INCLUDE__
#include "../Source/tinyxml.h"
#endif

namespace E3DEngine
{
    class TableQuery
    {
    private:
        map < int, map<string, string>> table;
        static TableQuery * query;
        static string selectKey;
    private:
        TableQuery() = default;
        ~TableQuery() = default;

		static TableQuery * getInstance();
    public:
        static TableQuery * Select(std::string key);
        static TableQuery * From(map<int, map<string, string>> table);

    public:
        string Where(string key, _Equal_ int value);
        string Where(string key1, _Equal_ int value1, string key2, _Equal_ int value2);
    private:
        map<string, string> * selectMap(string key, int value);
    };

    class E3D_EXPORT_DLL TableBase : public IObject
    {
    protected:
        DECLARE_CLASS(TableBase)
    public:
        static void* createInstance(string content = "");
		TableBase() = default;
		virtual ~TableBase();
        virtual void registProperty() { }
        virtual void display() { }
        virtual bool initTableParam(){return true;}
		TableBase * Select(int key);
		TableBase * Select(int key1, int key2);
#ifndef __IGNORED_INCLUDE__
		void Loaded(TiXmlNode * node);
#endif
		void LoadTable(std::string tableName, std::map<int, std::map<std::string, std::string>> tableMap);

	public:
        template<typename T> T* Select(int key) const
        {
            if(tablePointerMap.empty() == true){
                return nullptr;
            }
            map<int, TableBase*>::const_iterator it = tablePointerMap.find(key); 
            if(it == tablePointerMap.end()){
                return nullptr;
            }
            return reinterpret_cast<T*>(it->second);
        }

        template<typename T> T * Select(int key1, int key2) const
        {
            int keyhash = key1 * 10000 + key2;
            return Select<T>(keyhash);    
        }
        
        template<typename T> vector<T*>* GetTable() const
        {
            vector<T*> *list = new vector<T*>();

            for(const auto & it : tablePointerMap)
			{
                list->push_back(static_cast<T*>(it.second));
            }
            return list;
        }

    protected:
        void convertTypeSetValue(setValue &set, string value, string type);
        void processSelectResult(map<string, string> * configItem);
        virtual std::string GetKey1();
        virtual std::string GetKey2();

	public:
		std::string Name;
		std::string ID;
		std::string FilePath;
		int Type;

		map<string, setValue> m_methodMap;
		map<string, string> m_propertyTypeMap;
		std::map<int, TableBase*> tablePointerMap;

    };

}

#endif // end of TableBase


