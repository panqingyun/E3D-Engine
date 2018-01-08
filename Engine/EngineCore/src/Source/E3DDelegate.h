#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include "../Source/Interface.h"

namespace E3DEngine
{
	using EventFunc = void   (E3DEngine::IObject::*)(E3DEngine::IObject * _sender, E3DEngine::EventArgs *e);
#define  EventDelegateFunc(classAndFunc) reinterpret_cast<EventFunc>(&classAndFunc)
	namespace Event
	{
		template<typename ...ParamType> class IDelegate : public IObject
		{
		public:
			IDelegate() = default;
			virtual ~IDelegate() = default;
			virtual bool isType(const std::type_info& _type) = 0;
			virtual void invoke(ParamType ... params) = 0;
			virtual bool compare(IDelegate<ParamType...> *_delegate) const = 0;
			virtual void Cleanup() { }
		};

		template<typename T,  typename ...ParamType> class Delegate 
			: public IDelegate<ParamType...>
		{
		public:
			using Method = void(T::*)(ParamType...);

			Delegate(T * _object, Method _method) : mObject(_object), mMethod(_method) { }

			virtual bool isType(const std::type_info& _type) 
			{ 
				return typeid(Delegate<T, ParamType...>) == _type; 
			}

			virtual void invoke(ParamType...params)
			{
				(mObject->*mMethod)(params...);
			}

			virtual bool compare(IDelegate<ParamType...> *_delegate) const
			{
				if (0 == _delegate || !_delegate->isType(typeid(Delegate<ParamType...>)))
				{
					return false;
				}
				Delegate<ParamType...>* cast = static_cast<Delegate<ParamType...>*>(_delegate);
				return cast->mObject == mObject && cast->mMethod == mMethod;
			}
			void operator ()(ParamType ... params)
			{
				invoke(params...);
			}
			Delegate() = default;
			virtual ~Delegate() = default;
		private:
			T * mObject;
			Method mMethod;
		};

		template<typename T,typename ...ParamType> class Delegate<T, void(T:: *)(ParamType...)> 
			: public IDelegate<ParamType...>
		{
		public:
			using Method = void(T::*)(ParamType...);

			Delegate(T * _object, Method _method) : mObject(_object), mMethod(_method) { }
			virtual bool isType(const std::type_info& _type)
			{ 
				return typeid(Delegate<T, void(T:: *)(ParamType...)>) == _type; 
			}

			virtual void invoke(ParamType...params)
			{
				(mObject->*mMethod)(params...);
			}

			void operator()(ParamType... params)
			{
				invoke(params...);
			}

			virtual bool compare(IDelegate<ParamType...> *_delegate) const
			{
				if (0 == _delegate || !_delegate->isType(typeid(Delegate<T, void(T:: *)(ParamType...)>)))
				{
					return false;
				}
				Delegate<T, void(T:: *)(ParamType...)>* cast = static_cast<Delegate<T, void(T:: *)(ParamType...)>*>(_delegate);
				return cast->mObject == mObject && cast->mMethod == mMethod;
			}

			Delegate() = default;
			virtual ~Delegate() = default;
		private:
			T * mObject;
			Method mMethod;
		};

		template<typename ...ParamType> class Delegates : public IObject
		{
		public:
			using ListDelegate = std::list<IDelegate<ParamType...>*>;
			using ListDelegateIterator = typename ListDelegate::iterator;
			using ConstListDelegateIterator = typename ListDelegate::const_iterator;

			Delegates() = default;
			~Delegates() 
			{ 
				Cleanup(); 
			}

			bool empty() const
			{
				for (ConstListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if (*iter)
					{
						return false;
					}
				}
				return true;
			}

			void Cleanup()
			{
				for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if (*iter)
					{
						SAFE_DELETE(*iter);
					}
				}
			}


