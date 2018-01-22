using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public struct Vector2
    {
        public float x;
        public float y;

        public Vector2(float _x, float _y)
        {
            x = _x;
            y = _y;
        }

        public void SetValue(float _x, float _y)
        {
            x = _x;
            y = _y;
        }

        public float Length()
	    {
		    return (float)Math.Sqrt(x* x + y* y);
        }

        public void Normalize()
        {
            float s = Length();

            if (s == 0.0f)
                return;

            float inv = 1 / s;
            x *= inv;
            y *= inv;
        }

        public float this[int index]
        {
            get
            {
                if (index == 0)
                    return x;
                else if (index == 1)
                    return y;
                throw new IndexOutOfRangeException();
            }
            set
            {
                if(index == 0)
                    x = value;
                else if(index == 1)
                    y = value;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        public static Vector2 operator +(Vector2 lhs, float rhs)
        {
            Vector2 vec = new Vector2(lhs.x + rhs, lhs.y + rhs);
            return vec;
        }

        public static Vector2 operator -(Vector2 lhs, float rhs)
        {
            return new Vector2(lhs.x - rhs, lhs.y - rhs);
        }

        public static Vector2 operator *(Vector2 lhs, float rhs)
        {
            return new Vector2(lhs.x * rhs, lhs.y * rhs);
        }

        public static Vector2 operator /(Vector2 lhs, float rhs)
        {
            return new Vector2(lhs.x / rhs, lhs.y / rhs);
        }

        public static Vector2 operator +(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        public static Vector2 operator -(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x - rhs.x, lhs.y - rhs.x);
        }

        public static Vector2 operator *(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x * rhs.y, lhs.y * rhs.y);
        }

        public static Vector2 operator /(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
        }


    }

    public struct Vector3
    {
        public float x;
        public float y;
        public float z;

        public Vector3(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        public Vector3(Vector3 vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }

        public void SetValue(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }
        public float Length()
        {
            return (float)Math.Sqrt(x * x + y * y + z * z);
        }

        public float LengthSq()
        {
            return x * x + y * y + z * z;
        }

        public void Normalize()
        {
            float s = Length();
            if (s == 0.0f)
                return;

            float inv = 1 / s;
            x *= inv;
            y *= inv;
            z *= inv;
        }

        float Dot(Vector3 rhs)
    	{
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }
        
        public Vector3 Cross(Vector3 rhs)
        {
            return new Vector3(y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x, x * rhs.y - rhs.x * y);
        }


        public float Distance(Vector3 rhs)
        {
            return (float)Math.Sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) + (z - rhs.z) * (z - rhs.z));
        }

        /// <summary>
        /// 旋转
        /// </summary>
        /// <param name="ax">绕x轴旋转的角度数</param>
        /// <param name="ay">绕y轴旋转的角度数</param>
        /// <param name="az">绕z轴旋转的角度数</param>
        public void Rotate(float ax, float ay, float az)
        {
            float a = (float)Math.Cos(EMath.Deg2Rad(ax));
            float b = (float)Math.Sin(EMath.Deg2Rad(ax));
            float c = (float)Math.Cos(EMath.Deg2Rad(ay));
            float d = (float)Math.Sin(EMath.Deg2Rad(ay));
            float e = (float)Math.Cos(EMath.Deg2Rad(az));
            float f = (float)Math.Sin(EMath.Deg2Rad(az));
            float nx = c * e * x - c * f * y + d * z;
            float ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
            float nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
            x = nx;
            y = ny;
            z = nz;

        }

        public Vector3 Lerp(float fact, Vector3 r)
        {
            return this + (r - this) * fact;
        }

        public float this[int index]
        {
            get
            {
                if (index == 0)
                    return x;
                else if (index == 1)
                    return y;
                else if(index == 2)
                    return z;
                throw new IndexOutOfRangeException();
            }
            set
            {
                if (index == 0)
                    x = value;
                else if (index == 1)
                    y = value;
                else if (index == 2)
                    z = value;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public static bool operator ==(Vector3 lhs, Vector3 rhs)
        {
            return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
        }

        public static bool operator !=(Vector3 lhs, Vector3 rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            return this == (Vector3)obj;
        }


        public static Vector3 operator +(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
        }

        public static Vector3 operator -(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
        }

        public static Vector3 operator *(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z *rhs);
        }

        public static Vector3 operator /(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
        }

        public static Vector3 operator +(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        public static Vector3 operator -(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x - rhs.x, lhs.y - rhs.x, lhs.z - rhs.z);
        }

        public static Vector3 operator *(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x * rhs.y, lhs.y * rhs.y, lhs.z * rhs.z);
        }

        public static Vector3 operator /(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
        }
    }

    public struct Vector4
    {
        public float x;
        public float y;
        public float z;
        public float w;

        public Vector4(float _x, float _y, float _z, float _w)
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }
        public void SetValue(float _x, float _y, float _z, float _w)
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        public float Length()
        {
            return (float)Math.Sqrt(x * x + y * y + z * z + w * w);
        }

        public void Normalize()
        {
            float s = Length();
            if (s == 0.0f)
                return;

            float inv = 1 / s;
            x *= inv;
            y *= inv;
            z *= inv;
            w *= inv;
        }

        public float this[int index]
        {
            get
            {
                if (index == 0)
                    return x;
                else if (index == 1)
                    return y;
                else if (index == 2)
                    return z;
                else if(index == 3)
                    return w;
                throw new IndexOutOfRangeException();
            }
            set
            {
                if (index == 0)
                    x = value;
                else if (index == 1)
                    y = value;
                else if (index == 2)
                    z = value;
                else if (index == 3)
                    w = value;
                else
                    throw new IndexOutOfRangeException();
            }
        }
        public static Vector4 operator +(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
        }

        public static Vector4 operator -(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
        }

        public static Vector4 operator *(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
        }

        public static Vector4 operator /(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
        }

        public static Vector4 operator +(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
        }

        public static Vector4 operator -(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x - rhs.x, lhs.y - rhs.x, lhs.z - rhs.z, lhs.w - rhs.w);
        }

        public static Vector4 operator *(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x * rhs.y, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
        }

        public static Vector4 operator /(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
        }
    }
}
