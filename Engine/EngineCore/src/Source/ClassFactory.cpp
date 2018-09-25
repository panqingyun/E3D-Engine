#include "ClassFactory.h"



ClassFactory::~ClassFactory()
{
	m_classMap.clear();
}

void ClassFactory::Destory()
{
	m_classMap.clear();
}

void* ClassFactory::CreateClass(string className, string content /*= ""*/)
{
	className = E3DEngine::StringBuilder::Trim(className);
	map<string, createClass>::const_iterator iter;
	iter = m_classMap.find(className);
	if (iter == m_classMap.end())
	{
		return nullptr;
	}
	else
	{
		return iter->second();
	}
}

void ClassFactory::registClass(string name, createClass method)
{
	if (m_classMap.find(name) != m_classMap.end())
	{
		return;
	}
	m_classMap.insert(pair<string, createClass>(name, method));
}

std::string ClassFactory::getTypeNameByClassName(string className)
{
	if (m_classNameTypeID.find(className) == m_classNameTypeID.end())
	{
		return "NAN";
	}

	return m_classNameTypeID[className];
}

void ClassFactory::insertClassNameTypeid(string className, string typeName)
{
	if (m_classNameTypeID.find(className) != m_classNameTypeID.end())
	{
		return;
	}

	m_classNameTypeID[className] = typeName;
}

ClassFactory & ClassFactory::GetInstance()
{
	static ClassFactory _ins;
	return _ins;
}
