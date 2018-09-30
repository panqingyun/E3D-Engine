
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-1  PanQingyun. All rights reserved. *************************//

#include <stdio.h>
#include "E3DGameObject.h"
#include "../Source/EngineDelegate.h"
#include "E3DTransform.hpp"
#include <stdarg.h>
#include "E3DRenderObject.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "../Physics/E3DCollider.hpp"

namespace E3DEngine
{
	
	void GameObject::SetActive(bool isActive)
	{
		if (isActive == IsActive)
		{
			return;
		}
		IsActive = isActive;
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->SetActive(isActive);
		}
		if (ActiveChangeEvent.empty() == false)
		{
			ActiveChangeEvent(this,nullptr);
		}
		for (auto & m_listComponent : m_listComponents)
		{
			for (auto & itr : m_listComponent.second)
			{
				if (isActive)
				{
					itr->OnEnable();
				}
				else
				{
					itr->OnDisable();
				}
			}
		}
		for(auto & Child : childNode)
		{
			if(Child.second != nullptr)
			{
				Child.second->SetActive(isActive);
			}
		}
	}
	
	std::vector<Component*> * GameObject::GetComponents(std::string type_name)
	{
		return &m_listComponents[type_name];
	}


	std::map<std::string, std::vector<Component*>> & GameObject::GetAllComponents()
	{
		return m_listComponents;
	}

	vvision::vec3f GameObject::GetBounds()
	{
		return size;
	}

	Component * GameObject::AddComponent(const char * type_name)
	{
		std::string className = "";
		std::string nameSpaceName = "";
		std::string full_name = std::string(type_name);
		int dotPos = full_name.find_last_of(".");

		Component * component = nullptr;
		if (dotPos == std::string::npos)
		{
			className = type_name;
		}
		else
		{
			className = full_name.substr(dotPos + 1);
			nameSpaceName = full_name.substr(0, dotPos);
		}
		// namespace == E3DEngine 是引擎类 否则不是

		if (nameSpaceName == E3D_NAME_SPACE)
		{
			string kName = ClassFactory::GetInstance().getTypeNameByClassName(className);
			if (kName != "NAN")
			{
				component = (Component *)ClassFactory::GetInstance().CreateClass(kName);
				if (component == nullptr)
				{
					return nullptr;
				}
				component->SetGameObject(this);
				component->mTypeName = type_name;
				component->Transform = Transform;
				m_listComponents[type_name].push_back((Component*)component);
			}
		}		
		else
		{
			// 不是引擎类
			component = new Component;
			component->mTypeName = full_name;
			component->mBehaviour->SetImage(MonoScriptManager::GetInstance().GetCodeImage());
			component->mBehaviour->Create(nameSpaceName.c_str(), className.c_str());
			AddComponent(component);
		}
		
		return component;
	}
	
	Component * GameObject::AddComponent(E3DEngine::Component *component)
	{
		if (component == nullptr)
		{
			return nullptr;
		}
		component->SetGameObject(this);
		component->Transform = Transform;
		m_listComponents[(component)->mTypeName].push_back(component);
		return component;
	}
	
	E3DEngine::Component * GameObject::GetComponent(const char * type_name)
	{
		if (m_listComponents.find(type_name) != m_listComponents.end())
		{
			return m_listComponents[type_name][0];
		}
		return nullptr;
	}

	void GameObject::RemoveComponent(Component *com)
	{
		std::string type_name = com->mTypeName;
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
		for (auto & m_listComponent : m_listComponents)
		{
			for (auto & itr : m_listComponent.second)
			{
				itr->LateUpdate(deltaTime);
			}
		}
		for (auto &node : childNode)
		{
			if (!node.second->IsActive)
			{
				continue;
			}
			node.second->AfterUpdate(deltaTime);
		}
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
					if (itr->mNotStart)
					{
						itr->Start();
						itr->mNotStart = false;
					}
					itr->Update(deltaTime);
				}
			}
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
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->RemoveInRenderer(ID);
		}
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


	E3DEngine::GameObject * GameObject::FindChild(UINT id)
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
			if (child.second->mName == name)
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
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->SetLayerMask(layerMask);
		}
		mBehaviour->SetFieldValue("layerMask", &m_layerMask);
	}

	GameObject::GameObject()
	{
		mTypeName = TP_Empty;
		Transform = new CTransform;
		Transform->gameObject = this;
		mTypeName = typeid(this).name();
		IsEmptyObject = true;
		DontDestoryOnLoad = false;
		mType = eT_GameObject;
		pCamera = nullptr;
		IsActive = true;
		m_pRenderer = nullptr;
		ParentNode = nullptr;
		m_layerMask = -1;
		m_bIsStatic = false;
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

	bool GameObject::IsRenderObject(GameObject * go)
	{
		if (go->GetRenderer() != nullptr)
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
			if (mType != eT_Scene)
			{
				if (mType == eT_Camera)
				{
					SceneManager::GetCurrentScene()->AddCamera(static_cast<Camera*>(node));
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
		node->ParentNode = nullptr;
		//SAFE_DELETE(node);
	}


	void GameObject::RemoveChild(UINT ID)
	{
		Transform->RemoveChild(ID);
		if (childNode.find(ID) == childNode.end())
		{
			return;
		}
		
		childNode[ID]->ParentNode = nullptr;
		childNode.erase(childNode.find(ID));
		//SAFE_DELETE(childNode[ID]);
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


	E3DEngine::Collider * GameObject::GetCollider()
	{
		return mCollider;
	}

	void GameObject::SetCollider(Collider * collider)
	{
		mCollider = collider;
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
		if (m_pRenderer!= nullptr)
		{
			m_pRenderer->SetRenderIndex(index);
		}
	}

	void GameObject::RemoveComponent(UINT id)
	{
		for (auto &comList : m_listComponents)
		{
			if (removeComponentFromListByID(comList.second, id))
			{
				break;
			}
		}
	}

	bool GameObject::removeComponentFromListByID(std::vector<Component*> &comList, UINT id)
	{
		bool isRemove = false;
		for (std::vector<Component*>::iterator itr = comList.begin();
			itr != comList.end() ;++itr)
		{
			if ((*itr)->ID == id)
			{
				comList.erase(itr);
				isRemove = true;
				break;
			}
		}
		return isRemove;
	}

	E3DEngine::RenderObject * GameObject::GetRenderer()
	{
		return m_pRenderer;
	}


	void GameObject::SetRenderer(Renderer * renderer)
	{
		m_pRenderer = renderer;
		m_pRenderer->SetTransform(Transform);
		m_pRenderer->SetLayerMask(m_layerMask);
		TransferRender();
		SetActive(true);
	}


	std::map<UINT, GameObject *> & GameObject::GetChilds()
	{
		return childNode;
	}


	std::vector<Vertex>& GameObject::GetVertex()
	{
		return m_vecVertex;
	}


	std::vector<uint>& GameObject::GetIndex()
	{
		return m_vecIndex;
	}

	void GameObject::ComponentAdded(Component * component)
	{

	}

	void GameObject::TransferRender()
	{
		TRANSFER_FIELD_OBJECT(m_pRenderer);
	}

	void GameObject::CreateBehaviour()
	{
		mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(GameObject);
		setBehaviourDefaultValue();
	}


	void GameObject::Destory(GameObject *go)
	{
		SceneManager::GetCurrentScene()->RemoveObject(go);
		SAFE_DELETE(go);
	}


	E3DEngine::CTransform * GameObject::GetTransform()
	{
		return Transform;
	}

	void GameObject::SetIsStatic(bool isStatic)
	{
		// TODO
		if (isStatic == m_bIsStatic)
		{
			return;
		}
		m_bIsStatic = isStatic;
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->IsStaticDraw = !isStatic;
			if(!isStatic)
				m_pRenderer->SetTransform(Transform);
		}
		Transform->SetNeedUpdate(!isStatic);
		Transform->WorldMatrix.identity();
	}



	bool GameObject::GetIsStatic()
	{
		return m_bIsStatic;
	}

	void GameObject::setBehaviourDefaultValue()
	{
		Object::setBehaviourDefaultValue();
		TRANSFER_FIELD_OBJECT(Transform);
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


	bool StringBuilder::IsText(std::string &cStrName)
	{
		const char *str = cStrName.c_str();
		char ch = *str++;
		int i = 1;
		if (!(ch == '_' || ((ch & 0x80) && (*str & 0x80)) || isalpha(ch)))
		{
			return false;
		}
		if ((ch & 0xff) == 0xA1 && (*str & 0x80) >= 0x3F)
		{
			return false;
		}
		else if ((ch & 0xff) > 0xA1 && (ch & 0xff) < 0xAA)
		{
			return false;
		}
		else if ((ch & 0xff) == 0xAA && (*str & 0x80) <= 0x40)
		{
			return false;
		}
		if (ch < 0)
		{
			*str++;
			i++;
		}
		int len = (int)strlen(str);
		for (i; i < len; i++)
		{
			ch = *str++;
			if (!(ch == '_' || ch == '-' || (ch & 0x80) || isalpha(ch) || isdigit(ch)))
			{
				return false;
			}
			if (i < len - 1)
			{
				if ((ch & 0xff) == 0xA1 && (*str & 0x80) >= 0x3F)
				{
					return false;
				}
				else if ((ch & 0xff) > 0xA1 && (ch & 0xff) < 0xAA)
				{
					return false;
				}
				else if ((ch & 0xff) == 0xAA && (*str & 0x80) <= 0x40)
				{
					return false;
				}
			}
			if (ch < 0)
			{
				*str++;
				i++;
			}
		}
		return true;
	}

	void StringBuilder::Replace(std::string & str, std::string src, std::string dest)
	{
		size_t pos = str.find(src);
		if (pos != std::string::npos)
		{
			size_t length = src.length();
			str.replace(pos, length, dest);
		}
	}

	void StringBuilder::ReplaceAll(std::string & str, std::string src, std::string dest)
	{
		size_t pos = str.find(src);
		if (pos != std::string::npos)
		{
			size_t length = src.length();
			str = str.replace(pos, length, dest);
			ReplaceAll(str, src, dest);
		}
	}

	bool StringBuilder::IsNumber(std::string str)
	{
		std::stringstream sin(str);
		double d;
		char c;
		if (!(sin >> d))
		{
			return false;
		}
		if (sin >> c)
		{
			return false;
		}
		return true;
	}

	std::string StringBuilder::RemoveTab(std::string & str)
	{
		if (str.empty())
		{
			return str;
		}
		size_t n = str.find_last_not_of(" \r\n\t");
		if (n != std::string::npos)
		{
			str.erase(n + 1, str.size() - n);
		}

		n = str.find_first_not_of(" \r\n\t");
		if (n != std::string::npos)
		{
			str.erase(0, n);
		}
		return str;
	}

	std::string StringBuilder::RemoveLastStr(std::string & str, std::string removeStr)
	{
		if (str.empty())
		{
			return str;
		}
		size_t n = str.find_last_not_of(removeStr);
		if (n != std::string::npos)
		{
			str.erase(n + 1, str.size() - n);
		}
		return str;
	}

	std::string StringBuilder::RemoveFirstStr(std::string & str, std::string removeStr)
	{
		if (str.empty())
		{
			return str;
		}
		size_t pos = str.find(removeStr);
		if (pos != std::string::npos)
		{
			size_t length = removeStr.length();
			std::string::iterator begin = str.begin() + pos;
			std::string::iterator end = str.begin() + pos + length;
			str.erase(begin, end);
		}
		return str;
	}
}

int Convert::ToInt(std::string source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		assert(false);
	}
	source = StringBuilder::Trim(source);
	return atoi(source.c_str());
}

int Convert::ToInt(const char * source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		assert(false);
	}
	return atoi(source);
}

int Convert::ToInt(const char source)
{
	if (!StringBuilder::IsNumber(&source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		assert(false);
	}
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
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		assert(false);
	}
	return atof(source.c_str());
}

float Convert::ToFloat(const char * source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		assert(false);
	}
	return atof(source);
}

