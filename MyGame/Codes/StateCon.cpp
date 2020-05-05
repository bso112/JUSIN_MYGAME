#include "stdafx.h"
#include "..\Headers\StateCon.h"


USING(MyGame)

HRESULT CStateCon::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CStateCon::Initialize(void * _pArg)
{
	return S_OK;
}

_int CStateCon::Update(_double _timeDelta)
{
	CState*	pNextState = m_pCurrState->Update(_timeDelta);
	
	if (nullptr != pNextState)
	{
		m_pCurrState = pNextState;
	}

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
