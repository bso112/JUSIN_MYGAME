#include "stdafx.h"
#include "..\Headers\Burn.h"
#include "Stat.h"
#include "Character.h"
USING(MyGame)


HRESULT CBurn::Initialize(void* _pArg)
{
	if (nullptr != _pArg)
		memcpy(&m_tStateDesc, _pArg, sizeof(STATEDESC));

	
	return S_OK;
}

void CBurn::OnAct(CCharacter* _pTarget)
{
	if (nullptr == _pTarget)
		return;

	_pTarget->TakeDamage(m_tStateDesc.m_tStats.m_fAtt->GetValue());

}

CBurn * CBurn::Create(void* _pArg)
{
	CBurn* pInstance = new CBurn();
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to create CBurn");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CBurn::Free()
{
	CBuff::Free();
}
