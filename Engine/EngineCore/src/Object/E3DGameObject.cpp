//
//  Object.cpp
//
//  Created by 潘庆云 on 2017/3/1.
//

#include <stdio.h>
#include "E3DGameObject.h"
#include "../Source/EngineDelegate.h"
#include "E3DTransform.hpp"
#include <stdarg.h>
#include "E3DRenderObject.hpp"

namespace E3DEngine
{
	
	void GameObject::SetActive(bool isActive)
	{
		if (isActive == IsActive)
		{
			return;
		}
		IsActive = isActive;
		
		if (ActiveChangeEvent.empty() == false)
		{
			ActiveChangeEvent(this,nullptr);
		}
		for(auto & Child : Transform->Childs)
		{
			if(Child.second->gameObject != nullptr)
			{
				Child.second->gameObject->SetActive(isActive);
			}
		}
	}
	
	std::vector<Component*> * GameObject::GetComponents(std::string type_name)
	{
		return &m_listComponents[type_name];
	}

	Component * GameObject::AddComponent(const char * type_name)
	{
		Component * component	= (Component *)ClassFactory::GetInstance().CreateClass(type_name);
		if (component == nullptr)
		{
			return nullptr;
		}
		component->Awake();
		(component)->gameObject = this;
		(component)->_TypeName = type_name;
		(component)->Transform = Transform;
		component->Start();
		m_listComponents[type_name].push_back((Component*)component);
		return component;
	}
	
	Component * GameObject::AddComponent(E3DEngine::Component *component)
	{
		if (component == nullptr)
		{
			return nullptr;
		}
		component->Awake();
		(component)->gameObject	= this;
		(component)->Transform  = Transform;
		component->Start();
		m_listComponents[(component)->_TypeName].push_back(component);
		return component;
	}
	
	void GameObject::RemoveComponent(Component *com)
	{
		std::string type_name = com->_TypeName;
		std::map<std::string, std::vector<Component*>>::iterator itr = m_listComponents.find(type_name);
		if (itr != m_listComponents.end())
		{
			m_listComponents.erase(itr);
		}
	}

	void GameObject::PrepareUpdate(float deltaTime)
	{

	}

	void GameObject::AfterUpdate(float deltaTime)
	{

	}

	void GameObject::Create(Object * parentNode)
	{
		if (parentNode == nullptr)
		{// add to current scene root node
			
		}
	}

	void GameObject::Update(float deltaTime)
	{
		if (IsActive)
		{
			PrepareUpdate(deltaTime);
			for (auto & m_listComponent : m_listComponents)
			{
				for (auto & itr : m_listComponent.second)
				{
					itr->Update(deltaTime);
				}
			}
			AfterUpdate(deltaTime);
			for (auto &node : childNode)
			{
				if (!node.second->IsActive)
				{
					continue;
				}
				node.second->Update(deltaTime);
			}
		}
	}
	
	GameObject::~GameObject()
	{
		for (auto & m_listComponent : m_listComponents)
		{
			for (auto & itr : m_listComponent.second)
			{
				itr->Destory();
				SAFE_DELETE(itr);
			}
		}
		if (ParentNode != nullptr)
		{
			ParentNode->RemoveChild(ID);
			ParentNode->Transform->RemoveChild(ID);
		}
		int childSize = childNode.size();
		for (int i = 0; i < childSize; i++)
		{
			auto node = childNode.begin()->second;
			childNode.erase(node->ID);
			SAFE_DELETE(node);
		}
		m_listComponents.clear();
	}
	
	void GameObject::SetParent(GameObject * parent)
	{
		if (ParentNode != nullptr)
		{
			ParentNode->RemoveChild(this);
		}
		if (parent != nullptr)
		{
			parent->AddChild(this);
		}
	}


	E3DEngine::GameObject * GameObject::FindChild(QWORD id)
	{
		if (childNode.find(id) == childNode.end())
		{
			GameObject * _child = nullptr;
			for (auto & child : childNode)
			{
				_child = child.second->FindChild(id);
				if (_child != nullptr)
				{
					break;
				}
			}
			return _child;
		}
		else
		{
			return childNode[id];
		}
	}


	E3DEngine::GameObject * GameObject::FindChild(std::string name)
	{
		GameObject * _child = nullptr;
		for (const auto &child : childNode)
		{
			if (child.second->Name == name)
			{
				_child = child.second;
				break;
			}
			else
			{
				_child = child.second->FindChild(name);
				if (_child != nullptr)
				{
					break;
				}
			}
		}
		return _child;
	}


	DWORD GameObject::GetLayerMask()
	{
		return m_layerMask;
	}


	void GameObject::SetLayerMask(DWORD layerMask)
	{
		m_layerMask = layerMask;
		if (NodeType != eT_Camera)
		{

		}
		m_pBehaviour->SetFieldValue("layerMask", &m_layerMask);
	}

