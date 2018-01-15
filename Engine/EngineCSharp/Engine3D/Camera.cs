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

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void screen2WorldPoint(ref float x, ref float y, ref float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void getViewMatrix(out float[] value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void getProjectionMatrix(out float[] value);
        
        public Vector3 Forward
        {
            get
            {
                return Transform.Forward * -1;
            }
        }

        public Vector3 Up
        {
            get
            {
                return Transform.Up;
            }
        }
        
        public Vector3 Right
        {
            get
            {
                return Transform.Right;
            }
        }
        private Matrix4x4 viewMatrix = new Matrix4x4();
        private Matrix4x4 projMatrix = new Matrix4x4();
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

        public Vector3 ScreenToWorldPoint(Vector3 screenPoint)
        {
            float x = 0, y = 0, z = 0;
            screen2WorldPoint(ref x, ref y, ref z);
            return new Vector3(x, y, z);
        }

        public Matrix4x4 GetViewMatrix()
        {
            getViewMatrix(out viewMatrix.data);
            return viewMatrix;
        }

        public Matrix4x4 GetProjectionMatrix()
        {
            getProjectionMatrix(out projMatrix.data);
            return projMatrix;
        }
    }
}
