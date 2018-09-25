using E3DEngine;

/// <summary>
/// Entry point
/// </summary>
namespace Game
{
    public class AppDemo
    {
        string mainScenePath = "Scene/MainEntry.scene";
        Camera MainCamera = null;

        public void Main(string[] args)
        {
            Scene.LoadScene(Application.ResourcePath + mainScenePath);
            MainCamera = Camera.MainCamera;      
        }

        public void MouseButtonDown(MouseButtonInfo mouseInfo)
        {
           
        }

        public void MouseButtonUp(MouseButtonInfo mouseInfo)
        {
           
        }
        
        public void MouseMove(MouseButtonInfo mouseInfo)
        {
           
        }

        public void Update(float deltaTime)
        {
          
        }
        
        private void KeyDown(KeyCode keyCode)
        {
            
        }
    }

}