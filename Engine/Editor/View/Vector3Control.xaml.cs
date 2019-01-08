using System;
using System.Reflection;
using System.Windows.Controls;
using System.Windows.Input;

namespace E3DEditor.View
{
    public delegate void TextChangeDelegate(string text);
    /// <summary>
    /// Vector3Control.xaml 的交互逻辑
    /// </summary>
    public partial class Vector3Control : UserControl
    {
        public float X
        {
            set
            {
                x.Text = value.ToString();
            }
            get
            {
                return Convert.ToSingle(x.Text);
            }
        }

        public float Y
        {
            set
            {
                y.Text = value.ToString();
            }
            get
            {
                return Convert.ToSingle(y.Text);
            }
        }

        public float Z
        {
            set
            {
                z.Text = value.ToString();
            }
            get
            {
                return Convert.ToSingle(z.Text);
            }
        }
        private E3DEngine.Vector3 vec = new E3DEngine.Vector3();

        public object SelectObject;
        public PropertyInfo ValueProperty;
        private bool _mouseDown = false;
        private double _mouseXpos = 0;
        private int operatTitle;// x = 0, y = 1, z =2
        private float curValue = 0;
        private E3DEngine.Vector3 _valueVector;
        public E3DEngine.Vector3 ValueObject
        {
            set
            {
                _valueVector = value;
                X = value.x;
                Y = value.y;
                Z = value.z;
                vec.x = X; vec.y = Y; vec.z = Z;
            }
        }

        public Vector3Control()
        {
            InitializeComponent();
        }

        public event KeyEventHandler EnterKeyDown;
        public TextChangeDelegate TextChange;

        private void _TextInput(object sender, TextCompositionEventArgs e)
        {
            TextBox tbx = sender as TextBox;
            TextChange?.Invoke(tbx.Text);
        }

        private void _PreviewKeyUp(object sender, KeyEventArgs e)
        {
            if (Key.Enter != e.Key)
                return;

            vec.x = X;
            vec.y = Y;
            vec.z = Z;
            EnterKeyDown?.Invoke(this, e);
            if (SelectObject != null)
            {
                ValueProperty.SetValue(SelectObject, vec);
            }
        }

        private void TextBlock_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            TextBlock txt = sender as TextBlock;
            if(txt == xTitle)
            {
                operatTitle = 0;
                curValue = vec.x;
            }
            else if(txt == yTitle)
            {
                operatTitle = 1;
                curValue = vec.y;
            }
            else if(txt == zTitle)
            {
                operatTitle = 2;
                curValue = vec.z;
            }
            _mouseDown = true;
            txt.CaptureMouse();
            _mouseXpos = e.GetPosition(null).X;
        }

        private void TextBlock_MouseMove(object sender, MouseEventArgs e)
        {
            if(_mouseDown)
            {
                double x = e.GetPosition(null).X;
                curValue += (float)(x - _mouseXpos) / 10.0f;
                if(operatTitle == 0)
                {
                    vec.x = curValue;
                }
                else if(operatTitle == 1)
                {
                    vec.y = curValue;
                }
                else if(operatTitle == 2)
                {
                    vec.z = curValue;
                }
                EnterKeyDown?.Invoke(this, null);
                if (SelectObject != null)
                {
                    ValueProperty.SetValue(SelectObject, vec);
                }
                _mouseXpos = x;
            }
        }

        private void TextBlock_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            TextBlock txt = sender as TextBlock;
            _mouseDown = false;
            txt.ReleaseMouseCapture();
        }
    }
}
