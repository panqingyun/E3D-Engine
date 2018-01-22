using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public delegate Object CreateDelegate(string str);
	public class Resource
	{
        private static Dictionary<Type, CreateDelegate> createFunDic = new Dictionary<Type, CreateDelegate>();

        static Resource()
		{
            createFunDic[typeof(ParticleSystem)] = ParticleSystem.CreateParticle;
            createFunDic[typeof(Material)] = Material.CreateMaterial;
            // TODO

        }

        public static T Load<T>(string filePath) where T : Object
        {
            Type tp = typeof(T);
            if (createFunDic.ContainsKey(tp))
            {
                return createFunDic[tp](Application.ResourcePath + filePath) as T;
            }
            return null;
        }

        public static Object Load(string filePath, Type tp)
        {            
            if(createFunDic.ContainsKey(tp))
            {
                return createFunDic[tp](filePath);
            }
            return null;
        }
	}
}
