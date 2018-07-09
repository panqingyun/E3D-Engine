using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class BoxScript : Component
{
    void Start()
    {
        gameObject.AddComponent<BoxCollider>().CreateRigiBody(10);
    }

    private Vector3 rotate = new Vector3();
    private void Update(float deltaTime)
    {
        //rotate.y += 1f;
        //if (rotate.y >= 360)
        //{
        //    rotate.y = 0;
        //}
        //this.gameObject.Transform.Rotation = rotate;
    }

}
