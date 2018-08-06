using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace E3DEngine
{
    public class Scene : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Scene createScene(string path);

        public List<GameObject> GameObjectList = new List<GameObject>();

      
        public static Scene LoadScene(string path)
        {
            Scene scene = createScene(path);
            return scene;
        }
    }
}
