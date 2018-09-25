using E3DEngine;

class AppMain : Component
{
    public bool ShowDebug
    {
        get; set;
    }

    public int ShowNumber
    {
        get;set;
    }

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
