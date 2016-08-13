#pragma once

#include "XAudio2HrtfNative.h"

namespace XAudio2Hrtf
{
	public ref class XAudio2HrtfCLR
	{
	public:
		XAudio2HrtfCLR();
		float Testing();
	private:
		XAudio2HrtfNative* nativeObj;
	};
}
