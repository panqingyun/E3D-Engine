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
        protected extern Component getComponent(string comName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void removeComponent(Component com);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void AddChild(GameObject go);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern GameObject findChildWithName(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern GameObject findChildWithID(uint id);

        public Renderer Renderer
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
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
        
        public Transform Transform;
       

        public void RemoveComponent(Component com)
        {
            removeComponent(com);
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