float Convert::ToFloat(int source)
{
	return (float)source;
}

double Convert::ToDouble(std::string source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		assert(false);
	}
	return strtod(source.c_str(), nullptr);
}

double Convert::ToDouble(const char * source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		assert(false);
	}
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


std::string Convert::ToString(bool source)
{
	if (source)
	{
		return "true";
	}
	return "false";
}


std::string Convert::ToString(vec3f source)
{
	std::string &str1 = ToString(source.x);
	std::string &str2 = ToString(source.y);
	std::string &str3 = ToString(source.z);

	return str1 + "," + str2 + "," + str3;
}


std::string Convert::ToString(vec4f source)
{
	std::string &str1 = ToString(source.x);
	std::string &str2 = ToString(source.y);
	std::string &str3 = ToString(source.z);
	std::string &str4 = ToString(source.w);

	return str1 + "," + str2 + "," + str3 + "," + str4;
}

std::string Convert::ToStdString(MonoString* str)
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

MonoObject * Convert::ToCSVector4(vec4f vec)
{
	MonoClass * klass = mono_class_from_name(MonoScriptManager::GetInstance().GetEngineImage(), NAME_SPACE, "Vector4");
	MonoObject * ret = mono_object_new(MonoScriptManager::GetInstance().GetEngineDomain(), klass);

	MonoClassField * fieldX = mono_class_get_field_from_name(klass, "x");
	MonoClassField * fieldY = mono_class_get_field_from_name(klass, "y");
	MonoClassField * fieldZ = mono_class_get_field_from_name(klass, "z");
	MonoClassField * fieldW = mono_class_get_field_from_name(klass, "w");
	mono_field_set_value(ret, fieldX, &vec.x);
	mono_field_set_value(ret, fieldY, &vec.y);
	mono_field_set_value(ret, fieldZ, &vec.z);
	mono_field_set_value(ret, fieldZ, &vec.w);

	return ret;
}

