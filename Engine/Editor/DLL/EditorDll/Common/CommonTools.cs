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
        static Dictionary<string, FileType> extMap = new Dictionary<string, FileType>();
        static CommonTools()
        {
            extMap[".jpg"]      = FileType.eImage;
            extMap[".png"]      = FileType.eImage;
            extMap[".tga"]      = FileType.eImage;
            extMap[".bmp"]      = FileType.eImage;
            extMap[".dds"]      = FileType.eImage;
            extMap[".txt"]      = FileType.eText;
            extMap[".plist"]    = FileType.eText;
            extMap[".xml"]      = FileType.eText;
            extMap[".js"]       = FileType.eText;
            extMap[".json"]     = FileType.eText;
            extMap[".fbx"]      = FileType.eModel;
            extMap[".obj"]      = FileType.eModel;
            extMap[".x"]        = FileType.eModel;
            extMap[".3d"]       = FileType.eModel;
            extMap[".cs"]       = FileType.eScript;
            extMap[".prefab"]   = FileType.ePrefab;
            extMap[".scene"]    = FileType.eScene;
            extMap[".mp3"]      = FileType.eAudio;
            extMap[".wav"]      = FileType.eAudio;
            extMap[".ogg"]      = FileType.eAudio;
            extMap[".mp4"]      = FileType.eVideo;
            extMap[".particle"] = FileType.eParticle;
            extMap[".material"] = FileType.eMaterial;
            extMap[".glsl"]     = FileType.eShader;
            extMap[".shader"]   = FileType.eShader;
            extMap[".hlsl"]     = FileType.eShader;
            extMap[".cginc"]    = FileType.eShader;
        }

        public static FileType GetFileType(string fileName)
        {
            int fileExtPos = fileName.LastIndexOf('.');
            if (fileExtPos == -1)
            {
                return FileType.eUnKnown;
            }

            string ext = fileName.Substring(fileExtPos);
            ext = ext.ToLower();
            if (extMap.ContainsKey(ext))
            {
                return extMap[ext];
            }
           
            return FileType.eUnKnown;
        }
    }
}
