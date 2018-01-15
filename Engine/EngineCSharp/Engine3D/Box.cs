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
        private Box()
        {

        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Box Create(float l, float w, float h);
        
    }
}
