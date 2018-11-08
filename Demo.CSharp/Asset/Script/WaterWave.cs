using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class WaterWave : Component
{
    private float totalTime = 0;

    private Renderer renderer = null;

    void Start()
    {
        renderer = gameObject.Renderer;
    }

    void Update(float dt)
    {
        totalTime += dt;
        if(totalTime > 1024)
        {
            totalTime = 0;
        }
        if(renderer == null)
        {
            return;
        }
        renderer.Material.UpdateFloatValue("time", totalTime);
    }
}
