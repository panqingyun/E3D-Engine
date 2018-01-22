using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Transform : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getPosition( out float x, out float y, out float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setPosition( float x, float y, float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getScale(out float x, out float y, out float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setScale(float x, float y, float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getRotation(out float x, out float y, out float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setRotation(float x, float y, float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getForward(out float x, out float y, out float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getUp(out float x, out float y, out float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getRight(out float x, out float y, out float z);

        public GameObject gameObject
        {
            get;set;
        }
        
        public void SetRote(Quaternion quat)
        {
            rotation = rotation + quat.ToEulerAngles();
            Rotation = rotation;
        }

        public Quaternion GetRoate()
        {
            Vector3 vec = Rotation;
            return Quaternion.FromEulerAngles(vec.x, vec.y, vec.z);
        }
       
        private Vector3 position;
        public Vector3 Position
        {
            get
            {
                float x, y, z;
                getPosition(out x, out y, out z);
                position.SetValue(x, y, z);
                return position;
            }
            set
            {
                setPosition(value.x, value.y, value.z);
                position = value;
            }
        }

        private Vector3 scale;
        public Vector3 Scale
        {
            get
            {
                float x, y, z;
                getScale(out x, out y, out z);
                scale.SetValue(z, y, z);
                return scale;
            }
            set
            {
                setScale(value.x, value.y, value.z);
                scale = value;
            }
        }

        private Vector3 rotation;
        public Vector3 Rotation
        {
            get
            {
                float x, y, z;
                getRotation(out x, out y, out z);
                rotation.SetValue(z, y, z);
                return rotation;
            }
            set
            {
                setRotation(value.x, value.y, value.z);
                rotation = value;
            }
        }

        private Vector3 forward;
        public Vector3 Forward
        {
            get
            {
                float x, y, z;
                getForward(out x, out y, out z);
                forward.SetValue(x, y, z);
                return forward;
            }
        }
        private Vector3 up;
        public Vector3 Up
        {
            get
            {
                float x, y, z;
                getUp(out x, out y, out z);
                up.SetValue(x, y, z);
                return up;
            }
        }

        private Vector3 right;
        public Vector3 Right
        {
            get
            {
                float x, y, z;
                getRight(out x, out y, out z);
                right.SetValue(x, y, z);
                return right;
            }
        }
    }
}
