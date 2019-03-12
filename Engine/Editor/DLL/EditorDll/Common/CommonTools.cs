using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    public class CommonTools
    {
        public static FileType GetFileType(string fileName)
        {
            int fileExtPos = fileName.LastIndexOf('.');
            if (fileExtPos == -1)
            {
                return FileType.eUnKnown;
            }

            string ext = fileName.Substring(fileExtPos);
            ext = ext.ToLower();
            if (ext == ".jpg" || ext == ".png" || ext == ".tga" || ext == ".bmp" || ext == ".dds")
            {
                return FileType.eImage;
            }
            if (ext == ".txt" || ext == ".plist" || ext == ".xml" || ext == ".js" || ext == ".json" )
            {
                return FileType.eText;
            }
            if (ext == ".fbx" || ext == ".obj" || ext == ".x" || ext == ".3d")
            {
                return FileType.eModel;
            }
            if(ext == ".cs")
            {
                return FileType.eScript;
            }
            if (ext == ".prefab")
            {
                return FileType.ePrefab;
            }
            if (ext == ".scene")
            {
                return FileType.eScene;
            }
            if (ext == ".mp3" || ext == ".wav" || ext == ".ogg")
            {
                return FileType.eAudio;
            }
            if (ext == ".mp4")
            {
                return FileType.eVideo;
            }
            if (ext == ".particle")
            {
                return FileType.eParticle;
            }
            if (ext == ".material")
            {
                return FileType.eMaterial;
            }
            if (ext == ".shader")
            {
                return FileType.eShader;
            }
            return FileType.eUnKnown;
        }
    }
}
