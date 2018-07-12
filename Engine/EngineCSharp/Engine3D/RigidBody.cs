using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class RigidBody : Component
    {
        public float Mass
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }
}
