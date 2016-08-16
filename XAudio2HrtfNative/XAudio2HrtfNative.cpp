#include "XAudio2HrtfNative.h"
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

XAudio2HrtfNative::XAudio2HrtfNative() {}

XAudio2HrtfNative::~XAudio2HrtfNative() {}

int XAudio2HrtfNative::LoadFile(LPCWSTR filename)
{
	BOOL mfStarted = FALSE;
	auto hr = MFStartup(MF_VERSION);
	mfStarted = SUCCEEDED(hr);

	IMFSourceReader *reader = NULL;
	if (SUCCEEDED(hr))
	{
		hr = MFCreateSourceReaderFromURL(filename, nullptr, &reader);
	}

	// Select the first audio stream, and deselect all other streams.
	if (SUCCEEDED(hr))
	{
		hr = reader->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_ALL_STREAMS), FALSE);
	}

	if (SUCCEEDED(hr))
	{
		hr = reader->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), TRUE);
	}

	// Create a partial media type that specifies uncompressed PCM audio.
	IMFMediaType *partialType = NULL;
	if (SUCCEEDED(hr))
	{
		hr = MFCreateMediaType(&partialType);
	}

	if (SUCCEEDED(hr))
	{
		hr = partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	}

	if (SUCCEEDED(hr))
	{
		hr = partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	}

	// Set this type on the source reader. The source reader will load the necessary decoder.
	if (SUCCEEDED(hr))
	{
		hr = reader->SetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, partialType);
	}


	// Get the complete uncompressed format
	IMFMediaType *uncompressedAudioType = NULL;
	if (SUCCEEDED(hr))
	{
		hr = reader->GetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &uncompressedAudioType);
	}

	// Ensure the stream is selected.
	if (SUCCEEDED(hr))
	{
		hr = reader->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), TRUE);
	}

	// Get the audio block size and number of bytes/second from the audio format.
	if (SUCCEEDED(hr))
	{
		WAVEFORMATEX* format = nullptr;
		UINT32 size = 0;
		hr = MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType, &format, &size);

		// Only mono PCM files are supported for HRTF processing
		if (SUCCEEDED(hr) && format->wFormatTag != WAVE_FORMAT_PCM && format->nChannels != 1)
		{
			hr = E_INVALIDARG;
		}

		if (SUCCEEDED(hr))
		{
			CopyMemory(&_format, format, sizeof WAVEFORMATEX);
		}

		if (format)
		{
			CoTaskMemFree(format);
		}
	}

	// Get audio samples from the source reader.
	_audioData.resize(0);
	while (SUCCEEDED(hr))
	{
		DWORD dwFlags = 0;

		// Read the next sample.
		IMFSample *sample;
		hr = reader->ReadSample(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &dwFlags, nullptr, &sample);

		if (SUCCEEDED(hr) && (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM) != 0)
		{
			// End of stream
			break;
		}

		if (SUCCEEDED(hr) && sample == nullptr)
		{
			// No sample, keep going
			continue;
		}

		// Get a pointer to the audio data in the sample.
		IMFMediaBuffer *buffer = NULL;
		if (SUCCEEDED(hr))
		{
			hr = sample->ConvertToContiguousBuffer(&buffer);
		}

		DWORD bufferSize = 0;
		if (SUCCEEDED(hr))
		{
			BYTE* data;
			hr = buffer->Lock(&data, nullptr, &bufferSize);

			auto currentDataSize = _audioData.size();
			if (SUCCEEDED(hr))
			{
				_audioData.resize(currentDataSize + bufferSize);
			}

			if (SUCCEEDED(hr))
			{
				CopyMemory(_audioData.data() + currentDataSize, data, bufferSize);
				// Unlock the buffer
				hr = buffer->Unlock();
			}
		}
	}

	if (mfStarted)
	{
		MFShutdown();
	}

	return hr;
}

int XAudio2HrtfNative::Initialize() {
	
	auto hr = CreateHrtfApo(nullptr, &_xapo);

	if (SUCCEEDED(hr))
	{
		_xapo->QueryInterface(__uuidof(IXAPOHrtfParameters), reinterpret_cast<void**>(&_hrtfParams));
	}

	// Set the default environment.
	if (SUCCEEDED(hr))
	{
		hr = _hrtfParams->SetEnvironment(HrtfEnvironment::Small);
	}

	if (FAILED(hr)) {
		return hr;
	}

	auto pos = HrtfPosition{ 0.0f, 0.0f, 0.0f };

	if (SUCCEEDED(hr))
	{
		hr = _hrtfParams->SetSourcePosition(&pos);
	}

	if (FAILED(hr = XAudio2Create(&xAudio2Instance, XAUDIO2_1024_QUANTUM)))
		return hr;

	if (FAILED(hr = xAudio2Instance->CreateMasteringVoice(&masteringVoice, 2, 48000)))
		return hr;

	if (SUCCEEDED(hr))
	{
		hr = xAudio2Instance->CreateSourceVoice(&sourceVoiceInstance, GetFormat());
	}

	if (SUCCEEDED(hr))
	{
		XAUDIO2_EFFECT_DESCRIPTOR fxDesc{};
		fxDesc.InitialState = TRUE;
		fxDesc.OutputChannels = 2;          // Stereo output
		fxDesc.pEffect = _xapo;              // HRTF xAPO set as the effect.

		XAUDIO2_EFFECT_CHAIN fxChain{};
		fxChain.EffectCount = 1;
		fxChain.pEffectDescriptors = &fxDesc;

		XAUDIO2_VOICE_SENDS sends = {};
		XAUDIO2_SEND_DESCRIPTOR sendDesc = {};
		sendDesc.pOutputVoice = masteringVoice;
		sends.SendCount = 1;
		sends.pSends = &sendDesc;

		// HRTF APO expects mono 48kHz input, so we configure the submix voice for that format.
		hr = xAudio2Instance->CreateSubmixVoice(&submixVoice, 1, 48000, 0, 0, &sends, &fxChain);
	}

	// Route the source voice to the submix voice.
	// The complete graph pipeline looks like this -
	// Source Voice -> Submix Voice (HRTF xAPO) -> Mastering Voice
	if (SUCCEEDED(hr))
	{
		XAUDIO2_VOICE_SENDS sends = {};
		XAUDIO2_SEND_DESCRIPTOR sendDesc = {};
		sendDesc.pOutputVoice = submixVoice;
		sends.SendCount = 1;
		sends.pSends = &sendDesc;
		hr = sourceVoiceInstance->SetOutputVoices(&sends);
	}

	// Submit audio data to the source voice.
	if (SUCCEEDED(hr))
	{
		XAUDIO2_BUFFER buffer{};
		buffer.AudioBytes = static_cast<UINT32>(GetSize());
		buffer.pAudioData = GetData();
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		hr = sourceVoiceInstance->SubmitSourceBuffer(&buffer);
	}

	sourceVoiceInstance->EnableEffect(0);
	
	return hr;
}

int XAudio2HrtfNative::Play()
{
	return sourceVoiceInstance->Start();
}

int XAudio2HrtfNative::Stop()
{
	return sourceVoiceInstance->Stop();
}

int XAudio2HrtfNative::SetEnvironment(int envCode) {
	return _hrtfParams->SetEnvironment(static_cast<HrtfEnvironment>(envCode));
}

int XAudio2HrtfNative::SetPosition(float x, float y, float z)
{
	auto pos = HrtfPosition{ x, y, z };

	return _hrtfParams->SetSourcePosition(&pos);
}

int XAudio2HrtfNative::SetVolume(float value)
{
	return sourceVoiceInstance->SetVolume(value);
}
