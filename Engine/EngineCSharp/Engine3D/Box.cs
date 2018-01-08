using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Box : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Box createBox(float l, float w, float h);

        public static Box CreateBox(float l, float w, float h)
        {
            Box box = createBox(l, w, h);
            return box;
        }

    }
}
