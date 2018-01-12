using System;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public class Material : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Material createMaterial(string materialPath);

        private Material()
        {

        }
        public static Material CreateMaterial(string materialPath)
        {
            return createMaterial(materialPath);
        }

        public void UpdateFloatValue(string name, float value)
        {

        }
    }
}