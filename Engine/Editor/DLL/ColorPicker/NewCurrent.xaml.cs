using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using ColorPicker.ExtensionMethods;

namespace ColorPicker
{
    /// <summary>
    /// Interaction logic for NewCurrent.xaml
    /// </summary>
    public partial class NewCurrent : UserControl
    {
        public static Type ClassType
        {
            get { return typeof(NewCurrent); }
        }

        public NewCurrent()
        {
            InitializeComponent();
        }

        #region NewColor

        public static DependencyProperty NewColorProperty = DependencyProperty.Register("NewColor", typeof(Color), ClassType, 
            new FrameworkPropertyMetadata(Colors.Gray, new PropertyChangedCallback(OnNewColorChanged)));
         [Category("ColorPicker")]
        public Color NewColor
        {
            get
            {
                return (Color)GetValue(NewColorProperty);
            }
            set
            {
                SetValue(NewColorProperty, value);
            }
        }

        private static void OnNewColorChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var nc = (NewCurrent)d;
            nc.rNew.Fill = new SolidColorBrush(((Color)e.NewValue).WithAlpha(nc.Alpha));

        }

        #endregion

        #region CurrentColor

        public static DependencyProperty CurrentColorProperty = DependencyProperty.Register("CurrentColor", typeof(Color), ClassType, 
            new FrameworkPropertyMetadata(Colors.Black, new PropertyChangedCallback(OnCurrentColorChanged)));

        /// <summary>
        /// The color being selected 
        /// </summary>
         [Category("ColorPicker")]
        public Color CurrentColor
        {
            get
            {
                return (Color)GetValue(CurrentColorProperty);
            }
            set
            {
                SetValue(CurrentColorProperty, value);
            }
        }

        private static void OnCurrentColorChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var nc = (NewCurrent) d;
            nc.rCurrent.Fill = new SolidColorBrush((Color) e.NewValue);
        }

        #endregion

        #region Alpha

        public static DependencyProperty AlphaProperty = DependencyProperty.Register("Alpha", typeof(byte), ClassType, new PropertyMetadata((byte)255, new PropertyChangedCallback(OnAlphaChanged)));
        /// <summary>
        /// The Alpha Component of the currrent color
        /// </summary>
          [Category("ColorPicker")]
        public byte Alpha
        {
            get
            {
                return (byte)GetValue(AlphaProperty);
            }
            set
            {
                SetValue(AlphaProperty, value);
            }
        }

        private static void OnAlphaChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var nc = (NewCurrent)d;
            nc.rNew.Fill = new SolidColorBrush(nc.NewColor.WithAlpha(Convert.ToByte(e.NewValue)));
        }

        #endregion

        //public bool ShowLabels { get; set; }

        #region orientation
        
        public static readonly DependencyProperty OrientationProperty = DependencyProperty.Register("Orientation", typeof(Orientation), typeof(NewCurrent),
            new FrameworkPropertyMetadata(Orientation.Vertical, FrameworkPropertyMetadataOptions.AffectsMeasure, OnOrientationChanged));

        private static void OnOrientationChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var or = (Orientation) e.NewValue ;
            if (or != (Orientation)e.OldValue)
            {
                var newCurrent = (NewCurrent) d;
                if (or == Orientation.Horizontal)
                {
                    newCurrent.SetOrientationToHorizontal();
                }
                else
                {
                    newCurrent.SetOrientationToVertical();
                }
            }


        }
        private void SetOrientationToHorizontal()
        {
            var star = new GridLength(50, GridUnitType.Star);
            var auto = GridLength.Auto;

            LayoutRoot.ColumnDefinitions[0].Width = star;
            LayoutRoot.ColumnDefinitions[1].Width = star;

            LayoutRoot.RowDefinitions[0].Height = auto;
            LayoutRoot.RowDefinitions[1].Height = star;
            LayoutRoot.RowDefinitions[2].Height = auto;
            LayoutRoot.RowDefinitions[3].Height = auto;

            tbCurrent.SetValue(Grid.RowProperty ,  0);
            tbCurrent.SetValue(Grid.ColumnProperty , 0);

            tbNew.SetValue(Grid.RowProperty,0);
            tbNew.SetValue(Grid.ColumnProperty, 1);


            rNew.SetValue(Grid.RowProperty, 1);
            rNew.SetValue(Grid.ColumnProperty, 1);
            rNewBG.SetValue(Grid.RowProperty, 1);
            rNewBG.SetValue(Grid.ColumnProperty, 1);

            rCurrent.SetValue(Grid.RowProperty, 1);
            rCurrent.SetValue(Grid.ColumnProperty, 0);
            rCurrentBG.SetValue(Grid.RowProperty, 1);
            rCurrentBG.SetValue(Grid.ColumnProperty, 0);
        }

        private void SetOrientationToVertical()
        {
            var star = new GridLength(35, GridUnitType.Star);
            var auto = GridLength.Auto;

            LayoutRoot.ColumnDefinitions[0].Width = star;
            LayoutRoot.ColumnDefinitions[1].Width = auto;

            LayoutRoot.RowDefinitions[0].Height = auto;
            LayoutRoot.RowDefinitions[1].Height = star;
            LayoutRoot.RowDefinitions[2].Height = star;
            LayoutRoot.RowDefinitions[3].Height = auto;

           
            tbNew.SetValue(Grid.RowProperty, 0);
            tbNew.SetValue(Grid.ColumnProperty, 0);

            rNew.SetValue(Grid.RowProperty, 1);
            rNew.SetValue(Grid.ColumnProperty, 0);
            rNewBG.SetValue(Grid.RowProperty, 1);
            rNewBG.SetValue(Grid.ColumnProperty, 0);

            rCurrent.SetValue(Grid.RowProperty, 2);
            rCurrent.SetValue(Grid.ColumnProperty, 0);
            rCurrentBG.SetValue(Grid.RowProperty, 2);
            rCurrentBG.SetValue(Grid.ColumnProperty, 0);


            tbCurrent.SetValue(Grid.RowProperty, 3);
            tbCurrent.SetValue(Grid.ColumnProperty, 0);
        
        


        }

        [Category("ColorPicker")]
        public Orientation Orientation
        {
            get { return (Orientation) GetValue(OrientationProperty); }
            set { SetValue(OrientationProperty, value); }
        }

#endregion


    }
}
