using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EngineEditor
{
    public partial class PositionContener : UserControl
    {
        public PositionContener()
        {
            InitializeComponent();
        }

        public string ShowText
        {
            set
            {
                name.Text = value;
            }
            get
            {
                return name.Text;
            }
        }

        public float XPosition
        {
            set
            {
                X.Text = value.ToString();
            }
            get
            {
                return (float)Convert.ToDouble(X.Text);
            }
        }

        public float YPosition
        {
            set
            {
                Y.Text = value.ToString();
            }
            get
            {
                return (float)Convert.ToDouble(Y.Text);
            }
        }

        public float ZPosition
        {
            set
            {
                Z.Text = value.ToString();
            }
            get
            {
                return (float)Convert.ToDouble(Z.Text);
            }
        }

        private void X_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != '\b' && (e.KeyChar > '9' || e.KeyChar < '0'))
            {
                e.Handled = true;
            }
        }


    }
}
