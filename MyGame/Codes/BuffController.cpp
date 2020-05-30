#include "stdafx.h"
#include "..\Headers\BuffController.h"

USING(MyGame)
CBuffController::CBuffController(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}
HRESULT CBuffController::Initialize()
{
	return S_OK;
}
_int CBuffController::Act(CCharacter* _pTarget)
{
	if (m_listBuff.size() <= 0)
		return 0;

	auto& iter = m_listBuff.begin();
	while (iter != m_listBuff.end())
	{
		_int iDuration = (*iter)->Act(_pTarget);
		//남은턴이 0턴이면
		if (iDuration == 0)
		{
			//삭제
			Safe_Release(*iter);
			iter = m_listBuff.erase(iter);
		}
		else
			++iter;
	}
	return 0;
}

HRESULT CBuffController::Add_Buff(CBuff * _pBuff)
{
	if (nullptr == _pBuff)
		return E_FAIL;

	m_listBuff.push_back(_pBuff); 

	return S_OK;
}

CBuffController * CBuffController::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CBuffController* pInstance = new CBuffController(_pGraphic_Device);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to create CBuffController");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CBuffController::Free()
{
	for (auto& buff : m_listBuff)
	{
		Safe_Release(buff);
	}

	Safe_Release(m_pGraphic_Device);
}
