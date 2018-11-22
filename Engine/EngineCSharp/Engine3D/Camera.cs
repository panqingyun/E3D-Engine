using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Camera : Component
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void renderCamera();

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void screen2WorldPoint(ref float x, ref float y, ref float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void world2ScreenPoint(ref float x, ref float y, ref float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void getViewMatrix(out float[] value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void getProjectionMatrix(out float[] value);

        private Matrix4x4 viewMatrix = new Matrix4x4();
        private Matrix4x4 projMatrix = new Matrix4x4();
        private Vector3 worldPoint;
        private Vector3 screenPoint;

        /// <summary>
        /// 前方向
        /// </summary>
        public Vector3 Forward
        {
            get
            {
                return gameObject.Transform.Forward * -1;
            }
        }

        /// <summary>
        /// 当前第一个摄像机
        /// </summary>
        public static Camera MainCamera
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        /// <summary>
        /// 上方向
        /// </summary>
        public Vector3 Up
        {
            get
            {
                return gameObject.Transform.Up;
            }
        }
        
        /// <summary>
        /// 右方向
        /// </summary>
        public Vector3 Right
        {
            get
            {
                return gameObject.Transform.Right;
            }
        }

        /// <summary>
        /// 渲染摄像机队列中的物体
        /// </summary>
        public void Render()
        {
            renderCamera();
        }

        public Vector3 WorldToScreenPoint(Vector3 worldPoint)
        {
            world2ScreenPoint(ref worldPoint.x, ref worldPoint.y, ref worldPoint.z);
            screenPoint = worldPoint;
            return screenPoint;
        }

        /// <summary>
        /// 把屏幕坐标转换成世界坐标
        /// </summary>
        /// <param name="screenPoint">屏幕坐标</param>
        /// <returns>世界坐标</returns>
        public Vector3 ScreenToWorldPoint(Vector3 screenPoint)
        {
            screen2WorldPoint(ref screenPoint.x, ref screenPoint.y, ref screenPoint.z);
            worldPoint = screenPoint;
            return worldPoint;
        }
        /// <summary>
        /// 获取视矩阵
        /// </summary>
        /// <returns>视图矩阵</returns>
        public Matrix4x4 GetViewMatrix()
        {
            getViewMatrix(out viewMatrix.data);
            return viewMatrix;
        }

        /// <summary>
        /// 获取投影矩阵
        /// </summary>
        /// <returns>投影矩阵</returns>
        public Matrix4x4 GetProjectionMatrix()
        {
            getProjectionMatrix(out projMatrix.data);
            return projMatrix;
        }
    }
}
