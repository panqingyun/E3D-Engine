using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    public class Scene : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Scene createScene();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void changeScene(uint sceneId);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void destoryScene(uint sceneId);

        public static Scene CreateScene()
        {
            return createScene();
        }

        public static Scene LoadScene(string path)
        {
            Scene scene = createScene();
            changeScene(scene.ID);
            return scene;
        }

        public static void DestoryScene(Scene scene)
        {
            if(scene == null)
            {
                return;
            }
            destoryScene(scene.ID);
        }

        public static void ChangeScene(Scene scene)
        {
            changeScene(scene.ID);
        }
    }
}
