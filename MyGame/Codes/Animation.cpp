#include "stdafx.h"
#include "..\Headers\Animation.h"
#include "Texture.h"
#include "Clock.h"

USING(MyGame)
CAnimation::CAnimation()
{
}

//텍스쳐는 얕은복사
CAnimation::CAnimation(CAnimation & _rhs)
	:m_pTexture(_rhs.m_pTexture)
{

}


CAnimation* CAnimation::Render()
{
	if (nullptr == m_pClock)
		return nullptr;


	m_pTexture->Set_Texture(m_iCurrFrame);

	if (m_pClock->isThreashHoldReached(m_dFrameTime))
	{
		++m_iCurrFrame;
	}

	//애니메이션이 끝났을때
	if (m_iCurrFrame == (int)m_pTexture->Get_TextureSize())
	{
		//루프
		if (m_bLoop)
			m_iCurrFrame = 0;
		else
		{
			m_iCurrFrame = (int)m_pTexture->Get_TextureSize() - 1;
			return m_pNextAnim;
		}
	}
	return nullptr;
}

HRESULT CAnimation::Play()
{
	m_iCurrFrame = 0;

	return S_OK;
}

HRESULT CAnimation::Set_NextAnim(CAnimation * _pAnimation)
{
	m_pNextAnim = _pAnimation;
	return S_OK;
}

HRESULT CAnimation::Initialize(CTexture* _pTexture, _double _dFrameTime, _bool _bLoop)
{
	if (nullptr == _pTexture)
		return E_FAIL;

	m_pClock = CClock_Trigger::Create();
	m_pTexture = _pTexture;
	m_dFrameTime = _dFrameTime;
	m_bLoop = _bLoop;

	return S_OK;
}

CAnimation * CAnimation::Create(CTexture * _pTexture, _double _dFrameTime, _bool _bLoop)
{
	CAnimation* pInstance = new CAnimation();
	if (FAILED(pInstance->Initialize(_pTexture, _dFrameTime, _bLoop)))
	{
		MSG_BOX("Fail to create CAnimation");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CAnimation::Free()
{
	Safe_Release(m_pTexture);

	if (0 != Safe_Release(m_pClock))
		MSG_BOX("Fail to Release Clock");

}
