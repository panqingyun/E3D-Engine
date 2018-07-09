using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class MeshScript : Component
{
    void Awake()
    {
        Collider collider = gameObject.AddComponent<MeshCollider>();
        collider.CreateRigiBody(0);
    }
}
