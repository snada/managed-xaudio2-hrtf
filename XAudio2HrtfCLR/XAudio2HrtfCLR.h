#pragma once
#include "XAudio2HrtfNative.h"
#include <vcclr.h>

namespace XAudio2Hrtf
{
	public ref class PositionalSound
	{
	public:
		PositionalSound(System::String ^filename);
		void Play();
		void Stop();
		void SetPosition(float x, float y, float z);
		void SetVolume(float value);
		float GetXPosition();
		float GetYPosition();
		float GetZPosition();
	private:
		XAudio2HrtfNative* nativeObj;
		float x, y, z = 0.0f;
	};
}