	GameObject::GameObject()
	{
		Transform = new CTransform;
		Transform->gameObject = this;
		TypeName = typeid(this).name();
		IsEmptyObject = true;
		DontDestoryOnLoad = false;
		NodeType = eT_GameObject;
		pCamera = nullptr;
		IsActive = true;
		m_pRenderer = nullptr;
		ParentNode = nullptr;
		Scene * pScene = SceneManager::GetInstance().GetCurrentScene();
		if (pScene != nullptr)
		{
			pScene->AddChild(this);
		}
		m_layerMask = -1;
	}
	
	void GameObject::SetCamera(E3DEngine::Camera *camera)
	{
		pCamera = camera;
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->SetCamera(camera);
		}
	}
	
	void GameObject::SetDontDestory(bool dontDestory)
	{
		DontDestoryOnLoad = dontDestory;
	}

	void GameObject::OnCollisionEnter(GameObject * other)
	{
		for (std::map<std::string, std::vector<Component*>>::iterator it = m_listComponents.begin();
			it != m_listComponents.end(); it ++)
		{
			for (auto & com : it->second)
			{
				static_cast<Component*>(com)->OnCollisionEnter(other);
			}
		}
	}


	void GameObject::TransformChange()
	{
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->TransformChange();
		}
	}

	bool GameObject::IsRenderObject(GameObject * node)
	{
		if (node->NodeType == eT_NormalRenderObject)
		{
			return true;
		}
		return false;
	}


	void GameObject::AddChild(GameObject * node)
	{
		if (node == nullptr)
		{
			return;
		}
		GameObject *go = static_cast<GameObject*>(node);

		Transform->AddChild(node->ID, go->Transform);
		if (node->ParentNode == this)
		{
			return;
		}
		if (node->ParentNode != nullptr)
		{
			node->ParentNode->RemoveChild(node);
		}
		if (childNode.find(node->ID) == childNode.end())
		{
			childNode[node->ID] = node;
			node->ParentNode = this;
			if (NodeType != eT_Scene)
			{
				if (NodeType == eT_Camera)
				{
					SceneManager::GetInstance().GetCurrentScene()->AddCamera(static_cast<Camera*>(node));
				}
			}

		}
	}


	void GameObject::RemoveChild(GameObject * node)
	{
		if (node == nullptr)
		{
			return;
		}

		Transform->RemoveChild(node->ID);
		if (childNode.find(node->ID) == childNode.end())
		{
			return;
		}
		childNode.erase(childNode.find(node->ID));
		if (pCamera != nullptr)
		{
			pCamera->GetRenderQueue()->Remove(node);
		}
		
		node->ParentNode = nullptr;
		SAFE_DELETE(node);
	}


	void GameObject::RemoveChild(QWORD ID)
	{
		Transform->RemoveChild(ID);
		if (childNode.find(ID) == childNode.end())
		{
			return;
		}
		if (pCamera != nullptr)
		{
			pCamera->GetRenderQueue()->Remove(childNode[ID]);
		}			

		childNode[ID]->ParentNode = nullptr;
		childNode.erase(childNode.find(ID));
		SAFE_DELETE(childNode[ID]);
	}


	void GameObject::DestoryAllChild()
	{
		for (auto &node : childNode)
		{
			Transform->RemoveChild(node.second->ID);
			SAFE_DELETE(node.second);
		}

		childNode.clear();
	}


	void GameObject::Render(float deltaTime)
	{
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->Render(deltaTime);
		}
	}


	void GameObject::SetRenderIndex(DWORD index)
	{
		RenderIndex = index;
		if (SceneManager::GetInstance().GetCurrentScene() == nullptr)
		{
			return;
		}
		SceneManager::GetInstance().GetCurrentScene()->ChangeRenderIndex(ID, (eRenderIndex)index);
	}


	E3DEngine::RenderObject * GameObject::GetRenderer()
	{
		return m_pRenderer;
	}

	void GameObject::ComponentAdded(Component * component)
	{

	}

	void GameObject::SetMaterial(Material *material)
	{
		if (m_pRenderer == nullptr)
		{
			return;
		}

		m_pRenderer->pMaterial = material;
	}

	Material * GameObject::GetMaterial()
	{
		if (m_pRenderer == nullptr)
		{
			return nullptr;
		}

		return m_pRenderer->pMaterial;
	}


	void GameObject::CreateBehaviour()
	{
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(GameObject);
		setBehaviourDefaultValue();
	}


	void GameObject::setBehaviourDefaultValue()
	{
		Object::setBehaviourDefaultValue();
		TRANSFER_FIELD_OBJECT(Transform);
		m_pBehaviour->Awake();
		m_pBehaviour->Start();
	}

	StringBuilder::StringBuilder() = default;
	
	StringBuilder::~StringBuilder()	= default;
	
	std::vector<std::string> StringBuilder::Split(std::string str, std::string pattern)
	{
		std::string::size_type pos;
		std::vector<std::string> result;
		str += pattern;//扩展字符串以方便操作
		size_t size = str.size();
		
		for (size_t i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				result.push_back(s);
				i = (int)(pos + pattern.size()) - 1;
			}
		}
		return result;
	}
	
	std::string StringBuilder::Format(const char* format, ...)
	{
#define MAX_STRING_LENGTH (1024*100)
		
		std::string ret;
		
		va_list ap;
		va_start(ap, format);
		
		char* buf = (char*)malloc(MAX_STRING_LENGTH);
		if (buf != nullptr)
		{
			vsnprintf(buf, MAX_STRING_LENGTH, format, ap);
			ret = buf;
			free(buf);
		}
		va_end(ap);
		
		return ret;
	}
	
	std::string StringBuilder::Trim(std::string & str)
	{
		if (str.empty())
		{
			return str;
		}
		size_t n = str.find_last_not_of( " \r\n\t" );
		if( n != string::npos )
		{
			str.erase( n + 1 , str.size() - n );
		}
  
		n = str.find_first_not_of ( " \r\n\t" );
		if( n != string::npos )
		{
			str.erase( 0 , n );
		}
		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" ") + 1);
		return str;
	}

}

