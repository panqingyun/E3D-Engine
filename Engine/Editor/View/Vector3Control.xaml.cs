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
    }
}