			Delegates<ParamType...>& operator+=(IDelegate<ParamType...>* _delegate)
			{
				for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if ((*iter) && (*iter)->compare(_delegate))
					{
						SAFE_DELETE(_delegate);
						return *this;
					}
				}
				mListDelegates.push_back(_delegate);
				return *this;
			}

			Delegates<ParamType...>& operator-=(IDelegate<ParamType...>* _delegate)
			{
				for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if ((*iter) && (*iter)->compare(_delegate))
					{
						if ((*iter) != _delegate) delete (*iter);
						(*iter) = 0;
						break;
					}
				}
				delete _delegate;
				return *this;
			}

			void operator()(ParamType... params)
			{
				ListDelegateIterator iter = mListDelegates.begin();
				//std::vector<void> _Results;
				while (iter != mListDelegates.end())
				{
					if (0 == (*iter))
					{
						iter = mListDelegates.erase(iter);
					}
					else
					{
						//_Results.push_back((*iter)->invoke(params...));
						++iter;
					}
				}
				//return _Results;
			}
		private:
			Delegates<ParamType...>(const Delegates& _event);
			Delegates<ParamType...>& operator=(const Delegates& _event);

		private:
			ListDelegate mListDelegates;
		};

		template< typename ...ParamType> class Delegates<ParamType...> : public IObject
		{
		public:
			using ListDelegate = std::list<IDelegate<ParamType...>*>;
			using ListDelegateIterator = typename ListDelegate::iterator;
			using ConstListDelegateIterator = typename ListDelegate::const_iterator;

			Delegates() = default;
			~Delegates() 
			{ 
				Cleanup(); 
			}

			bool empty() const
			{
				for (ConstListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if (*iter)
					{
						return false;
					}
				}
				return true;
			}

			virtual void Cleanup()
			{
				for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if (*iter)
					{
						SAFE_DELETE(*iter);
					}
				}
				mListDelegates.clear();
			}

			Delegates<ParamType...>& operator += (IDelegate<ParamType...>* _delegate)
			{
				for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if ((*iter) && (*iter)->compare(_delegate))
					{
						SAFE_DELETE(_delegate);
						return *this;
					}
				}
				mListDelegates.push_back(_delegate);
				return *this;
			}

			Delegates<ParamType...>& operator-=(IDelegate<ParamType...>* _delegate)
			{
				for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
				{
					if ((*iter) && (*iter)->compare(_delegate))
					{
						if ((*iter) != _delegate) delete (*iter);
						(*iter) = nullptr;
						mListDelegates.erase(iter);
						break;
					}
				}
				SAFE_DELETE(_delegate);
				return *this;
			}

			void operator()(ParamType... params)
			{
				ListDelegate tempList;
				std::copy(mListDelegates.begin(), mListDelegates.end(), std::back_inserter(tempList));
				ListDelegateIterator iter = tempList.begin();
				for (; iter != tempList.end(); ++ iter)
				{	
					if ((*iter) != nullptr)
					{
						(*iter)->invoke(params...);
					}
				}
			}
		private:
			Delegates<ParamType...>(const Delegates& _event);
			Delegates<ParamType...>& operator=(const Delegates& _event);

		private:
			ListDelegate mListDelegates;
		};


		using EventDelegates = Delegates<IObject*, EventArgs*>;
		using EventDelegate = Delegates<IObject*>;

	}

	template<typename F, typename T> Event::Delegate<T, F>* EventHandler(F func, T * _object)
	{
		return new Event::Delegate<T, F>(_object, func);
	}
	
	
#define  event Event::
}
using EventHandleFunction = E3DEngine::Event::IDelegate<E3DEngine::IObject*,  E3DEngine::EventArgs*>;

#define NewFunctionHandler(delegate, obj)\
		dynamic_cast<E3DEngine::Event::IDelegate<E3DEngine::IObject*, E3DEngine::EventArgs*>*>(E3DEngine::EventHandler(delegate, obj))



#endif
