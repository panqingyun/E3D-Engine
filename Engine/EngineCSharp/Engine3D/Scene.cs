﻿using System;
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

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void changeScene(uint sceneId);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void destoryScene(uint sceneId);

        public List<GameObject> GameObjectList = new List<GameObject>();

      
        public static Scene LoadScene(string path)
        {
            Scene scene = createScene(path);
           // changeScene(scene.ID);

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
