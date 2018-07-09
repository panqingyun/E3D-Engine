using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class SphereScript : Component
{
    void Start()
    {
        gameObject.AddComponent<SphereCollider>().CreateRigiBody(15);
    }
}
