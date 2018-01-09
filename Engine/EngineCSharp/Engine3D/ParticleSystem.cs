using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class ParticleSystem : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern ParticleGroup[] createParticle(string path);

        public ParticleGroup[] Particles;

        public void CreateParticle(string path)
        {
            Particles = createParticle(path);
        }

    }

    public class ParticleGroup : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetEmitterEnable(bool isEnable);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void moveEmitter(float x, float y, float z);

        public void MoveEmitter(Vector3 newPos)
        {
            moveEmitter(newPos.x, newPos.y, newPos.z);
        }
    }
}
