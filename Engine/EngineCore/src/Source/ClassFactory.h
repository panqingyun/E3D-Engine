#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Source/Interface.h"
#include "../Object/E3DGameObject.h"

using namespace std;
using setValue = void(*)(void * t, object v);
using getValue = object(*)(void *t);

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
static void Set##varName(void * cp, object value)\
{\
	classType* tp = (classType*)cp; \
	tp->varName = object_cast<varType>(value); \
}\
varType Get##varName(void) const \
{\
return varName; \
}

#define SAVE_MEMBER(var, type)\
if (m_methodMap.find(#var) == m_methodMap.end())\
{\
	m_methodMap.insert(pair<std::string, setValue>(#var, Set##var));\
	m_propertyTypeMap.insert(pair<std::string, std::string>(#var, #type));\
}


#define DECLARE_PROPERTY(classType, varType, varName)\
public:\
varType varName;\
static void Set##varName(void * cp, object value)\
{\
	classType* tp = (classType*)cp; \
	tp->varName = object_cast<varType>(value); \
}\
static object Get##varName(void * cp) \
{\
	classType* tp = (classType*)cp; \
	return tp->varName; \
}


#define SAVE_PROPERTY(var, type)\
m_setMethodMap.insert(std::pair<std::string, setValue>(#var, Set##var));\
m_propertyTypeMap.insert(std::pair<std::string, DWORD>(#var, type));\
m_getMethodMap.insert(std::pair<std::string, getValue>(#var, Get##var));\

using createClass = void* (*)();

class E3D_EXPORT_DLL ClassFactory
{
private:
	ClassFactory() { };
	~ClassFactory();;
	
public:
	virtual void Init()
	{
	}
	virtual void Destory();
	void* CreateClass(string className,string content = "");
	
	static void func()
	{

	}

	void registClass(string name, createClass method);
	
	string getTypeNameByClassName(string className);
	
	void insertClassNameTypeid(string className, string typeName);
	
	static ClassFactory &GetInstance();
private:
	map<string, createClass> m_classMap;
	map<string, string> m_classNameTypeID;
};


