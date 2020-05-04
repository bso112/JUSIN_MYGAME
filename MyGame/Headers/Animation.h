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
	
private:
	CAnimation*			m_pNextAnim = nullptr;
	
public:
	//다음에 실행할 애니메이션의 포인터를 반환한다.
	CAnimation*	Render();
	//애니메이션을 실행한다.
	HRESULT		Play();

public:
	HRESULT	Set_NextAnim(CAnimation* _pAnimation);


public:
	HRESULT Initialize(CTexture * _pTextures, _double _dFrameTime, _bool _bLoop);
public:
	static CAnimation* Create(CTexture* _pTextures, _double _dFrameTime, _bool _bLoop);
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
