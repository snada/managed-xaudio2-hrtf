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
using XAudio2Hrtf;

namespace Xaudio2HrtfWPFTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private PositionalSound sound = null;

        public MainWindow()
        {
            InitializeComponent();
            this.sound = new PositionalSound("Resource Files/MonoSound.wav");
            this.sound.Play();

            this.EnvironmentComboBox.ItemsSource = Enum.GetValues(typeof(XAudio2Hrtf.HrtfEnvironment)).Cast<XAudio2Hrtf.HrtfEnvironment>();
            this.EnvironmentComboBox.SelectedIndex = 0;
        }

        private void Thumb_DragDelta(object sender, System.Windows.Controls.Primitives.DragDeltaEventArgs e)
        {
            UIElement thumb = e.Source as UIElement;

            Canvas.SetLeft(thumb, Canvas.GetLeft(thumb) + e.HorizontalChange);
            Canvas.SetTop(thumb, Canvas.GetTop(thumb) + e.VerticalChange);

            float newXPos = this.sound.GetXPosition() + (float)e.HorizontalChange / 200.0f;
            float newZPos = this.sound.GetZPosition() + (float)e.VerticalChange / 200.0f;

            this.sound.SetPosition(newXPos, 0.0f, newZPos);
        }

        private void VolumeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (this.sound != null)
                this.sound.SetVolume((float)e.NewValue);
        }

        private void buttonPlay_Click(object sender, RoutedEventArgs e)
        {
            this.sound.Play();
        }

        private void buttonStop_Click(object sender, RoutedEventArgs e)
        {
            this.sound.Stop();
        }

        private void EnvironmentComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            this.sound.SetEnvironment((HrtfEnvironment)e.AddedItems[0]);
        }
    }
}
