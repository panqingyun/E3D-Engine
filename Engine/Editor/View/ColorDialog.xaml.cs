using ColorPicker;
using ColorPicker.ColorModels.HSB;
using ColorPicker.ExtensionMethods;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace E3DEditor.View
{
    /// <summary>
    /// ColorDialog.xaml 的交互逻辑
    /// </summary>
    public partial class ColorDialog : Window
    {
        public ColorDialog()
        {
            InitializeComponent();
            SetBinding(SelectedColorProperty, "Color");
            DataContext = colorSelector;
            colorSelector.ColorChanged += colorSelector_ColorChanged;
            Deactivated += ColorDialog_Deactivated;
        }

        private void ColorDialog_Deactivated(object sender, EventArgs e)
        {
            try
            {
                Close();
            }
            catch { }
        }
        
        void alphaDisplay_AlphaChanged(object sender, ColorPicker.EventArgs<byte> e)
        {
            SetValue(SelectedColorProperty, SelectedColor.WithAlpha(e.Value));
            if (SelectedColorChanged != null)
            {
                SelectedColorChanged(this, new EventArgs<Color>(SelectedColor));
            }
        }

        void colorSelector_ColorChanged(object sender, ColorPicker.EventArgs<Color> e)
        {
            SetValue(SelectedColorProperty, e.Value.WithAlpha(alphaDisplay.Alpha));
            if (SelectedColorChanged != null)
            {
                SelectedColorChanged(this, new EventArgs<Color>(SelectedColor));
            }
        }

        public static Type ClassType
        {
            get { return typeof(ColorDialog); }
        }
        #region InitialColor

        public static DependencyProperty InitialColorProperty = DependencyProperty.Register("InitialColor", typeof(Color), ClassType,
            new FrameworkPropertyMetadata(Colors.Transparent, FrameworkPropertyMetadataOptions.BindsTwoWayByDefault, OnInitialColorChanged));
        [Category("ColorPicker")]
        public Color InitialColor
        {
            get
            {
                return (Color)GetValue(InitialColorProperty);
            }
            set
            {
                SetValue(InitialColorProperty, value);
            }
        }


        private static void OnInitialColorChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var cpf = (ColorDialog)d;
            cpf.newCurrent.CurrentColor = (Color)e.NewValue;
            cpf.SelectedColor = cpf.newCurrent.CurrentColor;
            if (cpf.SelectedColorChanged != null)
            {
                cpf.SelectedColorChanged(cpf, new EventArgs<Color>((Color)e.NewValue));
            }
        }


        #endregion

        public event EventHandler<EventArgs<Color>> SelectedColorChanged;
        #region SelectedColor

        public static DependencyProperty SelectedColorProperty = DependencyProperty.Register("SelectedColor", typeof(Color), ClassType,
            new FrameworkPropertyMetadata(Colors.Transparent, FrameworkPropertyMetadataOptions.BindsTwoWayByDefault, OnSelectedColorChanged));
        [Category("ColorPicker")]
        public Color SelectedColor
        {
            get
            {
                return (Color)GetValue(SelectedColorProperty);
            }
            set
            {
                SetValue(SelectedColorProperty, value);
            }
        }


        private static void OnSelectedColorChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var cpf = (ColorDialog)d;
            var color = (Color)e.NewValue;
            cpf.colorSelector.Color = color;
            cpf.alphaDisplay.Alpha = color.A;

        }


        #endregion

        [Category("ColorPicker")]
        public ColorSelector.ESelectionRingMode SelectionRingMode
        {
            get { return colorSelector.SelectionRingMode; }
            set { colorSelector.SelectionRingMode = value; }
        }
    }
}
