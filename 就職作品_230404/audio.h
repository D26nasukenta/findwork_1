#pragma once

#include <xaudio2.h>
#include "gameObject.h"

#define SOUND_MAX 50
class Audio : public GameObject
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice[SOUND_MAX];
	BYTE*					m_SoundData;

	int						m_Length;
	int						m_PlayLength;


public:
	static void InitMaster();
	static void UninitMaster();

	void Init() {};
	void Uninit();
	void Update() {};
	void Draw() {};

	void Load(const char *FileName);
	void Play(bool Loop ,float volume);


};

