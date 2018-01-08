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
    public partial class EditorContener : UserControl
    {
        public EditorContener()
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

        public string Content 
        {
            set
            {
                text.Text = value;
            }
            get
            {
                return text.Text;
            }
        }
    }
}
