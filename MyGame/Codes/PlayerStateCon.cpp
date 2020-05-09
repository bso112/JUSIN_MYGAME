#include "stdafx.h"
#include "PlayerStateCon.h"
#include "TimerMgr.h"


USING(MyGame)

CPlayerStateCon::CPlayerStateCon(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CStateCon(_pGraphic_Device)
{
	ZeroMemory(m_pStateArr, sizeof(m_pStateArr));
};

HRESULT CPlayerStateCon::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayerStateCon::Initialize(void * _pArg)
{
	return S_OK;
}

_int CPlayerStateCon::Start(_bool _canAttack, _bool _isAlerted)
{
	CPlayerState::STATE	eNextState = m_pCurrState->Act(_canAttack, _isAlerted, CTimerMgr::Get_Instance()->Get_TimeDelta());

	if (CPlayerState::STATE_END != eNextState)
	{
		//상태를 바꾼다.
		m_pCurrState = m_pStateArr[eNextState];
		//한번 행동
		m_pCurrState->Act(_canAttack, _isAlerted, CTimerMgr::Get_Instance()->Get_TimeDelta());
	}

	return TURN_NOEVENT;
}

_int CPlayerStateCon::Update(_bool _canAttack, _bool _isAlerted)
{
	CPlayerState::STATE	eNextState = m_pCurrState->LateUpdate();

	if (CPlayerState::STATE_END != eNextState)
	{
		//상태를 바꾼다.
		m_pCurrState = m_pStateArr[eNextState];
		//한번 행동
		m_pCurrState->Act(_canAttack, _isAlerted, CTimerMgr::Get_Instance()->Get_TimeDelta());
		return TURN_END;
	}

	return TURN_NOEVENT;
}

HRESULT CPlayerStateCon::Set_State(CPlayerState::STATE _eState, CPlayerState * _pAIState)
{
	if (CPlayerState::STATE_END <= _eState ||
		nullptr == _pAIState)
		return E_FAIL;

	m_pStateArr[_eState] = _pAIState;
	return S_OK;
}

HRESULT CPlayerStateCon::Set_Default_State(CPlayerState::STATE _eState)
{
	if (CPlayerState::STATE_END <= _eState)
		return E_FAIL;

	m_pCurrState = m_pStateArr[_eState];
	return S_OK;
}



CPlayerStateCon * CPlayerStateCon::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CPlayerStateCon* pInstance = new CPlayerStateCon(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CModule * CPlayerStateCon::Clone(void * _pArg)
{
	CPlayerStateCon* pInstance = new CPlayerStateCon(*this);

	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CPlayerStateCon::Free()
{
	for (auto& pState : m_pStateArr)
	{
		Safe_Release(pState);
	}
	CModule::Free();
}
