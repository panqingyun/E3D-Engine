using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Camera : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void renderCamera();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Camera createCamera(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setClearColor(float r, float g, float b, float a);

        public static Camera CreateCamera(string name)
        {
            return createCamera(name);
        }

        public void Render()
        {
            renderCamera();
        }

        public void SetClearColor(Vector4 color)
        {
            setClearColor(color.x, color.y, color.z, color.w);
        }
    }
}
