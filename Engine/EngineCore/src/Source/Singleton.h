
#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdlib>

namespace E3DEngine
{
    
    /** \class Singleton
     * Template singleton class
     *
     * \author Abdallah DIB
     */
    template<class T>
    class  Singleton
    {
        public :
        
        /** return a unique instance
         */
        static T& Instance()
        {
            if(!m_instance)
                m_instance=new T;
            return *m_instance;
        }
        
        /** destory the unique instance
         */
        static void Destroy()
        {
            if(m_instance)
            {
                delete m_instance;
                m_instance=NULL;
            }
        }
    protected:
        
        /** the private constructor
         */
        Singleton() {}
        
        /** the private destructor
         */
        ~Singleton() {}
        
    private:
        
        /** the instance
         */
        static T* m_instance;
        
        /** no copy allowed
         */
        Singleton(const Singleton&);
        /** no copy allowed
         */
        void operator=(Singleton&);
        
    };
    
    /** the only instance
     */
    template<class T>T* Singleton<T>::m_instance=NULL;
#define CREATE_SINGLETON(class_name) \
    class class_name: public Singleton<class_name> { \
        friend class Singleton<class_name>;
}

#endif
