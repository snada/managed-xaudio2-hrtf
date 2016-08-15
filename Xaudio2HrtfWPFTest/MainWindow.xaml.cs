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
        }

        private void TestButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                this.sound.SetPosition(14, 0, 0);
            }
            catch(Exception err)
            {
                var inner = err.InnerException;
                var lol = err.GetBaseException();
                MessageBox.Show("WE HAVE A NATIVE ERROR!: " + err.Message);
            }
        }

        private void Thumb_DragDelta(object sender, System.Windows.Controls.Primitives.DragDeltaEventArgs e)
        {
            UIElement thumb = e.Source as UIElement;

            Canvas.SetLeft(thumb, Canvas.GetLeft(thumb) + e.HorizontalChange);
            Canvas.SetTop(thumb, Canvas.GetTop(thumb) + e.VerticalChange);

            float newXPos = this.sound.GetXPosition() + (float)e.HorizontalChange / 100.0f;
            float newZPos = this.sound.GetZPosition() + (float)e.VerticalChange / 100.0f;

            this.sound.SetPosition(newXPos, 0, newZPos);

            Console.WriteLine(newXPos.ToString());
        }
    }
}
