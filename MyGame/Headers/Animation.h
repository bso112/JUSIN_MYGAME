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
	//�������Ӵ� �ð�
	_double				m_dFrameTime = 0.0; 
	_bool				m_bLoop = false;
	CClock_Trigger*		m_pClock = nullptr;
	_uint				m_iCurrFrame = 0;
	
private:
	CAnimation*			m_pNextAnim = nullptr;
	
public:
	//������ ������ �ִϸ��̼��� �����͸� ��ȯ�Ѵ�.
	CAnimation*	Render();
	//�ִϸ��̼��� �����Ѵ�.
	HRESULT		Play();

public:
	HRESULT	Set_NextAnim(CAnimation* _pAnimation);


public:
	HRESULT Initialize(CTexture * _pTextures, _double _dFrameTime, _bool _bLoop);
public:
	static CAnimation* Create(CTexture* _pTextures, _double _dFrameTime, _bool _bLoop);
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
