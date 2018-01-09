using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class GameObject : Object
    {

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern Component addComponent(string comName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void removeComponent(Component com);
        
        public bool Active
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public uint LayerMask
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public Material Material
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        private Dictionary<Type, List<Component>> component_dic = new Dictionary<Type, List<Component>>();
        
        public Transform Transform;

        public GameObject()
        {
            
        }

        public void RemoveComponent(Component com)
        {
            if(component_dic.ContainsKey(com.GetType()))
            {
                removeComponent(com);
                component_dic.Remove(com.GetType());
            }
        }

        public T GetComponent<T>() where T : Component
        {
            if(component_dic.ContainsKey(typeof(T)))
            {
                return component_dic[typeof(T)][0] as T;
            }
            return null;
        }

        public List<T> GetComponents<T>() where T : Component
        {
            if (component_dic.ContainsKey(typeof(T)))
            {
                return component_dic[typeof(T)] as List<T>;
            }
            return null;
        }

        public Component GetComponent(Type t)
        {
            if (component_dic.ContainsKey(t))
            {
                return component_dic[t][0];
            }
            return null;
        }

        public List<Component> GetComponents(Type t)
        {
            if (component_dic.ContainsKey(t))
            {
                return component_dic[t];
            }
            return null;
        }

        public T AddComponent<T>() where T : Component
        {
            Type tp = typeof(T);
            
            Component com = addComponent(tp.FullName);
            if(com == null)
            {
                return null;
            }
            com.gameObject = this;
            if(!component_dic.ContainsKey(tp))
            {
                component_dic[tp] = new List<Component>();
            }
            component_dic[tp].Add(com);
            return com as T;
        }
    }
}
