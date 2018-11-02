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
        protected static extern void destory(GameObject go);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern Component addComponent(string comName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected static extern void newGameObject(GameObject go);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern Component getComponent(string comName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void removeComponent(Component com);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void AddChild(GameObject go);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern GameObject findChildWithName(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern GameObject findChildWithID(uint id);


        private Renderer m_pRenderer;

        public Renderer GetRenderer()
        {
            return m_pRenderer;
        }
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

        private Dictionary<string, List<Component>> component_dic = new Dictionary<string, List<Component>>();

        public Transform Transform;

        public GameObject()
        {
            newGameObject(this);
        }

        public void RemoveComponent(Component com)
        {
            if(component_dic.ContainsKey(com.GetType().FullName))
            {
                removeComponent(com);
                component_dic.Remove(com.GetType().FullName);
            }
        }

        public T GetComponent<T>() where T : Component
        {
            return GetComponent(typeof(T)) as T;
        }

        public Component GetComponent(Type tp)
        {
            return GetComponent(tp.FullName);
        }

        public Component GetComponent(string typeFullName)
        {
            return getComponent(typeFullName);
        }
        
        public List<Component> GetComponents(Type t)
        {
            return GetComponents(t.FullName);
        }

        public List<Component> GetComponents(string typeFullName)
        {
            if (component_dic.ContainsKey(typeFullName))
            {
                return component_dic[typeFullName];
            }
            return null;
        }

        public T AddComponent<T>() where T : Component
        {
            Type tp = typeof(T);

            Component com = AddComponent(tp);
            return com as T;
        }

        public Component AddComponent(Type tp)
        {
            return AddComponent(tp.FullName);
        }

        public Component AddComponent(string typeFullName)
        {
            Component com = addComponent(typeFullName);
            return com;
        }

        public GameObject FindChild(string name)
        {
            return findChildWithName(name);
        }

        public GameObject FindChild(uint id)
        {
            return findChildWithID(id);
        }

        public static void Destory(GameObject go)
        {
            destory(go);
            go = null;
        }
    }
}
