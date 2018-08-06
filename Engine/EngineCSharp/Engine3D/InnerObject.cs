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
        /// <summary>
        /// 创建一个长方体
        /// </summary>
        /// <param name="l">长</param>
        /// <param name="w">宽</param>
        /// <param name="h">高</param>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Box Create(float l, float w, float h);
        
    }

    public class Sphere : GameObject
    {
        private Sphere()
        {

        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Sphere Create(float R);
    }

    public class SkyBox : GameObject
    {
        private SkyBox() { }
        /// <summary>
        /// 天空盒
        /// </summary>
        /// <param name="skyMaterial"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void CreateSkyBox(Material skyMaterial);
    }

    public class SkeyDome : GameObject
    {
        private SkeyDome() { }
        /// <summary>
        /// 天空穹
        /// </summary>
        /// <param name="skyMaterial"></param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void CreateSkyDome(Material skyMaterial);
    }
}
