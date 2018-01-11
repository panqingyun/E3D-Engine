using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Sphere : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Sphere CreateSphere(float R);
    }
}
