using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using E3DEngine;

/// <summary>
/// Entry point
/// </summary>
namespace Game
{
    class CubeComponent : Component
    {
        void Start()
        {
            
        }

        void Update(float deltaTime)
        {
            //Debug.Log(gameObject.Transform.Position.y.ToString());
        }

        void OnCollisionEnter(E3DEngine.Object collisionObject)
        {
           
        }
    }

    public class AppGame
    {
        private Camera MainCamera = null;
        private Scene MainScene = null;
        private Box boxGround = null;
        public void Main(string[] args)
        {
            MainScene = Scene.LoadScene("Resource/Scene/MainEntry.scene");
            MainCamera = Camera.CreateCamera("MainCamera");
            MainCamera.SetClearColor(new Vector4(0.4f, 0.4f, 0.4f, 0));
            MainCamera.Transform.Position = new Vector3(0, 0, 200);
            MainCamera.Transform.Rotation = new Vector3(-10f, 0, 0);
            Material material = Material.CreateMaterial("Resource/Scene/MainEntry/Material/CubeMaterial.material");
            Debug.Log(material.ID.ToString());
            float xStart = -80;
            float yStart = 300;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3 - i; j++)
                {
                    Box box = Box.CreateBox(10, 10, 10);
                    box.AddComponent<CubeComponent>();
                    box.Material = material;
                    box.Transform.Position = new Vector3(xStart + 20 * j, yStart - i * 20, 0);
                    BoxCollider collider = box.AddComponent<BoxCollider>();
                    collider.CreateRigiBody(50);
                }
                xStart += 16;
            }

            boxGround = Box.CreateBox(200, 100, 5);
            boxGround.Material = material;
            boxGround.Transform.Position = new Vector3(0, -50, 0);
            boxGround.Active = true;
            BoxCollider collider3 = boxGround.AddComponent<BoxCollider>();
            collider3.CreateRigiBody(0);
        }
        
        //private Vector3 rotate1 = new Vector3();
        //private Vector3 rotate2 = new Vector3();
        public void Update(float deltaTime)
        {
            //if (rotate1.y > 3.1415926 * 2)
            //{
            //    rotate1.y = 0;
            //}
            //if (rotate2.x > 3.1415926 * 2)
            //{
            //    rotate1.x = 0;
            //}
            //rotate1.y += 0.05f;
            //rotate2.x -= 0.1f;
            //box.Transform.Rotation = rotate1;
            //box2.Transform.Rotation = rotate2;
        }

    }

}