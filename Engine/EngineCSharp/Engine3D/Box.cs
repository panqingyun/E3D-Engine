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
}
