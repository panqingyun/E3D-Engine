//
//  Interface.h
//
//  Created by 潘庆云 on 2017/1/22.
//

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "../Utils/E3DUtil.hpp"
#include "E3DAutoreleasePool.h"
#include <typeinfo>
namespace E3DEngine
{
	Interface IObject
	{

	};

	struct EventArgs
	{
		void * _data;
		double lParam;
		double rParam;
		bool  _handled;
	};

	Interface IActor : public IObject
	{
		virtual void EffectFrameChange(IObject * sender, EventArgs * e) = 0;
		virtual void EffectEnd(IObject * sender, EventArgs * e) = 0;
		virtual void PlayDurationEnd(IObject * sender, EventArgs * e) = 0;
	};


	class Ref : public IObject
	{
	public:
		Ref()
		{
			_referenceConut = 1;
			isAutoRelease = false;
		}
		virtual ~Ref() = default;
	public:
		Ref * get_ptr()
		{
			add_reference();
			return this;
		}
		void release()
		{
			_referenceConut == 0 ? _referenceConut : _referenceConut --;
			if (_referenceConut == 0 && isAutoRelease)
			{
				// 触发删除, 下一帧会delete
				AutoreleasePool::GetInstance().AddDeletePointer(this);
			}
		}

	public:
		unsigned int getReferenceCount() const
		{
			return _referenceConut;
		}

		void add_reference()
		{
			_referenceConut++;
		}

		void autoRelease()
		{
			isAutoRelease = true;
		}

	protected:
		unsigned int _referenceConut;
		bool isAutoRelease;
	};

	template<typename T> class share_pointer
	{
	public:
		share_pointer()
		{
			ptr = nullptr;
		}

		share_pointer(const share_pointer<T> &other)
		{
			*this = other;
		}

		share_pointer(T * _t)
		{
			create_share(_t);
		}
		
		~share_pointer()
		{
			release();
			ptr = nullptr;
		}

		share_pointer & operator = (const share_pointer<T> &other)
		{
			ptr = other.ptr;
			add_reference();
			return *this;
		}

		bool operator == (const share_pointer<T> &other)
		{
			return ptr == other.ptr;
		}

		bool operator != (const share_pointer<T> &other)
		{
			return ptr != other.ptr;
		}
	public:
		static share_pointer null()
		{
			static share_pointer _sh_ins;
			return _sh_ins;
		}

		static T * create_pointer(T * _t)
		{
			if (_t == nullptr)
			{
				return nullptr;
			}			
			return (T*)(((Ref*)_t)->get_ptr());;
		}
	public:
		T * create_share(T * _t)
		{
			if (_t == nullptr)
			{
				return nullptr;
			}
			ptr = (T*)(((Ref*)_t)->get_ptr());
			return ptr;
		}

		unsigned int getReferenceCount() const
		{
			if (ptr == nullptr)
			{
				return 0;
			}
			return ptr->getReferenceCount();
		}

		void release()
		{
			if (ptr == nullptr)
			{
				return;
			}
			if (ptr->getReferenceCount() == 0)
			{
				return;
			}
			ptr->release();
		}

		T * get_ptr()
		{
			return ptr;
		}
	protected:
		void add_reference()
		{
			if (ptr == nullptr)
			{
				return;
			}
			((Ref*)ptr)->add_reference();
		}
	private:
		T * ptr;
	};

	Interface IFactory : public Ref
    {
        virtual void Initilize()         = 0;
        virtual void Destory()           = 0;
    };

	Interface ISystem : public Ref
    {
        virtual void Update(float deltaTime)    = 0;
        virtual void Initilize()                = 0;
        virtual void Destory()                  = 0;
        virtual std::string  GetName()          = 0;
    };

	Interface IComponent : public Ref
    {
		virtual ~IComponent() override = default;
		virtual void Init(const char * monoName) {}
		virtual void Awake()					= 0;
        virtual void Update(float deltaTime)    = 0;
        virtual void Start()                    = 0;
        virtual void Destory()                  = 0;
    };
    
	Interface IManager : public Ref
	{
		virtual void Cleanup() = 0;
	};
}

#endif /* IFactory_h */
