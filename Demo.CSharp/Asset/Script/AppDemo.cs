using E3DEngine;

/// <summary>
/// Entry point
/// </summary>
namespace Game
{
    public delegate void MouseButtonDelegate(MouseButtonInfo mouseInfo);
    public delegate void KeyDelegate(KeyCode keyCode);

    public class AppDemo
    {
        string mainScenePath = "Scene/MainEntry.scene";
        
        public static event MouseButtonDelegate MouseDownEvent;
        public static event MouseButtonDelegate MouseMoveEvent;
        public static event MouseButtonDelegate MouseUpEvent;
        public static event KeyDelegate KeyPressEvent;

        public void Main()
        {
            Scene.LoadScene(Application.ResourcePath + mainScenePath);           
        }

        public void MouseButtonDown(MouseButtonInfo mouseInfo)
        {
            if(MouseDownEvent != null)
            {
                MouseDownEvent(mouseInfo);
            }

        }

        public void MouseButtonUp(MouseButtonInfo mouseInfo)
        {
            if (MouseUpEvent != null)
            {
                MouseUpEvent(mouseInfo);
            }
        }
        
        public void MouseMove(MouseButtonInfo mouseInfo)
        {
            if(MouseMoveEvent != null)
            {
                MouseMoveEvent(mouseInfo);
            }
            
        }

        public void Update(float deltaTime)
        {
          
        }

      
        private void KeyDown(KeyCode keyCode)
        {
            if(KeyPressEvent != null)
            {
                KeyPressEvent(keyCode);
            }
          
        }
    }

}