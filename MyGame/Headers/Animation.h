#pragma once
#include "Base.h"
BEGIN(MyGame)
class CTexture;
class CClock_Trigger;
class CAnimation final : public CBase
{
private:
	explicit CAnimation();
	explicit CAnimation(CAnimation& _rhs);
	virtual ~CAnimation() = default;

private:
	CTexture*			m_pTexture = nullptr;
	//한프레임당 시간
	_double				m_dFrameTime = 0.0; 
	_bool				m_bLoop = false;
	CClock_Trigger*		m_pClock = nullptr;
	_uint				m_iCurrFrame = 0;
public:
	HRESULT Play();

public:
	HRESULT Initialize(CTexture * _pTextures, _double _dFrameTime, _bool _bLoop);
public:
	static CAnimation* Create(CTexture* _pTextures, _double _dFrameTime, _bool _bLoop);
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
