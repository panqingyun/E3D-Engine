using E3DEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class CameraController : Component
{
    private Camera MainCamera = null;
    private Vector2 curMousePosition;
    private Vector2 lastMousePosition;
    private float cameraRotateX = 0, cameraRotateY = 0;
    private bool mouseRButtonDown = false, mouseMButtonDown = false;
    private Vector3 cameraRotation;
    private Vector3 curPos = new Vector3();

    void Start()
    {
        Debug.Log("12344");
        Game.App.KeyPressEvent += AppDemo_KeyPressEvent;
        Game.App.MouseDownEvent += AppDemo_MouseDownEvent;
        Game.App.MouseMoveEvent += AppDemo_MouseMoveEvent;
        Game.App.MouseUpEvent += AppDemo_MouseUpEvent;
        MainCamera = (Camera)gameObject;
        cameraRotateX = -MainCamera.Transform.Rotation.x;
        cameraRotateY = -MainCamera.Transform.Rotation.y;
    }

    void Destory()
    {
        Game.App.KeyPressEvent -= AppDemo_KeyPressEvent;
        Game.App.MouseDownEvent -= AppDemo_MouseDownEvent;
        Game.App.MouseMoveEvent -= AppDemo_MouseMoveEvent;
        Game.App.MouseUpEvent -= AppDemo_MouseUpEvent;
    }

    private void AppDemo_MouseUpEvent(MouseButtonInfo mouseInfo)
    {
        if (mouseInfo.mButton == MouseButton.RightButton)
        {
            Debug.LogWarning("MouseButton.RightButton");
            mouseRButtonDown = false;
        }
        else if (mouseInfo.mButton == MouseButton.MiddleButton)
        {
            mouseMButtonDown = false;
        }
    }

    private void AppDemo_MouseMoveEvent(MouseButtonInfo mouseInfo)
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
            gameObject.Transform.Rotation = cameraRotation;
        }
        else if (mouseMButtonDown)
        {
            curPos.SetValue(-curMousePosition.x + lastMousePosition.x, curMousePosition.y - lastMousePosition.y, 0);

            Vector3 dir = MainCamera.GetViewMatrix().Inverse() * curPos;
            dir.Normalize();
            Vector3 newPos = MainCamera.Transform.Position + dir;
            lastMousePosition = curMousePosition;
            gameObject.Transform.Position = newPos;
        }
    }

    private void AppDemo_MouseDownEvent(MouseButtonInfo mouseInfo)
    {
        lastMousePosition.x = mouseInfo.mPositionX;
        lastMousePosition.y = mouseInfo.mPositionY;
        if (mouseInfo.mButton == MouseButton.RightButton)
        {
            mouseRButtonDown = true;
        }
        else if (mouseInfo.mButton == MouseButton.MiddleButton)
        {
            mouseMButtonDown = true;
        }
    }

    Vector3 curCameraPos = new Vector3();
    Vector3 curCameraDir = new Vector3();
    float speed = 0.1f;
    private void AppDemo_KeyPressEvent(KeyCode keyCode)
    {
        curCameraPos = MainCamera.Transform.Position;
        if (keyCode == KeyCode.KeyW)
        {
            curCameraDir = MainCamera.Forward;
            curCameraDir.Normalize();
            gameObject.Transform.Position = curCameraPos + curCameraDir * speed;
        }
        else if (keyCode == KeyCode.KeyS)
        {
            curCameraDir = MainCamera.Forward * -1;
            curCameraDir.Normalize();
            gameObject.Transform.Position = curCameraPos + curCameraDir * speed;
        }
        else if (keyCode == KeyCode.KeyA)
        {
            curCameraDir = MainCamera.Right * -1 * speed;
            curCameraDir.Normalize();
            gameObject.Transform.Position = curCameraPos + curCameraDir * speed;
        }
        else if (keyCode == KeyCode.KeyD)
        {
            curCameraDir = MainCamera.Right * speed;
            curCameraDir.Normalize();
            gameObject.Transform.Position = curCameraPos + curCameraDir * speed;
        }
        else if (keyCode == KeyCode.KeyE)
        {
            curCameraDir = MainCamera.Up * speed;
            curCameraDir.Normalize();
            gameObject.Transform.Position = curCameraPos + curCameraDir * speed;
        }
        else if (keyCode == KeyCode.KeyQ)
        {
            curCameraDir = MainCamera.Up * -1 * speed;
            curCameraDir.Normalize();
            gameObject.Transform.Position = curCameraPos + curCameraDir * speed;
        }
    }
}
