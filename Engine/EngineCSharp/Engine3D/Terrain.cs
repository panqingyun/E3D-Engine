
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class Terrain : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Terrain Create(string heightMapNamer);
    }
}