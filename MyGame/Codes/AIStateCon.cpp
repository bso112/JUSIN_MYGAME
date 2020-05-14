#include "stdafx.h"
#include "..\Headers\AIStateCon.h"
#include "TimerMgr.h"


USING(MyGame)

CAIStateCon::CAIStateCon(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CStateCon(_pGraphic_Device) 
{
	ZeroMemory(m_pStateArr, sizeof(m_pStateArr));
};

HRESULT CAIStateCon::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAIStateCon::Initialize(void * _pArg)
{
	return S_OK;
}

_int CAIStateCon::Start(_bool _canAttack, _bool _isAlerted)
{
	CAIState::STATE	eNextState = m_pCurrState->Act(_canAttack, _isAlerted, CTimerMgr::Get_Instance()->Get_TimeDelta());
	
	if (CAIState::STATE_END != eNextState)
	{
		//상태를 바꾼다.
		m_pCurrState = m_pStateArr[eNextState];
		//한번 행동
		m_pCurrState->Act(_canAttack, _isAlerted, CTimerMgr::Get_Instance()->Get_TimeDelta());
	}

	return TURN_NOEVENT;
}

_int CAIStateCon::Update(_bool _canAttack, _bool _isAlerted)
{
	CAIState::STATE	eNextState = m_pCurrState->LateUpdate(_canAttack, _isAlerted, CTimerMgr::Get_Instance()->Get_TimeDelta());

	if (CAIState::STATE_END != eNextState)
	{
		m_pCurrState = m_pStateArr[eNextState];
		m_pCurrState->Act(_canAttack, _isAlerted, CTimerMgr::Get_Instance()->Get_TimeDelta());
		//턴종료
		return TURN_END;
	}

	return TURN_NOEVENT;
}

HRESULT CAIStateCon::Set_State(CAIState::STATE _eState, CAIState * _pAIState)
{
	if (CAIState::STATE_END <= _eState ||
		nullptr == _pAIState)
		return E_FAIL;

	m_pStateArr[_eState] = _pAIState;
	return S_OK;
}

HRESULT CAIStateCon::Set_Default_State(CAIState::STATE _eState)
{
	if (CAIState::STATE_END <= _eState)
		return E_FAIL;

	m_pCurrState = m_pStateArr[_eState];
	return S_OK;
}



CAIStateCon * CAIStateCon::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CAIStateCon* pInstance = new CAIStateCon(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CModule * CAIStateCon::Clone(void * _pArg)
{
	CAIStateCon* pInstance = new CAIStateCon(*this);

	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CAIStateCon::Free()
{
	for (auto& pState : m_pStateArr)
	{
		Safe_Release(pState);
	}
	CModule::Free();
}
