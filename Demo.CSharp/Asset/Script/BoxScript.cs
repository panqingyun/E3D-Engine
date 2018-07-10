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

    private void Update(float deltaTime)
    {
        
    }

}
