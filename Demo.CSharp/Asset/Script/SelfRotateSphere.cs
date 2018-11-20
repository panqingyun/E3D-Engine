using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class SelfRotateSphere : Component
{
    public float RotateSpeed = 0;

    void Start()
    {
    }

    private Vector3 rotate = new Vector3();
    void Update(float dt)
    {
        rotate.y += RotateSpeed * dt;
        if (rotate.y >= 360)
        {
            rotate.y = 0;
        }
        this.gameObject.Transform.Rotation = rotate;
    }

    void OnCollisionEnter(E3DEngine.Object collisionObject)
    {
       // Debug.LogWarning(collisionObject.Name + " Has Drop");
    }
}

namespace Game
{
    class BaseApp : Component
    {
        public int Number = 0;
        void Start()
        {
           // Debug.LogWarning(" qaq " + Number);
        }
    }
    namespace Bpp
    {
        class ABase
        {

        }
    }

}