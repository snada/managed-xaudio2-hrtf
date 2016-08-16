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
		PositionalSound(System::String ^filename, HrtfEnvironment environment);
		void Play();
		void Stop();
		void SetEnvironment(HrtfEnvironment environment);
		void SetPosition(float x, float y, float z);
		void SetVolume(float value);
		float GetXPosition();
		float GetYPosition();
		float GetZPosition();
	private:
		XAudio2HrtfNative* _nativeObj;
		HrtfEnvironment _environment;
		float x, y, z = 0.0f;
	};
}
