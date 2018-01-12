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

    public class AppGame
    {
        ParticleSystem particle = null;
        private Camera MainCamera = null;
        private Scene MainScene = null;
        private Box boxGround = null;
        Sphere sphere = null;
        public void Main(string[] args)
        {
            MainScene = Scene.LoadScene("Resource/Scene/MainEntry.scene");
            MainCamera = Camera.CreateCamera("MainCamera");
            MainCamera.SetClearColor(new Vector4(0.0f, 0.0f, 0.0f, 1));
            MainCamera.Transform.Position = new Vector3(0, 60, 200);
            MainCamera.Transform.Rotation = new Vector3(0, 0, 0);

            Material skyMaterial = Material.CreateMaterial("Resource/Material/SkyBox.material");
            GameObject.CreateSkyBox(skyMaterial);
            //Debug.Log(material.ID.ToString());

            float xStart = -80;
            float yStart = 300;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3 - i; j++)
                {
                    Box box = Box.CreateBox(10, 10, 10);
                    Material material = Material.CreateMaterial("Resource/Material/CubeMaterial.material");
                    box.AddComponent<App.CubeComponent>();
                    box.Material = material;
                    box.Transform.Position = new Vector3(xStart + 20 * j, yStart - i * 20, 0);
                    BoxCollider collider = box.AddComponent<BoxCollider>();
                    collider.CreateRigiBody(1000);
                }
                xStart += 16;
            }

            boxGround = Box.CreateBox(200, 100, 5);
            Material materialG = Material.CreateMaterial("Resource/Material/CubeMaterial.material");
            boxGround.Material = materialG;
            boxGround.Transform.Position = new Vector3(0, 0, 0);
            boxGround.Active = true;
            BoxCollider collider3 = boxGround.AddComponent<BoxCollider>();
            collider3.CreateRigiBody(0);
            Material materialS = Material.CreateMaterial("Resource/Material/SphereMaterial.material");
            sphere = Sphere.CreateSphere(20);
            sphere.Material = materialS;
            sphere.Transform.Position = new Vector3(0, 150, 0);
            SphereCollider sCollider = sphere.AddComponent<SphereCollider>();
            sCollider.CreateRigiBody(500);
            Material materialB = Material.CreateMaterial("Resource/Material/CubeMaterial.material");
            Box box1 = Box.CreateBox(30, 30, 30);
            box1.Material = materialB;
            box1.Transform.Position = new Vector3(25, 50, 0);
            BoxCollider collider4 = box1.AddComponent<BoxCollider>();
            collider4.CreateRigiBody(0);

            particle = new ParticleSystem();
            particle.CreateParticle("Resource/Particle/ParticleFire.particle");

            Terrain terrain = Terrain.CreateTerrain("Resource/Scene/MainEntry/hill.bmp");
            Material materialT = Material.CreateMaterial("Resource/Material/Terrain.material");
            terrain.Material = materialT;
            terrain.GetRenderer().DrawModule = eDrawModule.POINTS;
            //for(int i = 0; i < particle.Particles.Length; i ++)
            //{
            //    sphere.AddChild(particle.Particles[i]);
            //}
        }

        public void Update(float deltaTime)
        {     
            
        }

    }

}