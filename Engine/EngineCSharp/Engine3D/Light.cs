
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public enum LightType : uint
    {
        eDIRECTION_LIGHT = 1,
        ePOINT_LIGHT,
        eSPOT_LIGHT,
    };

    public class Light : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static Light Create(LightType type);

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

    class DirectionLight : Light
	{
	
	}

	class SpotLight : Light
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