#pragma once
#include "XAudio2HrtfNative.h"
#include <vcclr.h>

namespace XAudio2Hrtf
{
	public ref class PositionalSound
	{
	public:
		PositionalSound(System::String ^filename);
		void Play() {}
		void Stop() {}
		void SetPosition(float x, float y, float z) {}
	private:
		XAudio2HrtfNative* nativeObj;
	};
}
