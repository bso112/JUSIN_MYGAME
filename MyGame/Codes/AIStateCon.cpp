#include "stdafx.h"
#include "..\Headers\AIStateCon.h"
#include "TimerMgr.h"


USING(MyGame)

CAIStateCon::CAIStateCon(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CModule(_pGraphic_Device) 
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

_int CAIStateCon::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt)
{
	CAIState::STATE	eNextState = m_pCurrState->Act(_canAttack, _isAlerted, _iTurnCnt, CTimerMgr::Get_Instance()->Get_TimeDelta());
	
	if (CAIState::STATE_END != eNextState)
	{
		m_pCurrState = m_pStateArr[eNextState];
	}

	return S_OK;
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
