
using System.Runtime.CompilerServices;

namespace E3DEngine
{

    public class PLightSceneConfig
    {
        public const string _TypeName = "PointLight";
        public const string _Color = "Color";
    }

    public enum LightType : uint
    {
        DIRECTION_LIGHT = 1,
        POINT_LIGHT,
        SPOT_LIGHT,
    };

    public class Light : Component
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern Light setColor(float r, float g, float b, float a);
        
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