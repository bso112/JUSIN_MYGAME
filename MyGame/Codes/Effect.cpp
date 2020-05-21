#include "stdafx.h"
#include "..\Headers\Effect.h"
#include "Clock.h"
USING(MyGame)

CEffect::CEffect(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CEffect::CEffect(CEffect & _rhs)
	:CGameObject(_rhs)
{
	m_pDeadClock = CClock_Delay::Create();
}




_int CEffect::Update(_double _timeDelta)
{
	if (m_pDeadClock->isThreashHoldReached(m_fDuration))
	{
		m_bDead = true;
		//파티클 시스템을 해제한다.
		m_pParticleSystem->Set_Dead();
		return -1;
	}

	return 0;
}

void CEffect::Free()
{
	Safe_Release(m_pDeadClock);
	Safe_Release(m_pTransform);
	Safe_Release(m_pParticleSystem);
	CGameObject::Free();
}
