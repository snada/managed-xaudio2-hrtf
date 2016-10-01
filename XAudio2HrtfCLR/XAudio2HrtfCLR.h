#pragma once
#include "XAudio2HrtfNative.h"
#include <vcclr.h>

namespace XAudio2Hrtf
{
	public enum class HrtfEnvironment
	{
		Small = 0,
		Medium,
		Large,
		Outdoors
	};

	public ref class PositionalSound
	{
	public:
		PositionalSound(System::String ^filename);
		PositionalSound(System::String ^filename, int loopCount);
		PositionalSound(System::String ^filename, int loopCount, HrtfEnvironment environment);
		~PositionalSound();
		!PositionalSound();
		void Play();
		void Stop();
		void SetEnvironment(HrtfEnvironment environment);
		void SetPosition(float x, float y, float z);
		void SetVolume(float value);

		property float Volume {
			float get()
			{
				return this->Volume;
			}

			void set(float value)
			{
				this->_volume = value;
				this->SetVolume(value);
			}
		}

		property float X {
			float get()
			{
				return this->_x;
			}

			void set(float value)
			{
				this->_x = value;
				this->SetPosition(this->X, this->Y, this->Z);
			}
		}
		property float Y {
			float get()
			{
				return this->_y;
			}

			void set(float value)
			{
				this->_y = value;
				this->SetPosition(this->X, this->Y, this->Z);
			}
		}
		property float Z {
			float get()
			{
				return this->_z;
			}

			void set(float value)
			{
				this->_z = value;
				this->SetPosition(this->X, this->Y, this->Z);
			}
		}

	private:
		XAudio2HrtfNative* _nativeObj;
		HrtfEnvironment _environment;
		float _x, _y, _z = 0.0f;
		float _volume = 1.0f;
	};
}
