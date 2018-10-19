using E3DEngine;

class AppMain : Component
{
    public bool ShowDebug = false;
    public int ShowNumber = 0;

    void Start()
    {
        if (ShowDebug)
        {
            Debug.LogError("-------------gdsjfjfjkshfruihfih vhlfvnjkbnvbkjjjjjjjjjjjjjjjjjjjjjjjjj jjjjjjjjjjjjjjjjjjjnvdssssss ssssssssssssssfxvvvvccccccccccccccccc ccccccccccccccccccccccnjkdsaaaaa aaaaaaaaaaaaaaa aaaaaaaaaaa aaaaaaaaa anjjjjjjjjjjjcxxxxvvv nmsdfuiiiwereiwafhdjsksssssssssssssssssssssssssssssssssssssss-------------" + ShowNumber.ToString());
        }
    }

    void Update(float deltaTime)
    {
        
    }

}