int Convert::ToInt(std::string source)
{
	return atoi(source.c_str());
}

int Convert::ToInt(const char * source)
{
	return atoi(source);
}

int Convert::ToInt(const char source)
{
	return atoi(&source);
}

int Convert::ToInt(double source)
{
	return (int)source;
}

int Convert::ToInt(float source)
{
	return (int)source;
}

float Convert::ToFloat(std::string source)
{
	return atof(source.c_str());
}

float Convert::ToFloat(const char * source)
{
	return atof(source);
}

float Convert::ToFloat(int source)
{
	return (float)source;
}

double Convert::ToDouble(std::string source)
{
	return strtod(source.c_str(), nullptr);
}

double Convert::ToDouble(const char * source)
{
	return strtod(source, nullptr);
}

std::string Convert::ToString(double source)
{
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%f", source);
	return std::string(buffer);
}

std::string Convert::ToString(int source)
{
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d", source);
	return std::string(buffer);
}

std::string Convert::ToString(object source)
{
	std::string ret = object_cast<std::string>(source);
	return ret;
}


std::string Convert::ToString(MonoString* str)
{
	int length = mono_string_length(str);
	wchar_t * chars = (wchar_t *)mono_string_chars(str);

	std::wstring wStr(chars);
	std::string stdStr;
	stdStr.resize(wStr.length());
	std::copy(wStr.begin(), wStr.end(), stdStr.begin());
	return stdStr;
}

long Convert::_16To10(std::string str)
{
	return strtoul(str.c_str(), nullptr, 16);
}

long Convert::_16To10(const char* str)
{
	return strtoul(str, nullptr, 16);
}

bool Convert::IsBig_Endian()
{
	union myUnion
	{
		int  a;
		char b;
		int  c;
	};
	union myUnion t;
	t.a = 0x12345678;//union用法：此时
	if (t.c == 0x78)
	{
		return true;
	}
	return false;
}

vvision::vec4f Convert::ToColorRGBA(long color)
{
	UINT a = 0;
	UINT b = 0;
	UINT g = 0;
	UINT r = 0;
	vec4f v4Color;
	a = 0xff;
	b = 0xff00;
	g = 0xff0000;
	r = 0xff000000;
	v4Color.r = ((color & r) >> 24) / 255.0f;
	v4Color.g = ((color & g) >> 16) / 255.0f;
	v4Color.b = ((color & b) >> 8) / 255.0f;
	v4Color.a = (color & a) / 255.0f;
	return v4Color;
}

vvision::vec4f Convert::ToColorRGBA(std::string colorStr)
{
	long color = _16To10(colorStr);
	return ToColorRGBA(color);
}

vvision::vec4f Convert::ToVec4Color(aiColor4D color)
{
	return vec4f(color.r, color.g, color.b, color.a);
}

vvision::vec4f Convert::ToVec4Color(aiColor3D color)
{
	return vec4f(color.r, color.g, color.b, 1);
}

object::object() : content(nullptr)
{

}

object::object(const object & other) : content(other.content ? other.content->clone() : nullptr)
{

}

object::~object()
{
	delete content;
}

object & object::swap(object & rhs)
{
	std::swap(content, rhs.content);
	return *this;
}

bool object::empty() const
{
	return !content;
}

const std::type_info & object::type() const
{
	return content ? content->type() : typeid(void);
}

object & object::operator=(object rhs)
{
	rhs.swap(*this);
	return *this;
}

const char * bad_object_cast::what() const throw()
{
	return "E3DEngine::bad_object_cast: "
		"failed conversion using E3DEngine::object_cast";
}
