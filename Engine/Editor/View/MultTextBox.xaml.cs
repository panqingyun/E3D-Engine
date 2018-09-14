using E3DEditor.Common;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace E3DEditor.View
{
    public class listItem
    {
        public int index;
        public PropertyInfo property;
        public object sourceObject;
    }

    /// <summary>
    /// MultTextBox.xaml 的交互逻辑
    /// </summary>
    public partial class MultTextBox : UserControl
    {
        public MultTextBox()
        {
            InitializeComponent();
        }

        private PropertyInfo _propertyInfo;
        public PropertyInfo inputPropertyInfo
        {
            get
            {
                return _propertyInfo;
            }
            set
            {
                _propertyInfo = value;
                if (SelectObject != null)
                {
                    objectList = inputPropertyInfo.GetValue(SelectObject) as IList;
                    Number = objectList.Count;
                    if (Number != 0)
                    {
                        Content.Text = Number.ToString();
                    }
                    createControl();
                }
            }
        }
        public object SelectObject;
        public double TotalHeight = 0;
        public event EventHandler EnterComplete;

        private IList objectList = null;
        private int _number = 0;
        public int Number
        {
            get
            {
                return _number;
            }
            private set
            {
                _number = value;
            }
        }

        private Type getListContentType(Type listType)
        {
            string fullName = listType.FullName;
            int pos = fullName.IndexOf("[[");
            if (pos == -1)
            {
                return null;
            }
            fullName = fullName.Substring(pos + 2);
            string typeName = fullName.Split(',')[0];

            Type tp = Type.GetType(typeName);

            return tp;
        }

        private void createControl()
        {
            TotalHeight = 30;
            _grid.Children.Clear();
            _grid.RowDefinitions.Clear();
            _grid.ColumnDefinitions.Clear();
            Type contentType = getListContentType(inputPropertyInfo.PropertyType);
            List<PropertyInfo> properties = new List<PropertyInfo>();
            properties.AddRange(contentType.GetProperties());
            var col = new ColumnDefinition();
            col.Width = new GridLength(20);
            _grid.ColumnDefinitions.Add(col);

            for (int i = 0; i < properties.Count; i++)
            {
                var attr = properties[i].GetCustomAttributes(typeof(PropertyFieldAttribute), false);
                if (attr.Length == 0)
                {
                    continue;
                }
                col = new ColumnDefinition();
                col.Width = new GridLength(80);
                _grid.ColumnDefinitions.Add(col);
                _grid.ColumnDefinitions.Add(new ColumnDefinition());

            }
            newLine(VerticalAlignment.Top,5, 0);
            for (int n = 0; n < _number; n++)
            {
                var rowDef = new RowDefinition();
                rowDef.Height = new GridLength(Math.Max(20, this.FontSize * 2));
                _grid.RowDefinitions.Add(rowDef);
                object src = null;
                if (objectList.Count > n)
                {
                    src = objectList[n];
                }
                else
                {
                    src = Activator.CreateInstance(contentType);
                }
                for(int i = 0; i < properties.Count; i++)
                {
                    string name = CONST_STRING.GetTitleText(contentType, properties[i].Name);
                    newTextBlock(name, i);
                    newTextbox(i , properties[i], src, n);
                    newLine(VerticalAlignment.Bottom, 4, 1);
                }
                TotalHeight += 30;
            }
        }

        private void newTextBlock(string text, int i)
        {
            var textBlock = new TextBlock();
            textBlock.Text = text;
            textBlock.Foreground = Brushes.White;
            textBlock.VerticalAlignment = VerticalAlignment.Center;
            textBlock.Margin = new Thickness(4);
            Grid.SetColumn(textBlock, i * 2 + 1);
            Grid.SetRow(textBlock, _grid.RowDefinitions.Count - 1);
            _grid.Children.Add(textBlock);
        }

        private void newTextbox(int col, PropertyInfo prop, object sourceObj, int indexInList)
        {
            var numBox = new NumberTextBox();
            numBox.Background = Brushes.White;
            numBox.Tag = new listItem() { index = indexInList ,property = prop, sourceObject = sourceObj};
            numBox.Text = prop.GetValue(sourceObj).ToString();
            numBox.AllowDrop = false;
            InputMethod.SetIsInputMethodEnabled(numBox, false);
            numBox.LostFocus += TextBox_Loaded;
            Grid.SetColumn(numBox, col * 2 + 2);
            Grid.SetRow(numBox, _grid.RowDefinitions.Count - 1);
            _grid.RowDefinitions[_grid.RowDefinitions.Count - 1].Height = new GridLength(30);
            numBox.Margin = new Thickness(0, 2, 0, 0);
            numBox.VerticalAlignment = VerticalAlignment.Center;
            _grid.Children.Add(numBox);
        }

        private void TextBox_Loaded(object sender, RoutedEventArgs e)
        {
            NumberTextBox tb = sender as NumberTextBox;
            if (tb.Text == "")
            {
                return;
            }
            listItem item = tb.Tag as listItem;

            item.property.SetValue(item.sourceObject, Convert.ChangeType(tb.Text, item.property.PropertyType));

            if (objectList.Count < item.index + 1)
            {
                objectList.Add(item.sourceObject);
            }
            else
            {
                objectList[item.index] = item.sourceObject;
            }
        }
        
        private void newLine(VerticalAlignment aligment, int colSpan, int col)
        {
            Line line = new Line();
            line.Style = (Style)Resources["gridHorizontalLineStyle"];
            Grid.SetColumn(line, col);
            Grid.SetColumnSpan(line, colSpan);
            if (_grid.RowDefinitions.Count == 0)
            {
                Grid.SetRow(line, 0);
            }
            else
            {
                Grid.SetRow(line, _grid.RowDefinitions.Count - 1);
            }
            line.VerticalAlignment = aligment;

            _grid.Children.Add(line);
        }

        private void initObjectList()
        {
            objectList = inputPropertyInfo.GetValue(SelectObject) as IList;
            objectList.Clear();
        }

        private void Content_KeyUp(object sender, KeyEventArgs e)
        {
            if (Content.Text == "")
                return;
            if (e.Key == Key.Enter)
            {
                Number = Convert.ToInt32(Content.Text);
                initObjectList();
                createControl();
                NumberParamEventArgs _e = new NumberParamEventArgs();
                _e.InputNumber = Number;
                EnterComplete?.Invoke(this, _e);
            }
        }
    }
}
