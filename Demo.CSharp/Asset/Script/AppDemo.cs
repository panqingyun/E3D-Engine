using E3DEngine;

/// <summary>
/// Entry point
/// </summary>
namespace Game
{
    public class AppDemo
    {
        string mainScenePath = "Scene/MainEntry.scene";
        Vector2 curMousePosition;
        Vector2 lastMousePosition;
        float cameraRotateX = 0, cameraRotateY = 0;
        bool mouseRButtonDown = false, mouseMButtonDown = false;
        Vector3 cameraRotation;
        Camera MainCamera = null;

        public void Main(string[] args)
        {
            Scene.LoadScene(Application.ResourcePath + mainScenePath);
            MainCamera = Camera.MainCamera;
            cameraRotateX = -MainCamera.Transform.Rotation.x;
            cameraRotateY = -MainCamera.Transform.Rotation.y;            
        }

        public void MouseButtonDown(MouseButtonInfo mouseInfo)
        {
            lastMousePosition.x = mouseInfo.mPositionX;
            lastMousePosition.y = mouseInfo.mPositionY;
            if (mouseInfo.mButton == MouseButton.RightButton)
            {
                mouseRButtonDown = true;
            }
            else if(mouseInfo.mButton == MouseButton.MiddleButton)
            {
                mouseMButtonDown = true;
            }
        }

        public void MouseButtonUp(MouseButtonInfo mouseInfo)
        {
            if (mouseInfo.mButton == MouseButton.RightButton)
            {
                mouseRButtonDown = false;
            }
            else if(mouseInfo.mButton == MouseButton.MiddleButton)
            {
                mouseMButtonDown = false;
            }
        }

        Vector3 curPos = new Vector3();
        public void MouseMove(MouseButtonInfo mouseInfo)
        {
            curMousePosition.x = mouseInfo.mPositionX;
            curMousePosition.y = mouseInfo.mPositionY;

            if (mouseRButtonDown)
            {
                float rotaX = curMousePosition.y - lastMousePosition.y;
                float rotaY = curMousePosition.x - lastMousePosition.x;

                lastMousePosition = curMousePosition;

                cameraRotateX += rotaX * 0.2f;
                cameraRotateY += rotaY * 0.2f;
                cameraRotation.SetValue(-cameraRotateX, -cameraRotateY, 0);
                MainCamera.Transform.Rotation = cameraRotation;
            }
            else if(mouseMButtonDown)
            {
                curPos.SetValue(-curMousePosition.x + lastMousePosition.x, curMousePosition.y - lastMousePosition.y, 0);

                Vector3 dir = MainCamera.GetViewMatrix().Inverse() * curPos;
                dir.Normalize();
                Vector3 newPos = MainCamera.Transform.Position + dir;
                lastMousePosition = curMousePosition;
                MainCamera.Transform.Position = newPos;
            }
        }

        public void Update(float deltaTime)
        {
          
        }

        Vector3 curCameraPos = new Vector3();
        Vector3 curCameraDir = new Vector3();
        float speed = 0.1f;

        private void KeyDown(KeyCode keyCode)
        {
            curCameraPos = MainCamera.Transform.Position;
            if (keyCode == KeyCode.KeyW)
            {
                curCameraDir = MainCamera.Forward ;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir* speed;
            }
            else if(keyCode == KeyCode.KeyS)
            {
                curCameraDir = MainCamera.Forward * -1 ;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir * speed;
            }
            else if(keyCode == KeyCode.KeyA)
            {
                curCameraDir = MainCamera.Right * -1 * speed;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir * speed;
            }
            else if (keyCode == KeyCode.KeyD)
            {
                curCameraDir = MainCamera.Right * speed;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir * speed;
            }
            else if (keyCode == KeyCode.KeyE)
            {
                curCameraDir = MainCamera.Up * speed;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir * speed;
            }
            else if (keyCode == KeyCode.KeyQ)
            {
                curCameraDir = MainCamera.Up * -1 * speed;
                curCameraDir.Normalize();
                MainCamera.Transform.Position = curCameraPos + curCameraDir * speed;
            }
        }
    }

}