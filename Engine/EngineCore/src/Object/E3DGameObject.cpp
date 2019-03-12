
//********************************** Effective 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-1  PanQingyun. All rights reserved. *************************//

#include <stdio.h>
#include "E3DGameObject.h"
#include "../Source/EngineDelegate.h"
#include "E3DTransform.hpp"
#include <stdarg.h>
#include "E3DRenderObject.hpp"
#include "../RenderSystem/RenderObject/E3DRenderManager.hpp"
#include "../Physics/E3DCollider.hpp"
#include "../Source/E3DVertexManager.h"
#include "../Mesh/E3DMeshRender.h"
#include "../Component/E3DComponent.hpp"

namespace E3DEngine
{
	
	void GameObject::SetActive(bool isActive)
	{
		if (isActive == IsActive)
		{
			return;
		}
		IsActive = isActive;
		for (auto & component : m_listComponents)
		{			
			if (isActive)
			{
				component.second->OnEnable();
			}
			else
			{
				component.second->OnDisable();
			}
		}
		for(auto & Child : mChildGameObject)
		{
			if(Child != nullptr)
			{
				Child->SetActive(isActive);
			}
		}

		fillRender(isActive);
	}
	
	std::unordered_map<std::string, Component*> & GameObject::GetAllComponents()
	{
		return m_listComponents;
	}

	vvision::vec3f GameObject::GetBounds()
	{
		return size;
	}


	void GameObject::SetSize(float l, float h, float w)
	{
		size = vec3f(l, h, w);
	}

	Component * GameObject::AddComponent(std::string type_name)
	{
		std::string className = "";
		std::string nameSpaceName = "";
		std::string full_name = std::string(type_name);
		int dotPos = full_name.find_last_of('.');

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
				component->registProperty();
				if (component == nullptr)
				{
					return nullptr;
				}
				component->SetGameObject(this);
				component->mTypeName = type_name;
				component->Transform = Transform;
				m_listComponents[type_name] = component;
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
		component->mName = className;
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
		component->registProperty();
		m_listComponents[(component)->mTypeName] = component;
		return component;
	}
	
	E3DEngine::Component * GameObject::GetComponent(const char * type_name)
	{
		if (m_listComponents.find(type_name) != m_listComponents.end())
		{
			return m_listComponents[type_name];
		}
		return nullptr;
	}

	void GameObject::RemoveComponent(Component *com)
	{
		if (com == nullptr)
		{
			return;
		}
		std::string type_name = com->mTypeName;
		std::unordered_map<std::string, Component*>::iterator itr = m_listComponents.find(type_name);
		if (itr != m_listComponents.end())
		{
			m_listComponents.erase(itr);
		}
		SAFE_DELETE(com);
	}

	void GameObject::RemoveComponent(std::string fullName)
	{
		std::unordered_map<std::string, Component*>::iterator itr = m_listComponents.find(fullName);
		if (itr != m_listComponents.end())
		{
			m_listComponents.erase(itr);
		}
		SAFE_DELETE(itr->second);
	}

	void GameObject::PrepareUpdate(float deltaTime)
	{

	}

	void GameObject::AfterUpdate(float deltaTime)
	{
		for (auto & component : m_listComponents)
		{
			if (component.second->IsActive)
			{
				component.second->LateUpdate(deltaTime);
			}
		}
		for (auto &node : mChildGameObject)
		{
			if (!node->IsActive)
			{
				continue;
			}
			node->AfterUpdate(deltaTime);
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
			for (auto & component : m_listComponents)
			{
				if (!component.second->IsActive)
				{
					continue;
				}
				if (component.second->mNotStart)
				{
					component.second->Start();
					component.second->mNotStart = false;
				}
				component.second->Update(deltaTime);
			}
			for (auto &node : mChildGameObject)
			{
				if (!node->IsActive)
				{
					continue;
				}
				node->Update(deltaTime);
			}
		}
	}
	
