//
//  Object.h
//
//  Created by 潘庆云 on 2017/1/26.
//

#ifndef IObject_h
#define IObject_h
#include "E3DObject.h"

#include <algorithm>
#include <typeinfo>
#include "E3DComponent.hpp"
#include "../Source/E3DDelegate.h"
#include "../Source/E3DVertex.h"
#include "../Source/vmath.h"
using namespace vvision;


#ifndef _TT_REMOVE_REFERENCE_H_
#define _TT_REMOVE_REFERENCE_H_

namespace E3DEngine
{
#define ENGINE_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) /**/
#define ENGINE_MPL_AUX_LAMBDA_SUPPORT(i,name,params) /**/
#define ENGINE_TT_AUX_TEMPLATE_ARITY_SPEC(i, name) /**/
#define ENGINE_TT_AUX_TYPE_TRAIT_DEF1(trait,T,result) \
template< typename T > struct trait \
{ \
	typedef result type; \
	ENGINE_MPL_AUX_LAMBDA_SUPPORT(1, trait, (T)) \
}; \
\
ENGINE_TT_AUX_TEMPLATE_ARITY_SPEC(1, trait) \
/**/
    
#define ENGINE_TT_AUX_TYPE_TRAIT_PARTIAL_SPEC1_1(param,trait,spec,result) \
template< param > struct trait<spec> \
{ \
	typedef result type; \
}; \
/**/

    template <class T>
    struct remove_rvalue_ref
    {
        using type = T;
    };
    template <class T>
    struct remove_rvalue_ref<T&&>
    {
        using type = T;
    };
    
    ENGINE_TT_AUX_TYPE_TRAIT_DEF1(remove_reference, T, typename remove_rvalue_ref<T>::type);
    ENGINE_TT_AUX_TYPE_TRAIT_PARTIAL_SPEC1_1(typename T, remove_reference, T&, T);
    
}
#endif

#if (defined(__GNUC__) && __GNUC__ >= 3) \
|| defined(_AIX) \
|| (defined(__sgi) && defined(__host_mips)) \
|| (defined(__hpux) && defined(__HP_aCC)) \
|| (defined(linux) && defined(__INTEL_COMPILER) && defined(__ICC))
#define ENGINE_AUX_object_TYPE_ID_NAME
#include <cstring>
#endif

class object
{
public: // structors
    
    object();
    
    template<typename ValueType>
    object(const ValueType & value)
    : content(new holder<ValueType>(value))
    {
    }
    
    object(const object & other);    
    ~object();
    
public: // modifiers
    
    object & swap(object & rhs);
    
    template<typename ValueType>
    object & operator=(const ValueType & rhs)
    {
        object(rhs).swap(*this);
        return *this;
    }
    
    object & operator=(object rhs);
    
public: // queries
    
    bool empty() const;
    
    const std::type_info & type() const;
    
private:
    
    class placeholder
    {
    public: // structors        
        virtual ~placeholder() = default;
        
    public: // queries        
        virtual const std::type_info & type() const = 0;        
        virtual placeholder * clone() const = 0;        
    };
    
    template<typename ValueType>
    class holder : public placeholder
    {
    public: // structors
        
        holder(const ValueType & value)
        : held(value)
        {
        }
        
    public: // queries
        
        virtual const std::type_info & type() const override
        {
            return typeid(ValueType);
        }
        
        virtual placeholder * clone() const override
        {
            return new holder(held);
        }
        
    public: // representation
        
        ValueType held;
        
    private: // intentionally left unimplemented
        holder & operator=(const holder &);
    };
    
private: // representation
    
    template<typename ValueType>
    friend ValueType * object_cast(object *);
    
    template<typename ValueType>
    friend ValueType * unsafe_object_cast(object *);
    
    placeholder * content;
    
};

class bad_object_cast : public std::bad_cast
{
public:
    virtual const char * what() const throw() override;
};

template<typename ValueType>
ValueType * object_cast(object * operand)
{
    return operand &&
    operand->type() == typeid(ValueType) ? &static_cast<object::holder<ValueType> *>(operand->content)->held : 0;
}

