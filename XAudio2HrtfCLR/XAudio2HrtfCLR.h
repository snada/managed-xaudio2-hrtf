#pragma once
#include "XAudio2HrtfNative.h"
#include <vcclr.h>

namespace XAudio2Hrtf
{
	/// <summary>
	/// Enum abstracting the concept of environment in which the sound is played
	/// </summary>
	public enum class HrtfEnvironment
	{
		/// <summary>
		/// Small room environment
		/// </summary>
		Small = 0,

		/// <summary>
		/// Medium sized room environment
		/// </summary>
		Medium,

		/// <summary>
		/// Large room environment
		/// </summary>
		Large,

		/// <summary>
		/// Outdoors environment
		/// </summary>
		Outdoors
	};

	/// <summary>
	/// Positional sound with HRTF effect on top of XAudio2
	/// </summary>
	public ref class PositionalSound
	{
	public:
		/// <summary>
		/// Creates an infinite-looping positional sound
		/// </summary>
		/// <param name="filename">Path of a 48k samplerate mono wav file</param>
		PositionalSound(System::String ^filename);
		
		/// <summary>
		/// Creates a positional sound with a given number of loops
		/// </summary>
		/// <param name="filename">Path of a 48k samplerate mono wav file</param>
		/// <param name="loopCount">Number of loops played before this sounds stops automatically. Any value greater than 254 will be treated as inifite loops</param>
		PositionalSound(System::String ^filename, int loopCount);
		
		/// <summary>
		/// Creates a positional sound with a given number of loops and a given environment
		/// </summary>
		/// <param name="filename">Path of a 48k samplerate mono wav file</param>
		/// <param name="loopCount">Number of loops played before this sounds stops automatically. Any value greater than 254 will be treated as inifite loops</param>
		/// <param name="environment">HrtfEnvironment enum indicating the type/size of room this sound il played into, can be small, medium, large, or outdoors</param>
		PositionalSound(System::String ^filename, int loopCount, HrtfEnvironment environment);
		
		~PositionalSound();
		!PositionalSound();
		
		/// <summary>
		/// Start reproducing this positional sound
		/// </summary>
		void Play();

		/// <summary>
		/// Stop reproducing this positional sound
		/// </summary>
		void Stop();

		/// <summary>
		/// Sets the environment of this positional sound
		/// </summary>
		/// <param name="environment">HrtfEnvironment enum indicating the desided environment</param>
		void SetEnvironment(HrtfEnvironment environment);
		
		/// <summary>
		/// Changes position of this positional sound, relative to a origin based listener.
		/// </summary>
		/// <param name="x">Position on x axis</param>
		/// <param name="y">Position on y axis</param>
		/// <param name="z">Position on z axis</param>
		void SetPosition(float x, float y, float z);
		
		/// <summary>
		/// Changes volume value of this positional sound. 0 is silence, 1 full volume without any gain or attenuation. Negative levels can be used to invert audio phase.
		/// </summary>
		/// <param name="value">New volume value</param>
		void SetVolume(float value);
		
		/// <summary>
		/// Gets or sets Volume value of this positional sound. 0 is silence, 1 full volume without any gain or attenuation. Negative levels can be used to invert audio phase.
		/// </summary>
		property float Volume {
			float get()
			{
				return this->_volume;
			}

			void set(float value)
			{
				this->_volume = value;
				this->SetVolume(value);
			}
		}

		/// <summary>
		/// Gets or sets position on X axis of this positional sound, relative to a origin based listener.
		/// </summary>
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

		/// <summary>
		/// Gets or sets position on Y axis of this positional sound, relative to a origin based listener.
		/// </summary>
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
		
		/// <summary>
		/// Gets or sets position on Z axis of this positional sound, relative to a origin based listener.
		/// </summary>
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
