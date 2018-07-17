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

    void OnCollisionEnter(Object collisionObject)
    {

    }
}
