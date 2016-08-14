#include "XAudio2HrtfCLR.h"

namespace XAudio2Hrtf
{
	PositionalSound::PositionalSound(System::String ^filename)
	{
		nativeObj = new XAudio2HrtfNative();

		pin_ptr<const wchar_t> transformedFileName = PtrToStringChars(filename);

		int returned = nativeObj->LoadFile(transformedFileName);
		
		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}

		returned = nativeObj->Initialize();

		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}
}
