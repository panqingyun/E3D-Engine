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

        public GameObject gameObject
        {
            get;set;
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
    }
}
