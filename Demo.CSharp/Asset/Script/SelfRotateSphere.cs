using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class SelfRotateSphere : Component
{
    void Start()
    {
    }

    private Vector3 rotate = new Vector3();
    void Update(float dt)
    {
        rotate.y += 1f;
        if (rotate.y >= 360)
        {
            rotate.y = 0;
        }
        this.gameObject.Transform.Rotation = rotate;
    }
}
