#pragma once

#include <tchar.h>


#include <vector>
#include <xaudio2.h>
#include <xapo.h>
#include <hrtfapoapi.h>

#include <stdio.h>

class __declspec(dllexport) XAudio2HrtfNative
{
public:
	XAudio2HrtfNative();
	~XAudio2HrtfNative();
	int LoadFile(_In_ LPCWSTR filename);

	const WAVEFORMATEX* GetFormat() const
	{
		return &_format;
	}

	size_t GetSize() const
	{
		return _audioData.size();
	}

	const BYTE* GetData() const
	{
		return _audioData.data();
	}

private:
	WAVEFORMATEX        _format;
	std::vector<BYTE>   _audioData;
};
