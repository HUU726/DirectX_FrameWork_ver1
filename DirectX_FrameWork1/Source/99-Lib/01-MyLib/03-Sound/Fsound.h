#pragma once

#include <xaudio2.h>
#include <vector>


class SoundManager
{
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
		bool start;
	} PARAM;


	IXAudio2* p_XAudio2;
	IXAudio2MasteringVoice* p_MasteringVoice;
	std::vector<PARAM> params;

	std::vector<IXAudio2SourceVoice*> sourceVoices;
	std::vector<WAVEFORMATEXTENSIBLE> wfxs;	//WAVフォーマット
	std::vector<XAUDIO2_BUFFER> buffers;
	std::vector<BYTE*> dataBuffers;

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	SoundManager() : p_XAudio2(nullptr), p_MasteringVoice(NULL) {}

public:

	static SoundManager& GetInstance()
	{
		static SoundManager instance;
		return instance;
	}

	/**
	* @brief	追加したサウンドをスロットにセットする
	* @note		シーン開始前に1回だけ
	*/
	void SetUpSounds();
	/**
	* @brief	スロットにセットされているサウンドを開放する
	* @note		シーン終了時に1回だけ
	*/
	void ReleaseSounds();

	/**
	* @brief	SoundManager初期化関数
	* @note		ゲームループ前に1回だけ初期化
	*/
	HRESULT Init();
	/**
	* @brief	SounManager後処理関数
	* @note		ゲームループ終了時に1回だけ
	*/
	void Uninit();


	/**
	* @brief	サウンドを追加する関数
	* @param	const char*	_filePath	ファイルパス
	* @param	bool		_isLoop		ループするか否か
	* @param	bool		_isStart	シーン開始時に自動的に再生するか否か
	* @return	int						再生時に扱うID
	*/
	int AddSound(const char* _filePath, bool _isLoop, bool _isStart = false);
	/*
	* @brief	サウンドを追加する関数
	* @param	const char*	_filePath	ファイルパス
	* @param	bool		_isLoop		ループするか否か
	* @param	bool		_isStart	シーン開始時に自動的に再生するか否か
	* @return	int						再生時に扱うID
	*/
	int AddSoundDirect(const char* _filePath, bool _isLoop, bool _isStart = false);

	// 引数で指定したサウンドを最初から再生する
	void Play(int _id);
	// 引数で指定したサウンドを停止する
	void Stop(int _id);
	//再生中の一時停止
	void Pause(int _id);
	// 再生を再開する
	void Resume(int _id);

	//音量設定
	void SetVolume(int _id, float _volume);
	//ピッチ設定
	void SetPitch(int _id, float _pitch);

};