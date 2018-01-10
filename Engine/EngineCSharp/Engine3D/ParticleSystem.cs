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

        public ParticleGroup[] Particles;

        public void CreateParticle(string path)
        {
            Particles = createParticle(path);
        }

    }

    public class ParticleGroup : GameObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetEmitterEnable(bool isEnable);
    
    }
}
