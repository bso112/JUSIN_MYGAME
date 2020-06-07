#pragma once
#include "Base.h"

BEGIN(MyGame)
class CSoundMgr : public CBase
{
	DECLARE_SINGLETON(CSoundMgr)
public:
	enum CHANNELID { BGM, PLAYER, PLAYER_FOOTSTEP, PLAYER_ATT, MONSTER, EFFECT, MONSTER_EFFECT, UI, MAXCHANNEL };
private:
	explicit CSoundMgr() {};
	virtual ~CSoundMgr() = default;

public:
	void Initialize();

public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();

private:
	void LoadSoundFile();

private:
	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;


	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
