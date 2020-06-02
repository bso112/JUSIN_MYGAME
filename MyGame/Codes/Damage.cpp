#include "stdafx.h"
#include "Damage.h"
#include "Stat.h"
#include "Character.h"
USING(MyGame)


HRESULT CDamage::Initialize(void* _pArg)
{
	if (nullptr != _pArg)
		memcpy(&m_tStateDesc, _pArg, sizeof(STATEDESC));

	
	return S_OK;
}

void CDamage::OnAct(CCharacter* _pTarget)
{
	if (nullptr == _pTarget)
		return;

	//½ºÅÈÀÌ Áö¿öÁü
	_pTarget->TakeDamage(5);

}

CDamage * CDamage::Create(void* _pArg)
{
	CDamage* pInstance = new CDamage();
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to create CBurn");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CDamage::Free()
{
	CBuff::Free();
}
