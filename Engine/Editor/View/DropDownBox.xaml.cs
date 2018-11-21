using System.Collections;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace E3DEditor.View
{
    public delegate void DorpDownEventHander(object sender, bool isDown);
    public delegate void DropDwonSelectEventHander(object sender, string selectText);
    /// <summary>
    /// DropDownBox.xaml 的交互逻辑
    /// </summary>
    public partial class DropDownBox : UserControl
    {
        public event DorpDownEventHander DorpDownEvent;
        public event DropDwonSelectEventHander DropDownSelected;

        public void ReplaceNewTextBox(string text)
        {
            textContent.Children.Remove(textBox);
            textBox = null;
            NumberTextBox number = new NumberTextBox();
            number.HorizontalAlignment = HorizontalAlignment.Stretch;
            number.VerticalAlignment = VerticalAlignment.Stretch;
            textContent.Children.Add(number);
            textBox = number;
            textBox.Text = text;
            Panel.SetZIndex(textBox, -1);
            textBox.AllowDrop = true;
            textBox.Background = Brushes.Transparent;
        }

        public DropDownBox()
        {
            InitializeComponent();
        }

        public double _height = 30;

        public string Title
        {
            get { return titleName.Text; }
            set { titleName.Text = value; }
        }

        public string SelectText
        {
            get { return textBox.Text; }
            set { textBox.Text = value; }
        }

        public object SelectedItem
        {
            get { return tableList.SelectedItem; }
            set { tableList.SelectedItem = value; }
        }

        public IEnumerable ItemSource
        {
            get { return tableList.ItemsSource; }
            set { tableList.ItemsSource = value; }
        }

        public ItemCollection Items
        {
            get
            {
                return tableList.Items;
            }
        }

        private bool isDown = true;
        private void ToggleButton_Click(object sender, RoutedEventArgs e)
        {
            setDownUp();
            DorpDownEvent?.Invoke(this, isDown);
        }

        private void setDownUp()
        {
            if (isDown)
            {
                toggle.Style = Resources["stlFlipToggleButton"] as Style;
                tableList.Visibility = Visibility.Visible;

                Height = 500;
            }
            else
            {
                toggle.Style = Resources["stlToggleButton"] as Style;
                tableList.Visibility = Visibility.Hidden;
                Height = _height;
            }
            isDown = !isDown;
        }

        private void tableList_Selected(object sender, RoutedEventArgs e)
        {
            //NodeBase node = tableList.SelectedItem as NodeBase;
            //textBox.Text = node.ID.ToString();
            setDownUp();
            DropDownSelected?.Invoke(this, textBox.Text);
        }
    }
}