template<typename ValueType>
inline const ValueType * object_cast(const object * operand)
{
    return object_cast<ValueType>(const_cast<object *>(operand));
}

template<typename ValueType>
ValueType object_cast(object & operand)
{
    using nonref = typename  E3DEngine::remove_reference<ValueType>::type;
    
    nonref * result = object_cast<nonref>(&operand);
    /*if (!result)
     *      game::throw_exception(bad_object_cast());*/
    return *result;
}

template<typename ValueType>
inline ValueType object_cast(const object & operand)
{
    using nonref = typename  E3DEngine::remove_reference<ValueType>::type;
    
    return object_cast<const nonref &>(const_cast<object &>(operand));
}

template<typename ValueType>
inline ValueType * unsafe_object_cast(object * operand)
{
    return &static_cast<object::holder<ValueType> *>(operand->content)->held;
}

template<typename ValueType>
inline const ValueType * unsafe_object_cast(const object * operand)
{
    return unsafe_object_cast<ValueType>(const_cast<object *>(operand));
}

const static std::string stringType  = "string";
const static std::string intType     = "int";
const static std::string floatType   = "float";
const static std::string doubleType  = "double";

struct Convert
{
    static int ToInt(std::string source);
    static int ToInt(const char * source);
	static int ToInt(const char source);
    static int ToInt(double source);
    static int ToInt(float source);

    static float ToFloat(std::string source);
    static float ToFloat(const char * source);
    static float ToFloat(int source);

    static double ToDouble(std::string source);
    static double ToDouble(const char * source);

    static std::string ToString(double source);
	static std::string ToString(int source);
    static std::string ToString(object source);
	static std::string ToString(MonoString* str);

	/*
		把16进制的字符串转换成10进制数
	*/
    static long _16To10(std::string str);
    
	/*
		把16进制的字符串转换成10进制数
	*/
    static long _16To10(const char* str);

	static bool IsBig_Endian();

	static vec4f ToColorRGBA(long color);
	/*
		colorStr 如 ffabcdff
	*/
	static vec4f ToColorRGBA(std::string colorStr);
	static vec4f ToVec4Color(aiColor4D color);
	static vec4f ToVec4Color(aiColor3D color);
	
	template<typename T> static vec3<T> Vec4ToVec3(vec4<T> vec)
	{
		return vec3<T>(vec.x, vec.y, vec.z);
	}
	
	template<typename T> static vec4<T> Vec3ToVec4(vec3<T> vec)
	{
		return vec4<T>(vec.x, vec.y, vec.z, 1);
	}

	static MonoObject * ToCSVector4(vec4f vec);
	static MonoObject * ToCSVector3(vec3f vec);

	static vec4f CSVector4ToVec4(MonoObject *vec);


	static bool ToBoolean(std::string src);
};

namespace E3DEngine
{

	template<typename  T> std::string GetClassName()
	{
		return typeid(T).name();
	}

	class Camera;
	class CTransform;
	class Material;
	class RenderObject;
	class Renderer;
	class SkyBox;
	class GameObject : public Object
	{
	public:
		template<typename T> T * AddComponent()
		{
			std::string type_id = GetClassName<T>();
			T *_t = new T();
			((Component*)_t)->gameObject = this;
			((Component*)_t)->Awake();
			((Component*)_t)->Start();
			((Component*)_t)->TypeName = type_id;
			((Component*)_t)->Transform = Transform;
			((Component*)_t)->OnEnable();
			m_listComponents[type_id].push_back((Component*)_t);
			ComponentAdded((Component*)_t);
			return _t;
		}
		template<typename T> T * GetComponent()
		{
			std::string type_id = GetClassName<T>();
			if (m_listComponents.find(type_id) != m_listComponents.end())
			{
				return (T*)m_listComponents[type_id][0];
			}
			return nullptr;
		}

