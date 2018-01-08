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
    public partial class BoolenContener : UserControl
    {
        public BoolenContener()
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

        public string YesText
        {
            set
            {
                yes.Text = value;
            }
        }

        public string NoText
        {
            set
            {
                no.Text = value;
            }
        }

        public bool IsYes
        {
            set
            {
                yes.Checked = value;
                no.Checked = !value;
            }
            get
            {
                return yes.Checked;
            }
        }
    }

}
