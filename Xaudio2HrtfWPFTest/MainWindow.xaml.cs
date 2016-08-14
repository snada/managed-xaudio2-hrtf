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
        }

        private void TestButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                this.sound = new PositionalSound("Resource Files/MonoSound.wav");
                MessageBox.Show("Everything fine.");
            }
            catch(Exception err)
            {
                var inner = err.InnerException;
                var lol = err.GetBaseException();
                MessageBox.Show("WE HAVE A NATIVE ERROR!: " + err.Message);
            }
        }
    }
}
