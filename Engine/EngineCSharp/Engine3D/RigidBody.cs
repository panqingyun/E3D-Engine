using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class RigidBody : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern void addRigidBody(Collider collider);

        private float mass;
        public RigidBody(Collider collider, float _mass)
        {
            mass = _mass;
           addRigidBody(collider);
        }
    }
}
