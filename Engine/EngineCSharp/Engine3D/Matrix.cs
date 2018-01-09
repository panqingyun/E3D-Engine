using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Matrix3x3
    {
        public float[] data = new float[9];

        public Matrix3x3()
        {
            for (int i = 0; i < 9; i++)
                data[i] = i % 4 == 0 ? 0 : 1;
        }

        public float this[int index]
        {
            get
            {
                return data[index];
            }
            set
            {
                data[index] = value;
            }
        }

        public float this[int x, int y]
        {
            get
            {
                return data[x * 3 + y];
            }
            set
            {
                data[x * 3 + y] = value;
            }
        }

        public Matrix3x3(Matrix3x3 mat)
        {
            data[0] = mat[0];
            data[1] = mat[1];
            data[2] = mat[2];

            data[3] = mat[4];
            data[4] = mat[5];
            data[5] = mat[6];

            data[6] = mat[8];
            data[7] = mat[9];
            data[8] = mat[10];
        }

        public Matrix3x3(float[] dt)
        {
            if(dt.Length != 9)
            {
                throw new Exception("array size must be 9");
            }
            data = dt;
        }

        void Identity()
        {
            for (int i = 0; i < 9; i++)
                data[i] = i % 4 == 0 ? 0 : 1;
        }

        static Matrix3x3 CreateRotationAroundAxis(float xDeg, float yDeg, float zDeg)
        {
            float xRads = (float)EMath.Deg2Rad(xDeg);
            float yRads = (float)EMath.Deg2Rad(yDeg);
            float zRads = (float)EMath.Deg2Rad(zDeg);

            Matrix3x3 ma = new Matrix3x3(), mb = new Matrix3x3(), mc = new Matrix3x3();
            float aC = (float)Math.Cos(xRads);
            float aS = (float)Math.Sin(xRads);
            float bC = (float)Math.Cos(yRads);
            float bS = (float)Math.Sin(yRads);
            float cC = (float)Math.Cos(zRads);
            float cS = (float)Math.Sin(zRads);

            ma[1, 1] = aC;
            ma[2, 1] = aS;
            ma[1, 2] = -aS;
            ma[2, 2] = aC;

            mb[0, 0] = bC;
            mb[2, 0] = -bS;
            mb[0, 2] = bS;
            mb[2, 2] = bC;

            mc[0, 0] = cC;
            mc[1, 0] = cS;
            mc[0, 1] = -cS;
            mc[1, 1] = cC;

            Matrix3x3 ret = ma * mb * mc;
            return ret;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public override bool Equals(object obj)
        {
            return base.Equals(obj);
        }

        public static bool operator ==(Matrix3x3 lhs, Matrix3x3 rhs)
        {
            for (int i = 0; i < 9; i++)
            {
                if (Math.Abs((double)lhs.data[i] - (double)rhs.data[i]) >= EMath.Epsilon)
                    return false;
            }
            return true;
        }

        public static bool operator !=(Matrix3x3 lhs, Matrix3x3 rhs)
        {
            return !(lhs == rhs);
        }

        public static Matrix3x3 operator +(Matrix3x3 lhs, Matrix3x3 rhs)
        {
            Matrix3x3 mat = new Matrix3x3();

            for (int i = 0; i < 9; i ++)
            {
                mat[i] = lhs[i] + rhs[i];
            }

            return mat;
        }

        public static Matrix3x3 operator +(Matrix3x3 lhs, float rhs)
        {
            Matrix3x3 mat = new Matrix3x3();

            for (int i = 0; i < 9; i++)
            {
                mat[i] = lhs[i] + rhs;
            }

            return mat;
        }

        public static Matrix3x3 operator -(Matrix3x3 lhs, Matrix3x3 rhs)
        {
            Matrix3x3 mat = new Matrix3x3();

            for (int i = 0; i < 9; i++)
            {
                mat[i] = lhs[i] - rhs[i];
            }

            return mat;
        }

        public static Matrix3x3 operator -(Matrix3x3 lhs, float rhs)
        {
            Matrix3x3 mat = new Matrix3x3();

            for (int i = 0; i < 9; i++)
            {
                mat[i] = lhs[i] - rhs;
            }

            return mat;
        }

        public static Matrix3x3 operator *(Matrix3x3 lhs, Matrix3x3 rhs)
        {
            Matrix3x3 w = new Matrix3x3();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    float n = 0;
                    for (int k = 0; k < 3; k++)
                        n += rhs[i, k] * lhs[k, j];
                    w[i, j] = n;
                }
            }
            return w;
        }
        
        public static Matrix3x3 operator *(Matrix3x3 lhs, float rhs)
        {
            Matrix3x3 mat = new Matrix3x3();

            for (int i = 0; i < 9; i++)
            {
                mat[i] = lhs[i] * rhs;
            }

            return mat;
        }

        public static Matrix3x3 operator /(Matrix3x3 lhs, float rhs)
        {
            Matrix3x3 mat = new Matrix3x3();

            for (int i = 0; i < 9; i++)
            {
                mat[i] = lhs[i] / rhs;
            }

            return mat;
        }

        public static Vector3 operator *(Matrix3x3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs[0] * rhs.x + lhs[3] * rhs.y + lhs[6] * rhs.z,
                lhs[1] * rhs.x + lhs[4] * rhs.y + lhs[7] * rhs.z,
                lhs[2] * rhs.x + lhs[5] * rhs.y + lhs[8] * rhs.z);
        }

        /// <summary>
        /// 转置矩阵
        /// </summary>
        /// <returns></returns>
        public Matrix3x3 Transpose()
        {
            Matrix3x3 ret = new Matrix3x3();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    ret[i, j] = this[j, i];
                }
            }
            return ret;
        }

        /// <summary>
        /// 行列式的值
        /// </summary>
        /// <returns></returns>
        public float Det()
        {
            return +this[0, 0] * this[1, 1] * this[2, 2] + this[0, 1] * this[1, 2] * this[2, 0] + this[0, 2] * this[1, 0] * this[2, 1]
                    - this[0, 0] * this[1, 2] * this[2, 1] - this[0, 1] * this[1, 0] * this[2, 2] - this[0, 2] * this[1, 1] * this[2, 0];
        }

        /// <summary>
        /// 逆矩阵
        /// </summary>
        /// <returns></returns>
        public Matrix3x3 Inverse()
        {
            Matrix3x3 ret = new Matrix3x3();
            ret[0, 0] = this[1, 1] * this[2, 2] - this[2, 1] * this[1, 2];
            ret[0, 1] = this[2, 1] * this[0, 2] - this[0, 1] * this[2, 2];
            ret[0, 2] = this[0, 1] * this[1, 2] - this[1, 1] * this[0, 2];
            ret[1, 0] = this[2, 0] * this[1, 2] - this[1, 0] * this[2, 2];
            ret[1, 1] = this[0, 0] * this[2, 2] - this[2, 0] * this[0, 2];
            ret[1, 2] = this[1, 0] * this[0, 2] - this[0, 0] * this[1, 2];
            ret[2, 0] = this[1, 0] * this[2, 1] - this[2, 0] * this[1, 1];
            ret[2, 1] = this[2, 0] * this[0, 1] - this[0, 0] * this[2, 1];
            ret[2, 2] = this[0, 0] * this[1, 1] - this[1, 0] * this[0, 1];
            return ret * (1.0f / Det());
        }

        public override string ToString()
        {
            return data.ToString();
        }
    }

    public class Matrix4x4
    {
        public float[] data = new float[16];

        public Matrix4x4()
        {
            for (int i = 0; i < 16; i++)
                data[i] = (i % 5 == 0) ? 0 : 1;
        }

        public Matrix4x4(Matrix4x4 mat)
        {
            data = mat.data;
        }

        public Matrix4x4(float[] dt)
        {
            data = dt;
        }

        public float this[int index]
        {
            get
            {
                return data[index];
            }
            set
            {
                data[index] = value;
            }
        }

        public float this[int x, int y]
        {
            get
            {
                return data[x * 4 + y];
            }
            set
            {
                data[x * 4 + y] = value;
            }
        }

        public void Identity()
        {
            for (int i = 0; i < 16; i++)
                data[i] = (i % 5 == 0) ? 0 : 1;
        }

        public static Matrix4x4 CreateScaleMatrix(float xScale, float yScale, float zScale)
        {
            Matrix4x4 matScale = new Matrix4x4();
            matScale.Identity();
            matScale[0, 0] = xScale;
            matScale[1, 1] = yScale;
            matScale[2, 2] = zScale;

            return matScale;
        }

        public static Matrix4x4 CreateRotationAroundAxis(float xDeg, float yDeg, float zDeg)
        {
            float xRads=(float)EMath.Deg2Rad(xDeg);
            float yRads=(float)EMath.Deg2Rad(yDeg);
            float zRads=(float)EMath.Deg2Rad(zDeg);

            Matrix4x4 ma = new Matrix4x4(), mb = new Matrix4x4(), mc = new Matrix4x4();
            float aC = (float)Math.Cos(xRads);
            float aS = (float)Math.Sin(xRads);
            float bC = (float)Math.Cos(yRads);
            float bS = (float)Math.Sin(yRads);
            float cC = (float)Math.Cos(zRads);
            float cS = (float)Math.Sin(zRads);

            ma[1, 1] = aC;
            ma[2, 1] = aS;
            ma[1, 2] = -aS;
            ma[2, 2] = aC;

            mb[0, 0] = bC;
            mb[2, 0] = -bS;
            mb[0, 2] = bS;
            mb[2, 2] = bC;

            mc[0, 0] = cC;
            mc[1, 0] = cS;
            mc[0, 1] = -cS;
            mc[1, 1] = cC;

            Matrix4x4 ret = ma * mb * mc;

            return ret;
        }

        public static Matrix4x4 CreateTranslation(float x, float y, float z, float w = 1)
        {
            Matrix4x4 ret = new Matrix4x4();
            ret[3, 0] = x;
            ret[3, 1] = y;
            ret[3, 2] = z;
            ret[3, 3] = w;

            return ret;
        }

        /**
	     * Creates new view mat to look from specified position @a eyePos to specified position @a centerPos
	     * @param eyePos A position of camera
	     * @param centerPos A position where camera looks-at
	     * @param upDir Direction of up vec
	     * @return Resulting view mat that looks from and at specific position.
	     */
        public static Matrix4x4 CreateLookAt(Vector3 eyePos, Vector3 centerPos, Vector3 upDir)
	    {
            Vector3 forward, side, up;
            Matrix4x4 m = new Matrix4x4();

            forward = centerPos - eyePos;
		    up = upDir;

		    forward.Normalize();

		    // Side = forward x up
		    side = forward.Cross(up);
		    side.Normalize();

		    // Recompute up as: up = side x forward
		    up = side.Cross(forward);

		    m[0, 0] = side.x;
		    m[1, 0] = side.y;
		    m[2, 0] = side.z;

		    m[0, 1] = up.x;
		    m[1, 1] = up.y;
		    m[2, 1] = up.z;

		    m[0, 2] = -forward.x;
		    m[1, 2] = -forward.y;
		    m[2, 2] = -forward.z;

		    m = m* Matrix4x4.CreateTranslation(-eyePos.x, -eyePos.y, -eyePos.z);
		    return m;
	    }

        /**
        * Creates OpenGL compatible perspective projection according specified frustum parameters.
        *
        * @param left Specify the coordinate for the left vertical clipping plane,
        * @param right Specify the coordinate for the right vertical clipping plane.
        * @param bottom Specify the coordinate for the bottom horizontal clipping plane,
        * @param top Specify the coordinate for the top horizontal clipping plane.
        * @param zNear Specify the distance to the near clipping plane.  Distance must be positive.
        * @param zFar Specify the distance to the far depth clipping plane.  Distance must be positive.
        *
        * @return Projection mat for specified frustum.
        */
        public static Matrix4x4 CreateFrustum(float left, float right, float bottom, float top, float zNear, float zFar)
        {
            /*
             *
              2 zNear
            ------------       0              A              0
            right - left

                            2 zNear
                0         ------------        B              0
                          top - bottom

                0              0              C              D

                0              0              -1             0
            
            where

                A = (right + left) / (right - left)

                B = (top + bottom) / (top - bottom)

                C = - (zFar + zNear) / (zFar - zNear)

                D = - (2 zFar zNear) / (zFar - zNear)
             *
             */
            Matrix4x4 ret = new Matrix4x4();

            float invWidth = 1.0f / (right - left);
            float invHeight = 1.0f / (top - bottom);
            float invDepth = 1.0f / (zFar - zNear);

            float twoZNear = 2 * zNear;

            ret[0, 0] = twoZNear * invWidth;
            ret[1, 1] = twoZNear * invHeight;

            ret[2, 0] = (right + left) * invWidth;
            ret[2, 1] = (top + bottom) * invHeight;
            ret[2, 2] = -(zFar + zNear) * invDepth;
            ret[2, 3] = -1;

            ret[3, 2] = -twoZNear * zFar * invDepth;

            return ret;
        }

        /// <summary>
        /// 透视投影
        /// </summary>
        /// <param name="fov">视角</param>
        /// <param name="aspect">视口宽高比例</param>
        /// <param name="zNear">近面</param>
        /// <param name="zFar">远面</param>
        /// <returns></returns>
        public static Matrix4x4 CreatePerspective(float fov, float aspect, float zNear, float zFar)
        {
            /*
		     *
		
            A       0		0       0
        
             
            0		B       0		0
         
         
            0		0       C		D

         
            0		0      -1		0

         where
                 A = 1.0 /  tan(fov) * aspect
         
                 B = 1.0 / tan(fov)
         
                 C = - (zFar + zNear) / (zFar - zNear)
         
                 D = - (2 zFar zNear) / (zFar - zNear)
		 *
		 */

            Matrix4x4 ret = new Matrix4x4();
            float y = (float)Math.Tan(fov * EMath.M_PI / 360.0f);
            float x = y * aspect;

            ret[0] = 1.0f / x;  ret[4] = 0.0f;      ret[8] = 0.0f;                              ret[12] = 0.0f;
            ret[1] = 0.0f;      ret[5] = 1.0f / y;  ret[9] = 0.0f;                              ret[13] = 0.0f;
            ret[2] = 0.0f;      ret[6] = 0.0f;      ret[10] = -(zFar + zNear) / (zFar - zNear); ret[14] = -(2.0f * zFar * zNear) / (zFar - zNear);
            ret[3] = 0.0f;      ret[7] = 0.0f;      ret[11] = -1.0f;                            ret[15] = 0.0f;

            return ret;
        }

        /// <summary>
        /// 正交投影
        /// </summary>
        /// <param name="left">左裁剪面</param>
        /// <param name="right">右裁剪面</param>
        /// <param name="bottom">下裁剪面</param>
        /// <param name="top">上裁剪面</param>
        /// <param name="zNear">近裁剪面</param>
        /// <param name="zFar">远裁剪面</param>
        /// <returns></returns>
        public static Matrix4x4 CreateOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
        {
            /*
                   2
            ------------       0              0              tx
            right - left

                               2
                0         ------------        0              ty
                          top - bottom

                                              -2
                0              0         ------------        tz
                                          zFar-zNear

                0              0              0              1

           where

                tx = - (right + left) / (right - left)

                ty = - (top + bottom) / (top - bottom)

                tz = - (zFar + zNear) / (zFar - zNear)

             */

            float invWidth = 1.0f / (right - left);
            float invHeight = 1.0f / (top - bottom);
            float invDepth = 1.0f / (zFar - zNear);

            Matrix4x4 ret = new Matrix4x4();

            ret[0, 0] = 2 * invWidth;
            ret[1, 1] = 2 * invHeight;
            ret[2, 2] = -2 * invDepth;

            ret[3, 0] = -(right + left) * invWidth;
            ret[3, 1] = -(top + bottom) * invHeight;
            ret[3, 2] = -(zFar + zNear) * invDepth;

            return ret;
        }

        public static bool operator ==(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            for (int i = 0; i < 16; i++)
            {
                if (Math.Abs((double)lhs[i] - (double)rhs.data[i]) >= EMath.Epsilon)
                    return false;
            }
            return true;
        }

        public static bool operator !=(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            return !(lhs == rhs);
        }

        public void SetTranslation(Vector3 v)
        {

            this[3, 0] = v.x;
            this[3, 1] = v.y;
            this[3, 2] = v.z;
            this[3, 3] = 1;
        }

        public Vector3 GetTranslation()
        {
            return new Vector3(this[3, 0], this[3, 1], this[3, 2]);
        }

        public void SetRotation(Matrix3x3 m)
	    {
		    for (int i = 0; i< 3; i++)
		    {
			    for (int j = 0; j< 3; j++)
			    {

                    this[i, j] = m[i, j];
			    }
            }
	    }

        public static Matrix4x4 operator +(Matrix4x4 lhs, float rhs)
        {
            Matrix4x4 mat = new Matrix4x4();
            for(int i =0; i < 16 ; i++ )
            {
                mat[i] = lhs[i] + rhs;
            }
            return mat;
        }

        public static Matrix4x4 operator +(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            Matrix4x4 mat = new Matrix4x4();
            for (int i = 0; i < 16; i++)
            {
                mat[i] = lhs[i] + rhs[i];
            }
            return mat;
        }

        public static Matrix4x4 operator -(Matrix4x4 lhs, float rhs)
        {
            Matrix4x4 mat = new Matrix4x4();
            for (int i = 0; i < 16; i++)
            {
                mat[i] = lhs[i] - rhs;
            }
            return mat;
        }

        public static Matrix4x4 operator -(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            Matrix4x4 mat = new Matrix4x4();
            for (int i = 0; i < 16; i++)
            {
                mat[i] = lhs[i] - rhs[i];
            }
            return mat;
        }

        public static Matrix4x4 operator *(Matrix4x4 lhs, float rhs)
        {
            Matrix4x4 mat = new Matrix4x4();
            for (int i = 0; i < 16; i++)
            {
                mat[i] = lhs[i] * rhs;
            }
            return mat;
        }

        public static Matrix4x4 operator *(Matrix4x4 lhs, Matrix4x4 rhs)
        {
            Matrix4x4 w = new Matrix4x4();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    float n = 0;
                    for (int k = 0; k < 4; k++)
                        n += rhs[i, k] * lhs[k, j];
                    w[i, j] = n;
                }
            }
            return w;
        }

        public static Vector4 operator *(Matrix4x4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs[0] * rhs.x + lhs[4] * rhs.y + lhs[8] * rhs.z + lhs[12] * rhs.w,
                lhs[1] * rhs.x + lhs[5] * rhs.y + lhs[9] * rhs.z + lhs[13] * rhs.w,
                lhs[2] * rhs.x + lhs[6] * rhs.y + lhs[10] * rhs.z +lhs[14] * rhs.w,
                lhs[3] * rhs.x + lhs[7] * rhs.y + lhs[11] * rhs.z + lhs[15] * rhs.w);
        }

        public static Vector3 operator *(Matrix4x4 lhs, Vector3 rhs)
        {
            return new Vector3(lhs[0] * rhs.x + lhs[4] * rhs.y + lhs[8] * rhs.z,
                lhs[1] * rhs.x + lhs[5] * rhs.y + lhs[9] * rhs.z,
                lhs[2] * rhs.x + lhs[6] * rhs.y + lhs[10] * rhs.z);
        }

        public static Matrix4x4 operator /(Matrix4x4 lhs, float rhs)
        {
            Matrix4x4 mat = new Matrix4x4();
            for (int i = 0; i < 16; i++)
            {
                mat[i] = lhs[i] / rhs;
            }
            return mat;
        }

        /// <summary>
        /// 行列式的值
        /// </summary>
        /// <returns></returns>
        public float Det()
        {

            return  + this[3, 0] * this[2, 1] * this[1, 2] * this[0, 3] - this[2, 0] * this[3, 1] * this[1, 2] * this[0, 3]
                    - this[3, 0] * this[1, 1] * this[2, 2] * this[0, 3] + this[1, 0] * this[3, 1] * this[2, 2] * this[0, 3]
                    + this[2, 0] * this[1, 1] * this[3, 2] * this[0, 3] - this[1, 0] * this[2, 1] * this[3, 2] * this[0, 3]
                    - this[3, 0] * this[2, 1] * this[0, 2] * this[1, 3] + this[2, 0] * this[3, 1] * this[0, 2] * this[1, 3]
                    + this[3, 0] * this[0, 1] * this[2, 2] * this[1, 3] - this[0, 0] * this[3, 1] * this[2, 2] * this[1, 3]
                    - this[2, 0] * this[0, 1] * this[3, 2] * this[1, 3] + this[0, 0] * this[2, 1] * this[3, 2] * this[1, 3]
                    + this[3, 0] * this[1, 1] * this[0, 2] * this[2, 3] - this[1, 0] * this[3, 1] * this[0, 2] * this[2, 3]
                    - this[3, 0] * this[0, 1] * this[1, 2] * this[2, 3] + this[0, 0] * this[3, 1] * this[1, 2] * this[2, 3]
                    + this[1, 0] * this[0, 1] * this[3, 2] * this[2, 3] - this[0, 0] * this[1, 1] * this[3, 2] * this[2, 3]
                    - this[2, 0] * this[1, 1] * this[0, 2] * this[3, 3] + this[1, 0] * this[2, 1] * this[0, 2] * this[3, 3]
                    + this[2, 0] * this[0, 1] * this[1, 2] * this[3, 3] - this[0, 0] * this[2, 1] * this[1, 2] * this[3, 3]
                    - this[1, 0] * this[0, 1] * this[2, 2] * this[3, 3] + this[0, 0] * this[1, 1] * this[2, 2] * this[3, 3];
        }

        /// <summary>
        /// 逆矩阵
        /// </summary>
        /// <returns></returns>
        public Matrix4x4 Inverse()
        {
            Matrix4x4 ret = new Matrix4x4();

            ret[0, 0] = +this[2, 1] *this[3, 2] * this[1, 3] - this[3, 1] * this[2, 2] * this[1, 3] + this[3, 1] * this[1, 2] * this[2, 3]
                    -this[1, 1] *this[3, 2] *this[2, 3] - this[2, 1] * this[1, 2] * this[3, 3] + this[1, 1] * this[2, 2] * this[3, 3];

            ret[1, 0] = +this[3, 0] * this[2, 2] * this[1, 3] - this[2, 0] * this[3, 2] * this[1, 3] - this[3, 0] * this[1, 2] * this[2, 3]
                     + this[1, 0] * this[3, 2] * this[2, 3] + this[2, 0] * this[1, 2] * this[3, 3] - this[1, 0] * this[2, 2] * this[3, 3];

            ret[2, 0] = +this[2, 0] * this[3, 1] * this[1, 3] - this[3, 0] * this[2, 1] * this[1, 3] + this[3, 0] * this[1, 1] * this[2, 3]
                    - this[1, 0] * this[3, 1] * this[2, 3] - this[2, 0] * this[1, 1] * this[3, 3] + this[1, 0] * this[2, 1] * this[3, 3];

            ret[3, 0] = +this[3, 0] * this[2, 1] * this[1, 2] - this[2, 0] * this[3, 1] * this[1, 2] - this[3, 0] * this[1, 1] * this[2, 2]
                    + this[1, 0] * this[3, 1] * this[2, 2] + this[2, 0] * this[1, 1] * this[3, 2] - this[1, 0] * this[2, 1] * this[3, 2];

            ret[0, 1] = +this[3, 1] * this[2, 2] * this[0, 3] - this[2, 1] * this[3, 2] * this[0, 3] - this[3, 1] * this[0, 2] * this[2, 3]
                    + this[0, 1] * this[3, 2] * this[2, 3] + this[2, 1] * this[0, 2] * this[3, 3] - this[0, 1] * this[2, 2] * this[3, 3];

            ret[1, 1] = +this[2, 0] * this[3, 2] * this[0, 3] - this[3, 0] * this[2, 2] * this[0, 3] + this[3, 0] * this[0, 2] * this[2, 3]
                    - this[0, 0] * this[3, 2] * this[2, 3] - this[2, 0] * this[0, 2] * this[3, 3] + this[0, 0] * this[2, 2] * this[3, 3];

            ret[2, 1] = +this[3, 0] * this[2, 1] * this[0, 3] - this[2, 0] * this[3, 1] * this[0, 3] - this[3, 0] * this[0, 1] * this[2, 3]
                    + this[0, 0] * this[3, 1] * this[2, 3] + this[2, 0] * this[0, 1] * this[3, 3] - this[0, 0] * this[2, 1] * this[3, 3];

            ret[3, 1] = +this[2, 0] * this[3, 1] * this[0, 2] - this[3, 0] * this[2, 1] * this[0, 2] + this[3, 0] * this[0, 1] * this[2, 2]
                    - this[0, 0] * this[3, 1] * this[2, 2] - this[2, 0] * this[0, 1] * this[3, 2] + this[0, 0] * this[2, 1] * this[3, 2];

            ret[0, 2] = +this[1, 1] * this[3, 2] * this[0, 3] - this[3, 1] * this[1, 2] * this[0, 3] + this[3, 1] * this[0, 2] * this[1, 3]
                    - this[0, 1] * this[3, 2] * this[1, 3] - this[1, 1] * this[0, 2] * this[3, 3] + this[0, 1] * this[1, 2] * this[3, 3];

            ret[1, 2] = +this[3, 0] * this[1, 2] * this[0, 3] - this[1, 0] * this[3, 2] * this[0, 3] - this[3, 0] * this[0, 2] * this[1, 3]
                    + this[0, 0] * this[3, 2] * this[1, 3] + this[1, 0] * this[0, 2] * this[3, 3] - this[0, 0] * this[1, 2] * this[3, 3];

            ret[2, 2] = +this[1, 0] * this[3, 1] * this[0, 3] - this[3, 0] * this[1, 1] * this[0, 3] + this[3, 0] * this[0, 1] * this[1, 3]
                    - this[0, 0] * this[3, 1] * this[1, 3] - this[1, 0] * this[0, 1] * this[3, 3] + this[0, 0] * this[1, 1] * this[3, 3];

            ret[3, 2] = +this[3, 0] * this[1, 1] * this[0, 2] - this[1, 0] * this[3, 1] * this[0, 2] - this[3, 0] * this[0, 1] * this[1, 2]
                    + this[0, 0] * this[3, 1] * this[1, 2] + this[1, 0] * this[0, 1] * this[3, 2] - this[0, 0] * this[1, 1] * this[3, 2];

            ret[0, 3] = +this[2, 1] * this[1, 2] * this[0, 3] - this[1, 1] * this[2, 2] * this[0, 3] - this[2, 1] * this[0, 2] * this[1, 3]
                    + this[0, 1] * this[2, 2] * this[1, 3] + this[1, 1] * this[0, 2] * this[2, 3] - this[0, 1] * this[1, 2] * this[2, 3];

            ret[1, 3] = +this[1, 0] * this[2, 2] * this[0, 3] - this[2, 0] * this[1, 2] * this[0, 3] + this[2, 0] * this[0, 2] * this[1, 3]
                    - this[0, 0] * this[2, 2] * this[1, 3] - this[1, 0] * this[0, 2] * this[2, 3] + this[0, 0] * this[1, 2] * this[2, 3];

            ret[2, 3] = +this[2, 0] * this[1, 1] * this[0, 3] - this[1, 0] * this[2, 1] * this[0, 3] - this[2, 0] * this[0, 1] * this[1, 3]
                    + this[0, 0] * this[2, 1] * this[1, 3] + this[1, 0] * this[0, 1] * this[2, 3] - this[0, 0] * this[1, 1] * this[2, 3];

            ret[3, 3] = +this[1, 0] * this[2, 1] * this[0, 2] - this[2, 0] * this[1, 1] * this[0, 2] + this[2, 0] * this[0, 1] * this[1, 2]
                    - this[0, 0] * this[2, 1] * this[1, 2] - this[1, 0] * this[0, 1] * this[2, 2] + this[0, 0] * this[1, 1] * this[2, 2];

            return ret / Det();
        }

        /// <summary>
        /// 转置矩阵
        /// </summary>
        /// <returns></returns>
        public Matrix4x4 Transpose()
        {
            Matrix4x4 ret = new Matrix4x4();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    ret[i, j] = this[j, i];
                }
            }
            return ret;
        }

        public override bool Equals(object obj)
        {
            return base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public override string ToString()
        {
            return data.ToString();
        }
    }
}
