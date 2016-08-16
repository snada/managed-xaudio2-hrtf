#pragma once

#include <tchar.h>

#include <vector>
#include <xaudio2.h>
#include <xapo.h>
#include <hrtfapoapi.h>

#include <stdio.h>

class XAudio2HrtfNative
{

public:
	__declspec(dllexport) XAudio2HrtfNative();
	__declspec(dllexport) ~XAudio2HrtfNative();
	__declspec(dllexport) int LoadFile(_In_ LPCWSTR filename);
	__declspec(dllexport) int Initialize();
	__declspec(dllexport) int Play();
	__declspec(dllexport) int SetPosition(float x, float y, float z);
	__declspec(dllexport) int SetVolume(float value);

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
	IXAPO* _xapo;
	IXAPOHrtfParameters* _hrtfParams;
	IXAudio2* xAudio2Instance = NULL;
	IXAudio2MasteringVoice* masteringVoice = NULL;
	IXAudio2SourceVoice* sourceVoiceInstance = NULL;
	IXAudio2SubmixVoice* submixVoice = NULL;
};
