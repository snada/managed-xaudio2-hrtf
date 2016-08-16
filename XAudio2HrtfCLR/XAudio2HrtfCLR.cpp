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

	void PositionalSound::Play()
	{
		nativeObj->Play();
	}

	void PositionalSound::SetVolume(float value)
	{
		int returned = nativeObj->SetVolume(value);

		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}

	void PositionalSound::SetPosition(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		int returned = nativeObj->SetPosition(this->x, this->y, this->z);
		
		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}

	float PositionalSound::GetXPosition()
	{
		return this->x;
	}

	float PositionalSound::GetYPosition()
	{
		return this->y;
	}

	float PositionalSound::GetZPosition()
	{
		return this->z;
	}
}
