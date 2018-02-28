using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class ParticleSystem : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern ParticleGroup[] createParticle(string path);

        private ParticleSystem()
        {

        }

        public ParticleGroup[] Particles;

        public static ParticleSystem Create(string path, int id = 0)
        {
            ParticleSystem particle = new ParticleSystem();
            particle.Particles = particle.createParticle(path);
            return particle;
        }

        public void SetPosition(Vector3 pos)
        {

        }
    }

    public class ParticleGroup : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetEmitterEnable(bool isEnable);
    
    }
}
