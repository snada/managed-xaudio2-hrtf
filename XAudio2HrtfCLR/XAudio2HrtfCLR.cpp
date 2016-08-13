#include "XAudio2HrtfCLR.h"

namespace XAudio2Hrtf
{
	XAudio2HrtfCLR::XAudio2HrtfCLR()
	{
		nativeObj = new XAudio2HrtfNative();
	}

	float XAudio2HrtfCLR::Testing()
	{
		return nativeObj->Testing();
	}
}