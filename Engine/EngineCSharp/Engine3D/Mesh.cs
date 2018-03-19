using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Mesh : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Mesh create(string path, int configID);

        public static Mesh Create(string path, int configID)
        {
            return create(path, configID);
        }

    }
}
