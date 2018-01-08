using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class EMath
    {
        public const double M_PI = 3.14159265358979323846;
        public const double Epsilon = 4.37114e-05;
        /// <summary>
        /// 角度变弧度
        /// </summary>
        /// <param name="x">角度数</param>
        /// <returns></returns>
        public static double Deg2Rad(float x)
        {
            return x * M_PI / 180.0;
        }
    }
}