	GameObject::~GameObject()
	{
		for (auto & component : m_listComponents)
		{
			component.second->Destory();
			SAFE_DELETE(component.second);
		}
		if (ParentNode != nullptr)
		{
			ParentNode->RemoveChild(ID);
			ParentNode->Transform->RemoveChild(ID);
		}
		int childSize = mChildGameObject.size();
		for (int i = 0; i < childSize; i++)
		{
			auto node = mChildGameObject.begin();
			mChildGameObject.erase(node);
			SAFE_DELETE(*node);
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
		GameObject * obj = nullptr;
		for (auto &gameObject : mChildGameObject)
		{
			if (gameObject->ID == id)
			{
				obj = gameObject;
				break;
			}
			else
			{
				obj = gameObject->FindChild(id);
				if (obj != nullptr)
				{
					break;
				}
			}
		}

		return obj;
	}


	E3DEngine::GameObject * GameObject::FindChild(std::string name)
	{
		GameObject * _child = nullptr;
		for (const auto &child : mChildGameObject)
		{
			if (child->mName == name)
			{
				_child = child;
				break;
			}
			else
			{
				_child = child->FindChild(name);
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
		if (mBehaviour != nullptr)
		{
			mBehaviour->SetFieldValue("layerMask", &m_layerMask);
		}
	}

	GameObject::GameObject()
	{
		Transform = new CTransform;
		Transform->gameObject = this;
		DontDestoryOnLoad = false;
		IsActive = false;
		m_pRenderer = nullptr;
		ParentNode = nullptr;
		m_layerMask = 0;
		m_bIsStatic = false;
		Flag = 0;
		TransChangeFun = nullptr;
		VertexBufferName = "";
		Color = Color4(1, 1, 1, 1);
	}
	
	void GameObject::SetDontDestory(bool dontDestory)
	{
		DontDestoryOnLoad = dontDestory;
	}

	void GameObject::OnCollisionEnter(GameObject * other)
	{
		for (std::unordered_map<std::string, Component*>::iterator it = m_listComponents.begin();
			it != m_listComponents.end(); it ++)
		{			
			it->second->OnCollisionEnter(other);
		}
	}


	void GameObject::TransformChange()
	{
		if (m_pRenderer != nullptr && !m_bIsStatic)
		{
			m_pRenderer->TransformChange();
		}
		if (TransChangeFun != nullptr)
		{
			TransChangeFun(ID);
		}
		for (auto &component : m_listComponents)
		{
			component.second->TransformChange();
		}
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
		if (FindChild(node->ID) == nullptr)
		{
			mChildGameObject.emplace_back(node);
			node->ParentNode = this;
			if (node->GetComponent(CAMERA_NAME))
			{
				SceneManager::GetCurrentScene()->AddCamera(static_cast<Camera*>(node->GetComponent(CAMERA_NAME)));
			}

		}
	}


	void GameObject::fillRender(bool isActive)
	{
		GetRenderSystem()->UseShareContext();
		if (m_pRenderer == nullptr)
		{
			return;
		}
		m_pRenderer->IsStaticDraw = m_bIsStatic;
		if (isActive)
		{
			if (m_pRenderer->GetRendererBuffer(ID) == nullptr)
			{
				fillVertextIndex();
			}
			if (!m_bIsStatic)
			{
				m_pRenderer->SetActive(true);
			}
		}
		else
		{
			m_pRenderer->RemoveInRenderer(ID);
		}
		m_pRenderer->TransformChange();
		GetRenderSystem()->UseRenderContext();
	}

	void GameObject::fillVertextIndex()
	{
		std::vector < Vertex > &vecVertex = VertexManager::GetVertex(VertexBufferName);
		std::vector < UINT > &vecIndex = VertexManager::GetIndex(VertexBufferName);
		m_pRenderer->FillBegin(ID);
		for (int i = 0; i < vecVertex.size(); i++)
		{
			Vertex ver = vecVertex[i];
			ver.SetColor(Color.r * m_pRenderer->GetMaterial()->mColor.r * vecVertex[i].Color[0],
				Color.g * m_pRenderer->GetMaterial()->mColor.g * vecVertex[i].Color[1],
				Color.b * m_pRenderer->GetMaterial()->mColor.b * vecVertex[i].Color[2],
				Color.a * m_pRenderer->GetMaterial()->mColor.a * vecVertex[i].Color[3]);
			if (m_bIsStatic)
			{
				vec4f pos = Transform->WorldMatrix * vec4f(vecVertex[i].Position[0], vecVertex[i].Position[1], vecVertex[i].Position[2], 1.0);
				ver.SetPosition(pos.x, pos.y, pos.z);
			}
			m_pRenderer->FillVertex(ver);
		}

		for (int i = 0; i < vecIndex.size(); i++)
		{
			m_pRenderer->FillIndex(vecIndex[i]);
		}

		m_pRenderer->FillEnd(ID, vecVertex.size(), vecIndex.size());

		if (m_bIsStatic)
		{
			m_pRenderer->CreateNewTransform();
		}
		else
		{
			m_pRenderer->SetTransform(Transform);
		}
	}

	void GameObject::RemoveChild(GameObject * node)
	{
		if (node == nullptr)
		{
			return;
		}

		Transform->RemoveChild(node->ID);
		
		for (std::list<GameObject*>::iterator it = mChildGameObject.begin(); it != mChildGameObject.end(); ++it)
		{
			if (*it == node)
			{
				mChildGameObject.erase(it);
				break;
			}
		}
		node->ParentNode = nullptr;
		//SAFE_DELETE(node);
	}


	void GameObject::RemoveChild(UINT ID)
	{
		Transform->RemoveChild(ID);

		for (std::list<GameObject*>::iterator it = mChildGameObject.begin(); it != mChildGameObject.end(); ++it)
		{
			if ((*it)->ID == ID)
			{
				(*it)->ParentNode = nullptr;
				mChildGameObject.erase(it);
				break;
			}
		}
		
		//SAFE_DELETE(childNode[ID]);
	}


	void GameObject::DestoryAllChild()
	{
		for (auto &node : mChildGameObject)
		{
			Transform->RemoveChild(node->ID);
			SAFE_DELETE(node);
		}

		mChildGameObject.clear();
	}


	E3DEngine::Collider * GameObject::GetCollider()
	{
		return m_pCollider;
	}

	void GameObject::SetCollider(Collider * collider)
	{
		m_pCollider = collider;
	}

	void GameObject::CreateComplete()
	{

	}

	void GameObject::SetRenderIndex(DWORD index)
	{
		if (m_pRenderer!= nullptr)
		{
			m_pRenderer->SetRenderIndex(index);
		}
	}

	E3DEngine::RenderObject * GameObject::GetRenderer()
	{
		return m_pRenderer;
	}


	void GameObject::SetRenderer(BatchRenderer * renderer)
	{
		m_pRenderer = renderer;
		m_pRenderer->SetLayerMask(m_layerMask);
		SceneManager::GetCurrentScene()->AddRenderObject(m_pRenderer->Get(), m_layerMask);		
		m_pRenderer->mName = mName;
		if (IsActive)
		{
			fillRender(true);
		}
	}


	std::list<GameObject *> & GameObject::GetChilds()
	{
		return mChildGameObject;
	}


	std::vector<Vertex>& GameObject::GetVertex()
	{
		return VertexManager::GetVertex(VertexBufferName);
	}


	std::vector<uint>& GameObject::GetIndex()
	{
		return VertexManager::GetIndex(VertexBufferName);
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
		TRANSFER_FIELD_OBJECT(Transform);
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


	void GameObject::SetColor(Color4 color)
	{
		Color = color;
#ifdef __E3D_EDITOR__
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->ChangeColor(color);
		}
#endif
	}


#ifdef __E3D_EDITOR__
	void GameObject::Selected(bool isSelect)
	{
		if (m_pRenderer != nullptr)
		{
			m_pRenderer->Get()->Selected(isSelect);
		}
	}
#endif

	void GameObject::SetIsStatic(bool isStatic)
	{
		m_bIsStatic = isStatic;
	}

	bool GameObject::GetIsStatic()
	{
		return m_bIsStatic;
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
		return 0;
	}
	source = StringBuilder::Trim(source);
	return atoi(source.c_str());
}

int Convert::ToInt(const char * source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		return 0;
	}
	return atoi(source);
}

int Convert::ToInt(const char source)
{
	if (!StringBuilder::IsNumber(&source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		return 0;
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
		return 0;
	}
	return atof(source.c_str());
}

float Convert::ToFloat(const char * source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		return 0;
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
		return 0;
	}
	return strtod(source.c_str(), nullptr);
}

double Convert::ToDouble(const char * source)
{
	if (!StringBuilder::IsNumber(source))
	{
		Debug::Log(ell_Error, "source string is not a number!");
		return 0;
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

string DecIntToHexStr(long long num)
{
	string str;
	long long Temp = num / 16;
	int left = num % 16;
	if (Temp > 0)
		str += DecIntToHexStr(Temp);
	if (left < 10)
		str += (left + '0');
	else
		str += ('A' + left - 10);
	return str;
}

std::string Convert::ToString(Color4 source)
{
	int r = source.r * 255;
	int g = source.g * 255;
	int b = source.b * 255;
	int a = source.a * 255;
	std::string str1 = DecIntToHexStr(r);
	std::string str2 = DecIntToHexStr(g);
	std::string str3 = DecIntToHexStr(b);
	std::string str4 = DecIntToHexStr(a);

	str1.length() == 1 ? str1 = "0" + str1 : str1;
	str2.length() == 1 ? str2 = "0" + str2 : str2;
	str3.length() == 1 ? str3 = "0" + str3 : str3;
	str4.length() == 1 ? str4 = "0" + str4 : str4;

	return str1 + str2 + str3 +  str4;
}

std::string Convert::ToString(vec4f source)
{
	std::string &&str1 = ToString(source.x);
	std::string &&str2 = ToString(source.y);
	std::string &&str3 = ToString(source.z);
	std::string &&str4 = ToString(source.w);

	return str1 + "," + str2 + "," + str3 + "," + str4;
}


std::string Convert::ToString(vec2f source)
{
	std::string &&str1 = ToString(source.x);
	std::string &&str2 = ToString(source.y);
	return str1 + "," + str2;
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

Color4 Convert::ToColor4(std::string colorStr)
{
	int t = colorStr.length();//得到字符串长度 
	long long answer = 0;
	for (int i = 0; i < t; i++)
	{
		if (colorStr[i] >= 'A' && colorStr[i] <= 'Z')
		{
			colorStr[i] = int(colorStr[i] - 'A') + 10 + '0';
		}
		answer += ((colorStr[i] - '0')*(pow(16, t - 1 - i)));
	}

	vec4f &&_v_color = ToColorRGBA(answer);
	return Color4(_v_color.r, _v_color.g, _v_color.b, _v_color.a);
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


vvision::vec3f Convert::ToVector3(std::string value)
{
	std::vector<std::string> vec = StringBuilder::Split(value, ",");
	if (vec.empty())
	{
		return vec3f(0, 0, 0);
	}
	float &&x = Convert::ToFloat(vec[0]);
	float &&y = Convert::ToFloat(vec[1]);
	float &&z = Convert::ToFloat(vec[2]);
	return vec3f(x, y, z);	
}


vvision::vec2f Convert::ToVector2(std::string value)
{
	std::vector<std::string> vec = StringBuilder::Split(value, ",");
	if (vec.empty())
	{
		return vec2f(0, 0);
	}
	float &&x = Convert::ToFloat(vec[0]);
	float &&y = Convert::ToFloat(vec[1]);
	return vec2f(x, y);
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
