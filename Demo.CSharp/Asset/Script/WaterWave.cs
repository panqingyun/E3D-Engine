using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class WaterWave : Component
{
    private Renderer renderer = null;

    void Start()
    {
        renderer = gameObject.Renderer;
        //renderer.Material.UpdateFloatValue("fFarPlane", 4000);
        //renderer.Material.UpdateFloatValue("fNearPlane", 1);
        //renderer.Material.UpdateFloatValue("u_foamAmount", 30);
        //renderer.Material.UpdateFloatValue("u_specularIntensity", 0.1f);
        //renderer.Material.UpdateFloatValue("u_specularPower", 1);
        //renderer.Material.UpdateFloatValue("u_causticIntensity", 1);
        //renderer.Material.UpdateFloat3Value("u_sunColor", 1, 1, 1);
        //renderer.Material.UpdateFloat3Value("u_diffuseColor", 0.6f, 0.6f, 0.6f);
        //renderer.Material.UpdateFloat4Value("u_skyColor", 0.9f, 0.9f, 0.9f, 1);
        //renderer.Material.UpdateFloatValue("u_waterDepth", 50);
    }

    void Update(float dt)
    {
        
    }
}
