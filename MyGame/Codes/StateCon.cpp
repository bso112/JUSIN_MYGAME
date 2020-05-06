#include "stdafx.h"
#include "..\Headers\StateCon.h"
#include "TimerMgr.h"


USING(MyGame)

HRESULT CStateCon::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CStateCon::Initialize(void * _pArg)
{
	return S_OK;
}

_int CStateCon::Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt)
{
	CState*	pNextState = m_pCurrState->Act(_canAttack, _isAlerted, _iTurnCnt, CTimerMgr::Get_Instance()->Get_TimeDelta());
	
	if (nullptr != pNextState)
	{
		m_pCurrState = pNextState;
		m_listState.push_back(m_pCurrState);
	}

	return S_OK;
}

HRESULT CStateCon::Set_Defualt_State(CState * _pState)
{
	if (_pState == nullptr) 
		return E_FAIL;
	m_pCurrState = _pState; 
	m_listState.push_back(m_pCurrState);
	return S_OK;
}

CStateCon * CStateCon::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CStateCon* pInstance = new CStateCon(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CModule * CStateCon::Clone(void * _pArg)
{
	CStateCon* pInstance = new CStateCon(*this);

	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void CStateCon::Free()
{
	for (auto& pState : m_listState)
	{
		Safe_Release(pState);
	}
	CModule::Free();
}
