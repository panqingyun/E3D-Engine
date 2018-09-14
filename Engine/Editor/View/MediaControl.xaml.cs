using E3DEditor.Common;
using System;
using System.Collections.Generic;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace E3DEditor.View
{
    /// <summary>
    /// MediaControl.xaml 的交互逻辑
    /// </summary>
    public partial class MediaControl : UserControl
    {
        private bool isInPlay = false;
        DispatcherTimer timer = null;
        public MediaControl()
        {
            InitializeComponent();
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromMilliseconds(500);
            timer.Tick += new EventHandler(timer_tick);
        }

        public Uri MediaSource
        {
            set
            {
                mediaElement.Source = value;
            }
        }

        //播放按钮
        private void button_Click(object sender, RoutedEventArgs e)
        {
            if (isInPlay)
            {
                playIcon.Source = new BitmapImage(new Uri(CONST_STRING.PlayIcon, UriKind.Relative));
                mediaElement.Pause();
                timer.Stop();
            }
            else
            {
                playIcon.Source = new BitmapImage(new Uri(CONST_STRING.PauseIcon, UriKind.Relative));
                mediaElement.Play();
                timer.Start();
            }
            isInPlay = !isInPlay;
        }
        
        private void mediaElement_MediaOpened(object sender, RoutedEventArgs e)
        {
            sliderPosition.Maximum = mediaElement.NaturalDuration.TimeSpan.TotalSeconds;
            //媒体文件打开成功
            timer.Start();
        }

        private void timer_tick(object sender, EventArgs e)
        {
            if (!isInPlay)
            {
                timer.Stop();
                sliderPosition.Value = 0;
                return;
            }
            sliderPosition.Value = mediaElement.Position.TotalSeconds;
            if (sliderPosition.Value >= sliderPosition.Maximum)
            {
                stopMedia();
            }
        }

        private void stopMedia()
        {
            mediaElement.Stop();
            playIcon.Source = new BitmapImage(new Uri(CONST_STRING.PlayIcon, UriKind.Relative));
            isInPlay = false;
        }

        //控制视频的位置
        private void sliderPosition_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //mediaElement.Stop();
            mediaElement.Position = TimeSpan.FromSeconds(sliderPosition.Value);
            //mediaElement.Play();
        }
        
    }
}
