#include "Fsound.h"

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif


void SoundManager::SetUpSounds()
{

	for (int i = 0; i < sourceVoices.size(); i++)
	{
		if (params[i].start)
		{
			sourceVoices[i]->SubmitSourceBuffer(&(buffers[i]));
			sourceVoices[i]->Start(0);
		}
	}
}

void SoundManager::ReleaseSounds()
{
	for (int i = 0; i < params.size(); i++)
	{
		if (sourceVoices[i])
		{
			sourceVoices[i]->Stop(0);
			sourceVoices[i]->FlushSourceBuffers();
			sourceVoices[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  dataBuffers[i];
		}
	}
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT SoundManager::Init()
{
	HRESULT hr;

	HANDLE hFile;
	DWORD  dwChunkSize;
	DWORD  dwChunkPosition;
	DWORD  filetype;

	// COMの初期化
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&p_XAudio2, 0);		// 第二引数は､動作フラグ デバッグモードの指定(現在は未使用なので0にする)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// 第三引数は、windowsでは無視
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create Mastering Voice ****/
	hr = p_XAudio2->CreateMasteringVoice(&p_MasteringVoice);			// 今回はＰＣのデフォルト設定に任せている
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// 本当６個の引数を持っている
	if (FAILED(hr)) {
		if (p_XAudio2)	p_XAudio2->Release();
		CoUninitialize();
		return -1;
	}


	return hr;
}

//=============================================================================
// 開放処理
//=============================================================================
void SoundManager::Uninit()
{
	for (int i = 0; i < params.size(); i++)
	{
		if (sourceVoices[i])
		{
			sourceVoices[i]->Stop(0);
			sourceVoices[i]->FlushSourceBuffers();
			sourceVoices[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  dataBuffers[i];
		}
	}

	p_MasteringVoice->DestroyVoice();

	if (p_XAudio2) p_XAudio2->Release();

	// COMの破棄
	CoUninitialize();
	{
		std::vector<SoundManager::PARAM> swapParams;
		std::vector<WAVEFORMATEXTENSIBLE> swapWfx;
		std::vector<XAUDIO2_BUFFER> swapBuffer;
		std::vector<BYTE*> swapDataBuffer;
		std::vector<IXAudio2SourceVoice*> swapSourceVoice;

		swapParams.swap(params);
		swapWfx.swap(wfxs);
		swapBuffer.swap(buffers);
		swapDataBuffer.swap(dataBuffers);
	}
}


//=============================================================================
// 開放処理
//=============================================================================
int SoundManager::AddSound(const char* _filePath, bool _isLoop, bool _isStart)
{
	params.push_back({ _filePath,_isLoop, _isStart });
	int id = params.size() - 1;
	return id;
}

int SoundManager::AddSoundDirect(const char* _filePath, bool _isLoop, bool _isStart)
{
	HRESULT hr;

	HANDLE hFile;
	DWORD  dwChunkSize;
	DWORD  dwChunkPosition;
	DWORD  filetype;

	/**** Initalize Sound ****/
	SoundManager::PARAM param{ _filePath,_isLoop,_isStart };
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
	BYTE* dataBuffer;
	IXAudio2SourceVoice* sourceVoice;


	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	hFile = CreateFileA(param.filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)		return S_FALSE;

	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	dataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, dataBuffer, dwChunkSize, dwChunkPosition);

	CloseHandle(hFile);

	//サブミットボイスで利用するサブミットバッファの設定
	buffer.AudioBytes = dwChunkSize;
	buffer.pAudioData = dataBuffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (param.bLoop)
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	else
		buffer.LoopCount = 0;


	p_XAudio2->CreateSourceVoice(&sourceVoice, &(wfx.Format));

	params.emplace_back(param);
	wfxs.emplace_back(wfx);
	buffers.emplace_back(buffer);
	dataBuffers.emplace_back(dataBuffer);
	sourceVoices.emplace_back(sourceVoice);

	return params.size() - 1;
}


//=============================================================================
// 再生
//=============================================================================
void SoundManager::Play(int _id)
{
	IXAudio2SourceVoice*& pSV = sourceVoices[_id];

	XAUDIO2_VOICE_STATE xa2state;
	sourceVoices[_id]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		//停止とキューから削除
		pSV->Stop(0);
		pSV->FlushSourceBuffers();
	}

	//再生とキューに追加
	pSV->SubmitSourceBuffer(&(buffers[_id]));
	pSV->Start(0);
}

//=============================================================================
// 停止
//=============================================================================
void SoundManager::Stop(int _id)
{
	if (sourceVoices[_id] == NULL) return;

	XAUDIO2_VOICE_STATE xa2state;
	sourceVoices[_id]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		sourceVoices[_id]->Stop(0);
		sourceVoices[_id]->FlushSourceBuffers();
	}
}

//=============================================================================
// 一時停止
//=============================================================================
void SoundManager::Pause(int _id)
{
	XAUDIO2_VOICE_STATE xa2state;
	sourceVoices[_id]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		IXAudio2SourceVoice*& pSV = sourceVoices[_id];
		pSV->Stop(0);
	}
}
//=============================================================================
// 途中から再生
//=============================================================================
void SoundManager::Resume(int _id)
{
	XAUDIO2_VOICE_STATE xa2state;
	sourceVoices[_id]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		IXAudio2SourceVoice*& pSV = sourceVoices[_id];
		pSV->Start();
	}
}

void SoundManager::SetVolume(int _id, float _volume)
{
	IXAudio2SourceVoice*& pSV = sourceVoices[_id];
	pSV->SetVolume(_volume);
}

void SoundManager::SetPitch(int _id, float _pitch)
{
	IXAudio2SourceVoice*& pSV = sourceVoices[_id];
	pSV->SetFrequencyRatio(_pitch);
}

//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT SoundManager::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT SoundManager::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}
