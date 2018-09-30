using E3DEngine;

class AppMain : Component
{
    public bool ShowDebug = false;
    public int ShowNumber = 0;

    void Start()
    {
        if (ShowDebug)
        {
            Debug.Log("--------------------------" + ShowNumber.ToString());
        }
    }

    void Update(float deltaTime)
    {
        
    }

    void OnCollisionEnter(Object collisionObject)
    {

    }
}
