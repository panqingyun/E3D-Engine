using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class Object
    {
        /// <summary>
        // 指向C++对象的指针， 在CPP中赋值
        /// </summary>
        private unsafe void* CppObject;

        ~Object()
        {
           
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_ManagedInstanceDeleted(IntPtr nativeInstance);

        public uint ID
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
        
        public string Name
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}