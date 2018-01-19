
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public enum LightType : uint
    {
        DIRECTION_LIGHT = 1,
        POINT_LIGHT,
        SPOT_LIGHT,
    };

    public class Light : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Light Create(LightType type);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern Light setColor(float r, float g, float b, float a);
        
        public static T Create<T>() where T : Light
        {
            Light l = null;
            if (typeof(T) == typeof(PointLight))
            {
                 l = Create(LightType.POINT_LIGHT);
            }
            else if(typeof(T) == typeof(DirectionLight))
            {
                l = Create(LightType.DIRECTION_LIGHT);
            }
            else if (typeof(T) == typeof(SpotLight))
            {
                l = Create(LightType.SPOT_LIGHT);
            }
            return l as T;
        }

        public Vector4 Color
        {
            set
            {
                setColor(value.x, value.y, value.z, value.w);
            }

        }// 颜色
        public float Intensity
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }// 强度
    }

    public class PointLight : Light
	{
	    public float Range
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }

    public class DirectionLight : Light
	{
	
	}

    public class SpotLight : Light
	{
	    public float Range
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        public int SpotAngle
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
	}
}