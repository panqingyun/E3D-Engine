using System;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class Material : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Material createMaterial(string materialPath, int id);

        private Material()
        {

        }
        public static Material CreateMaterial(string materialPath, int id = 1)
        {
            return createMaterial(materialPath, id);
        }

        public void UpdateFloatValue(string name, float value)
        {

        }
    }
}