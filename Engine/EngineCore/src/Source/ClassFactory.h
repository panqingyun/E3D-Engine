#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Source/Interface.h"
#include "../Object/E3DGameObject.h"

#define DECLARE_CLASS(className) \
public:\
static void * createInstance()\
{\
return new className;\
}\
static std::string ClassName;\

#define DECLARE_CLASS_NAME(className) \
std::string className::ClassName = typeid(className).name(); \


#define REGIST_CLASS(className)  \
ClassFactory::GetInstance().registClass(typeid(className).name(), className::createInstance); \
ClassFactory::GetInstance().insertClassNameTypeid(#className, typeid(className).name());


#define DECLARE_MEMBER(classType, varType, varName)\
public:\
varType varName;\
static void set##varName(void * cp, object value)\
{\
classType* tp = (classType*)cp; \
tp->varName = object_cast<varType>(value); \
}\
varType get##varName(void) const \
{\
return varName; \
}

#define SAVE_MEMBER(var, type)\
m_methodMap.insert(pair<string, setValue>(#var, set##var));\
m_propertyTypeMap.insert(pair<string, string>(#var, #type));

using setValue = void(*)(void * t, object v);

using namespace std;
using createClass = void* (*)();

class ClassFactory
{
private:
	ClassFactory() { };
	~ClassFactory()
	{
		m_classMap.clear();
	};
	
public:
	virtual void Init()
	{
	}
	virtual void Destory()
	{
		m_classMap.clear();
	}
	void* CreateClass(string className,string content = "")
	{
		className = E3DEngine::StringBuilder::Trim(className);
		map<string, createClass>::const_iterator iter;
		iter = m_classMap.find(className);
		if(iter == m_classMap.end())
		{
			return nullptr;
		}
		else
		{
			return iter->second();
		}
	}
	
	static void func()
	{

	}

	void registClass(string name, createClass method)
	{
		if (m_classMap.find(name) != m_classMap.end())
		{
			return;
		}
		m_classMap.insert(pair<string, createClass>(name, method));
	}
	
	string getTypeNameByClassName(string className)
	{
		if (m_classNameTypeID.find(className) == m_classNameTypeID.end())
		{
			return "NAN";
		}
		
		return m_classNameTypeID[className];
	}
	
	void insertClassNameTypeid(string className, string typeName)
	{
		if (m_classNameTypeID.find(className) != m_classNameTypeID.end())
		{
			return;
		}
		
		m_classNameTypeID[className] = typeName;
	}
	
	static ClassFactory &GetInstance()
	{
		static ClassFactory _ins;
		return _ins;
	}
private:
	map<string, createClass> m_classMap;
	map<string, string> m_classNameTypeID;
};


