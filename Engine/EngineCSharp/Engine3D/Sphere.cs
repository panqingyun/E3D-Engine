
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class Sphere : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Sphere CreateSphere(float R);
    }
}