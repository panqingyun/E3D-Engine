using System;
using System.Collections.Generic;
using System.Linq;
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
    /// <summary>
    /// NumberTextBox.xaml 的交互逻辑
    /// </summary>
    public partial class NumberTextBox : UserControl
    {
        public NumberTextBox()
        {
            InitializeComponent();
            tbx.PreviewKeyUp += Tbx_PreviewKeyUp;
        }

        private void Tbx_PreviewKeyUp(object sender, KeyEventArgs e)
        {
            _KeyUp?.Invoke(this, e);
        }

        public event KeyEventHandler _KeyUp;

        public string Text
        {
            get { return tbx.Text; }
            set { tbx.Text = value; }
        }

        public int Number
        {
            get
            {
                return Convert.ToInt32(tbx.Text);
            }
        }

        public string HintText
        {
            get { return (string)GetValue(HintTextProperty); }
            set { SetValue(HintTextProperty, value); }
        }
        public static readonly DependencyProperty HintTextProperty = DependencyProperty.Register("HintText", 
            typeof(string), typeof(NumberTextBox), new PropertyMetadata(defaultValue:"", propertyChangedCallback : null, 
                coerceValueCallback : hintTextCoerceValueCallback));
        
        private static object hintTextCoerceValueCallback(DependencyObject d, object baseValue)
        {
            if (baseValue != null)
            {
                var control = d as NumberTextBox;
                var hint = baseValue.ToString();
                control.tbx.Tag = hint;
                return baseValue.ToString();
            }
            return baseValue;
        }

        private void tbx_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            Regex re = new Regex(@"^[-+]?\d+(\.\d+)?$");
            e.Handled = re.IsMatch(e.Text);
        }

        private void tbx_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key >= Key.NumPad0 && e.Key <= Key.NumPad9) ||
                           (e.Key >= Key.D0 && e.Key <= Key.D9) ||
                           e.Key == Key.Back || e.Key == Key.OemPeriod || e.Key == Key.Decimal ||
                           e.Key == Key.Left || e.Key == Key.Right || e.Key == Key.Enter)
            {
                if (e.KeyboardDevice.Modifiers != ModifierKeys.None)
                {
                    e.Handled = true;
                }
            }
            else
            {
                e.Handled = true;
            }
        }
    }
}