		template<typename T> std::vector<T*> * GetComponents()
		{
			std::vector<T*> * retVector = nullptr;
			std::string type_id = GetClassName<T>();
			if (m_listComponents.find(type_id) != m_listComponents.end())
			{
				retVector = new std::vector<T*>();
				retVector->resize(m_listComponents[type_id].size());
				for (int i = 0; i < retVector->size(); ++i)
				{
					(*retVector)[i] = (T*)m_listComponents[type_id][i];
				}
			}
			return retVector;
		}


		// 获取长宽高
		virtual vec3f GetBounds() { return size; }
		std::vector<Component*> * GetComponents(std::string type_name);
		Component * AddComponent(const char * type_name);
		Component * AddComponent(Component * component);
		void RemoveComponent(UINT id);
		void RemoveComponent(Component *com);
		void SetIsStatic(bool isStatic);
		bool GetIsStatic() { return m_bIsStatic; }
		virtual void SetMaterial(Material *material);
		virtual Material * GetMaterial();
	public:
		virtual void PrepareUpdate(float deltaTime);
		virtual void AfterUpdate(float deltaTime);
		virtual void Create(Object * parentNode = nullptr);
		virtual void Update(float deltaTime) override;
		GameObject();
		virtual ~GameObject() override;
		virtual void SetParent(GameObject * parent);

		virtual GameObject * FindChild(UINT id);
		virtual GameObject * FindChild(std::string name);

		DWORD GetLayerMask();
		virtual void SetLayerMask(DWORD layerMask);

		virtual void SetActive(bool isActive);
		virtual void SetCamera(Camera * camera);
		virtual void SetDontDestory(bool dontDestory);
		virtual void OnCollisionEnter(GameObject* other);
		virtual void TransformChange();
		static bool IsRenderObject(GameObject * node);
		virtual void AddChild(GameObject * node);
		virtual void RemoveChild(GameObject * node);
		virtual void RemoveChild(UINT ID);
		virtual void DestoryAllChild();

		virtual void Render(float deltaTime);
		void SetRenderIndex(DWORD index);
		RenderObject * GetRenderer();
		std::map<UINT, GameObject *> &GetChilds()
		{
			return childNode;
		}

		std::vector<Vertex>& GetVertex() { return m_vecVertex; };
		std::vector<uint>& GetIndex() { return m_vecIndex; }
	protected:
		virtual void ComponentAdded(Component * component);
		virtual void CreateBehaviour() override;
		virtual void setBehaviourDefaultValue();
		virtual bool removeComponentFromListByID(std::vector<Component*> &comList, UINT id);
	public:
		object			Tag;
		bool			IsActive;
		Camera *		pCamera;
		GameObject		*		ParentNode;
		event EventDelegates	ActiveChangeEvent;
		bool					IsEmptyObject;
		bool					DontDestoryOnLoad;
		CTransform	*			Transform;
		// 渲染层级
		DWORD					RenderIndex;
	protected:
		std::map<std::string, std::vector<Component*>> m_listComponents;
	protected:
		std::map<UINT, GameObject *> childNode;
		DWORD m_layerMask;
		Renderer * m_pRenderer;
		vec3f		size;
		std::vector<Vertex> m_vecVertex;
		std::vector<BatchVertex> m_vecBatchVertex;
		std::vector<uint> m_vecIndex;
		bool	m_bIsStatic;
	};

	
	class StringBuilder
	{
	public:
		StringBuilder();
		~StringBuilder();
		
		static std::vector<std::string> Split(std::string str, std::string pattern);
		static std::string Format(const char* format, ...);
		static std::string Trim(std::string & str);
		static bool IsText(std::string& str);
		static void Replace(std::string &str, std::string src, std::string dest);
		static void ReplaceAll(std::string &str, std::string src, std::string dest);
		static bool IsNumber(std::string str);
		static std::string RemoveTab(std::string &str);
		static std::string RemoveLastStr(std::string &str, std::string removeStr);
		static std::string RemoveFirstStr(std::string &str, std::string removeStr);
	private:
		
	};
}
#endif /* IObject_h */
