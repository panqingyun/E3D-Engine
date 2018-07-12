using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Collider : Component
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setSize(float x, float y, float z);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void getSize(out float x, out float y, out float z);

        private Vector3 size = new Vector3();
        public Vector3 Size
        {
            get
            {
                float x, y, z;
                getSize(out x, out y, out z);
                size.SetValue(x, y, z);
                return size;
            }
            set
            {
                size = value;
                setSize(value.x, value.y, value.z);
            }
        }
    }

    public class BoxCollider : Collider
    {
        
    }

    public class SphereCollider : Collider
    {

    }

    public class MeshCollider : Collider
    {

    }

    public class CapsuleCollider : Collider
    {
        public float Radius
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public float Height
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
