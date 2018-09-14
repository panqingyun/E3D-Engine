using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace E3DEditor.View
{
    /// <summary>
    /// AutoSizeImage.xaml 的交互逻辑
    /// </summary>
    public partial class AutoSizeImage : UserControl
    {
        public AutoSizeImage()
        {
            InitializeComponent();
        }

        public ImageSource ImageSource
        {
            get { return (ImageSource)GetValue(ImageSourceProperty); }
            set { SetValue(ImageSourceProperty, value); }
        }
        public static readonly DependencyProperty ImageSourceProperty = DependencyProperty.Register("ImageSource",
            typeof(ImageSource), typeof(AutoSizeImage), new PropertyMetadata(defaultValue: null, propertyChangedCallback: null, coerceValueCallback: imageSourceChange));

        public Stretch ImageStretch
        {
            get;set;
        }
        public static readonly DependencyProperty ImageStretchPaoperty = DependencyProperty.Register("ImageStretch",
            typeof(Stretch), typeof(AutoSizeImage), new PropertyMetadata(defaultValue: Stretch.None, propertyChangedCallback: null, coerceValueCallback: stretchChangeCallBack));
        
        private static object stretchChangeCallBack(DependencyObject d, object baseValue)
        {
            if (baseValue != null)
            {
                AutoSizeImage control = d as AutoSizeImage;
                control.img.Stretch = (Stretch)baseValue;
            }
            return baseValue;
        }

        private static object imageSourceChange(DependencyObject d, object baseValue)
        {
            if (baseValue != null)
            {
                AutoSizeImage control = d as AutoSizeImage;
                control.img.Source = baseValue as ImageSource;
                if (control.img.Source.Width > control.img.Source.Height)
                {
                    control.Width = (control.img.Source.Width / control.img.Source.Height) * control.Height;
                }
                else
                {
                    control.Height = (control.img.Source.Height / control.img.Source.Width) * control.Width;
                }
            }
            return baseValue;
        }
    }
}
