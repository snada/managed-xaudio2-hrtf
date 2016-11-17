using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using XAudio2Hrtf;

namespace XAudio2HrtfCLRUnitTestProject
{
    [TestClass]
    public class PositionalSoundUnitTest
    {
        [TestMethod]
        public void NewPositionalSound()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");
        }

        [TestMethod]
        public void NewPositionalSoundWithLoopCount()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav", 1);
        }

        [TestMethod]
        public void DefaultEnvironmentIsSmall()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            Assert.AreEqual(HrtfEnvironment.Small, p.Environment);
        }

        [TestMethod]
        public void NewPositionalSoundWithLoopCountAndEnvironment()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav", 1, HrtfEnvironment.Large);
        }

        [TestMethod]
        public void NewPositionalSoundVolumeIsOne()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            Assert.AreEqual(1, p.Volume);
        }

        [TestMethod]
        public void NewPositionalSoundPositionIsOrigin()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            Assert.AreEqual(0, p.X);
            Assert.AreEqual(0, p.Y);
            Assert.AreEqual(0, p.Z);
        }

        [TestMethod]
        public void XProperty()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            p.X = 1;

            Assert.AreEqual(1, p.X);
        }

        [TestMethod]
        public void YProperty()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            p.Y = 2;

            Assert.AreEqual(2, p.Y);
        }

        [TestMethod]
        public void ZProperty()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            p.Z = 3;

            Assert.AreEqual(3, p.Z);
        }

        [TestMethod]
        public void SetPosition()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            p.X = 1;
            p.Y = 2;
            p.Z = 3;

            Assert.AreEqual(1, p.X);
            Assert.AreEqual(2, p.Y);
            Assert.AreEqual(3, p.Z);
        }

        [TestMethod]
        public void VolumeProperty()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            p.Volume = 0.5f;

            Assert.AreEqual(0.5f, p.Volume);
        }

        [TestMethod]
        public void EnvironmentProperty()
        {
            PositionalSound p = new PositionalSound("Resource Files/MonoSound.wav");

            p.Environment = HrtfEnvironment.Outdoors;

            Assert.AreEqual(HrtfEnvironment.Outdoors, p.Environment);
        }
    }
}
