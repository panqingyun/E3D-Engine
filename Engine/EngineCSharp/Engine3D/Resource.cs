using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public delegate Object CreateDelegate(string str);
	public class Resource
	{
        private enum FileType
        {
            NONE,
            PARTICLE,
            MATERIAL,
            TEXTURE,
            SHADER,
        }
        private static Dictionary<string, FileType> fileTypeDic = new Dictionary<string, FileType>();
        private static Dictionary<FileType, CreateDelegate> createFunDic = new Dictionary<FileType, CreateDelegate>();

        static Resource()
		{
            fileTypeDic["particle"] = FileType.PARTICLE;
            fileTypeDic["material"] = FileType.MATERIAL;
            fileTypeDic["texture"] = FileType.TEXTURE;
            fileTypeDic["shader"] = FileType.SHADER;

            createFunDic[FileType.PARTICLE] = ParticleSystem.CreateParticle;
            createFunDic[FileType.MATERIAL] = Material.CreateMaterial;
            // TODO

        }

        static private FileType getFileType(string filePath)
        {
            FileType ft = FileType.NONE;
            if (File.Exists(filePath))
            {
                int lastPoint = filePath.LastIndexOf('.');
                string ext = filePath.Substring(lastPoint + 1);
                if (fileTypeDic.ContainsKey(ext.ToLower()))
                {
                    ft = fileTypeDic[ext.ToLower()];
                }
            }

            return ft;
        }

        public static Object Load(string filePath)
        {
            FileType ft = getFileType(filePath);
           
            if(createFunDic.ContainsKey(ft))
            {
                return createFunDic[ft](filePath);
            }
            return null;
        }
	}
}