MonoObject * Convert::ToCSVector3(vec3f vec)
{
	MonoClass * klass = mono_class_from_name(MonoScriptManager::GetInstance().GetEngineImage(), NAME_SPACE, "Vector3");
	MonoObject * ret = mono_object_new(MonoScriptManager::GetInstance().GetEngineDomain(), klass);

	MonoClassField * fieldX = mono_class_get_field_from_name(klass, "x");
	MonoClassField * fieldY = mono_class_get_field_from_name(klass, "y");
	MonoClassField * fieldZ = mono_class_get_field_from_name(klass, "z");
	mono_field_set_value(ret, fieldX, &vec.x);
	mono_field_set_value(ret, fieldY, &vec.y);
	mono_field_set_value(ret, fieldZ, &vec.z);

	return ret;
}

vec4f Convert::CSVector4ToVec4(MonoObject * vec)
{
	MonoClass * klass = mono_object_get_class(vec);
	vec4f _vec4;

	MonoClassField * fieldX = mono_class_get_field_from_name(klass, "x");
	MonoClassField * fieldY = mono_class_get_field_from_name(klass, "y");
	MonoClassField * fieldZ = mono_class_get_field_from_name(klass, "z");
	MonoClassField * fieldW = mono_class_get_field_from_name(klass, "w");
	mono_field_get_value(vec, fieldX, &_vec4.x);
	mono_field_get_value(vec, fieldY, &_vec4.y);
	mono_field_get_value(vec, fieldZ, &_vec4.z);
	mono_field_get_value(vec, fieldW, &_vec4.w);

	return _vec4;
}


bool Convert::ToBoolean(std::string src)
{
	if (src.empty())
	{
		return false;
	}
	if (strcmp(src.c_str(), "true") == 0 || strcmp(src.c_str(), "TRUE") == 0)
	{
		return true;
	}
	else if (strcmp(src.c_str(), "false") == 0 || strcmp(src.c_str(), "FALSE") == 0)
	{
		return false;
	}

	return false;
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
