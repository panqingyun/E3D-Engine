﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using E3DEngine;
using log4net;

/// <summary>
/// Entry point
/// </summary>
namespace Game
{
    namespace App
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
        
    }

    public class AppDemo
    {
        ParticleSystem particle = null;
        private Camera MainCamera = null;
        private Scene MainScene = null;
        private Box boxGround = null;
        Sphere sphere = null;
        string skyBoxMaterialPath = "Material/SkyBox.material";
        string skyDomeMaterialPath = "Material/SkyDome.material";
        string cubeMaterialPath = "Material/CubeMaterial.material";
        string sphereMaterialPath = "Material/SphereMaterial.material";
        string particleFirePath = "Particle/ParticleFire.particle";
        string mainScenePath = "Scene/MainEntry.scene";
        string meshFilePath = "Mesh/Flower.mesh";
        Vector2 curMousePosition;
        Vector2 lastMousePosition;
        float cameraRotateX = 0, cameraRotateY = 0;
        bool mouseRButtonDown = false, mouseMButtonDown = false;
        Vector3 cameraRotation;
        Vector3 rotate = new Vector3();
        Mesh mesh = null;

        public void Main(string[] args)
        {
            MainScene = Scene.LoadScene(mainScenePath);
            MainCamera = Camera.Create();
            MainCamera.SetClearColor(new Vector4(0.0f, 0.0f, 0.0f, 1));
            MainCamera.Transform.Position = new Vector3(-20, 30, 50);
            MainCamera.Transform.Rotation = new Vector3(0, -10, 0);
            cameraRotateX = -MainCamera.Transform.Rotation.x;
            cameraRotateY = -MainCamera.Transform.Rotation.y;
            Light light = Light.Create<DirectionLight>();
            light.Color = new Vector4(1, 1, 1, 1.0f);
            light.Transform.Position = new Vector3(50, 50, 0);

            // PointLight pLight = Light.Create<PointLight>();
            // pLight.Range = 100;
            // pLight.Color = new Vector4(1, 1, 1, 1.0f);
            // pLight.Transform.Position = new Vector3(0, 0, 50);
            Material skyMaterial = Resource.Load<Material>(skyBoxMaterialPath);
            //GameObject.CreateSkyDome(skyMaterial);
            GameObject.CreateSkyBox(skyMaterial);
            //Debug.Log(material.ID.ToString());
            mesh = Resource.Load<Mesh>(meshFilePath);
            mesh.Transform.Position = new Vector3(0, 0, -100);
            mesh.Transform.Rotation = new Vector3(-90, 0, 0);
            //float xStart = -18;
            //float yStart = 50;
            //for (int i = 0; i < 15; i++)
            //{
            //    for (int j = 0; j < 15 - i; j++)
            //    {
            //        Box box = Box.Create(1, 1, 1);
            //        Material material = Resource.Load<Material>(cubeMaterialPath);
            //        box.AddComponent<App.CubeComponent>();
            //        box.Material = material;
            //        box.Transform.Position = new Vector3(xStart + 2 * j, yStart - i * 2, 0);
            //        BoxCollider collider = box.AddComponent<BoxCollider>();
            //        collider.CreateRigiBody(50);
            //    }
            //    xStart += 1.6f;
            //}

            //boxGround = Box.Create(50, 10, 0.5f);
            //Material materialG = Resource.Load<Material>(cubeMaterialPath);
            //boxGround.Material = materialG;
            //boxGround.Transform.Position = new Vector3(0, 0, 0);
            //boxGround.Transform.Rotation = new Vector3(0, 0, 20);
            //boxGround.Active = true;
            //BoxCollider collider3 = boxGround.AddComponent<BoxCollider>();
            //collider3.CreateRigiBody(0);
            //Material materialS = Resource.Load<Material>(sphereMaterialPath);
            //sphere = Sphere.Create(20);
            //sphere.Material = materialS;
            //sphere.Transform.Position = new Vector3(-30, 40, 0);
            //SphereCollider sCollider = sphere.AddComponent<SphereCollider>();
            //sCollider.CreateRigiBody(0);
            //Material materialB = Resource.Load<Material>(cubeMaterialPath);
            //Box box1 = Box.Create(3, 3, 3);
            //box1.Material = materialB;
            //box1.Transform.Position = new Vector3(2.5f, 5, 0);
            //BoxCollider collider4 = box1.AddComponent<BoxCollider>();
            //collider4.CreateRigiBody(0);

            //Material materialB2 = Resource.Load<Material>(cubeMaterialPath);
            //Box box2 = Box.Create(50, 10, 0.5f);
            //box2.Material = materialB2;
            //box2.Transform.Position = new Vector3(-25f, 15, 0);
            //box2.Transform.Rotation = new Vector3(0, 0, -20);
            //BoxCollider collider5 = box2.AddComponent<BoxCollider>();
            //collider5.CreateRigiBody(0);
            //particle = Resource.Load<ParticleSystem>(particleFirePath);

            //Vector3 nwPos = new Vector3(box1.Transform.Position.x - 1, box1.Transform.Position.y - 1.1f, box1.Transform.Position.z);
            //for (int i = 0; i < particle.Particles.Length; i++)
            //{
            //    particle.Particles[i].Transform.Position = nwPos;
            //}
        }

        public void MouseButtonDown(MouseButtonInfo mouseInfo)
        {
            lastMousePosition.x = mouseInfo.mPositionX;
            lastMousePosition.y = mouseInfo.mPositionY;
            if (mouseInfo.mButton == MouseButton.RightButton)
            {
                mouseRButtonDown = true;
            }
            else if(mouseInfo.mButton == MouseButton.MiddleButton)
            {
                mouseMButtonDown = true;
            }
        }

        public void MouseButtonUp(MouseButtonInfo mouseInfo)
        {
            if (mouseInfo.mButton == MouseButton.RightButton)
            {
                mouseRButtonDown = false;
            }
            else if(mouseInfo.mButton == MouseButton.MiddleButton)
            {
                mouseMButtonDown = false;
            }
        }

        Vector3 curPos = new Vector3();
        public void MouseMove(MouseButtonInfo mouseInfo)
        {
            curMousePosition.x = mouseInfo.mPositionX;
            curMousePosition.y = mouseInfo.mPositionY;

            if (mouseRButtonDown)
            {
                float rotaX = curMousePosition.y - lastMousePosition.y;
                float rotaY = curMousePosition.x - lastMousePosition.x;

                lastMousePosition = curMousePosition;

                cameraRotateX += rotaX * 0.2f;
                cameraRotateY += rotaY * 0.2f;
                cameraRotation.SetValue(-cameraRotateX, -cameraRotateY, 0);
                MainCamera.Transform.Rotation = cameraRotation;
            }
            else if(mouseMButtonDown)
            {
                curPos.SetValue(-curMousePosition.x + lastMousePosition.x, curMousePosition.y - lastMousePosition.y, 0);

                Vector3 dir = MainCamera.GetViewMatrix().Inverse() * curPos;
                dir.Normalize();
                Vector3 newPos = MainCamera.Transform.Position + dir;
                lastMousePosition = curMousePosition;
                MainCamera.Transform.Position = newPos;
            }
        }

        public void Update(float deltaTime)
        {
            //rotate.y += 1;
            //if(rotate.y == 360)
            //{
            //    rotate.y = 0;
            //}
            //sphere.Transform.Rotation = rotate;
        }

        Vector3 curCameraPos = new Vector3();
        Vector3 curCameraDir = new Vector3();

        private void KeyDown(KeyCode keyCode)
        {
            curCameraPos = MainCamera.Transform.Position;
            if (keyCode == KeyCode.KeyW)
            {
                curCameraDir = MainCamera.Forward;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir;
            }
            else if(keyCode == KeyCode.KeyS)
            {
                curCameraDir = MainCamera.Forward * -1;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir;
            }
            else if(keyCode == KeyCode.KeyA)
            {
                curCameraDir = MainCamera.Right * -1;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir;
            }
            else if (keyCode == KeyCode.KeyD)
            {
                curCameraDir = MainCamera.Right;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir;
            }
            else if (keyCode == KeyCode.KeyE)
            {
                curCameraDir = MainCamera.Up;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir;
            }
            else if (keyCode == KeyCode.KeyQ)
            {
                curCameraDir = MainCamera.Up * -1;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir;
            }
        }
    }

}