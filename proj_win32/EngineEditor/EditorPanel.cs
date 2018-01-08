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
    public partial class EditorPanel : UserControl
    {
        public EditorPanel()
        {
            InitializeComponent();
        }

        public List<Control> ControlList = new List<Control>();

        public void AddControl(Control ctrl)
        {
            ControlList.Add(ctrl);
            // TODO 排序
        }

        public string ShowText
        {
            set
            {
                groupBox.Text = value;
            }
            get
            {
                return groupBox.Text;
            }
        }
    }
}
