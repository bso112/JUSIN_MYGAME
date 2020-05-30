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
}



//이펙트는 이펙트매니저를 따로 이용하지 않음. 따라서 리턴값이 딱히 의미는 없음.
_int CEffect::Act()
{
	if (m_iDuration < m_iTurnCnt)
	{
		m_bDead = true;
		//파티클 시스템을 해제한다.
		m_pParticleSystem->Set_Dead();
		return -1;
	}

	++m_iTurnCnt;

	return 0;
}

_int CEffect::Update(_double _timeDelta)
{


	return 0;
}

void CEffect::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pParticleSystem);
	CGameObject::Free();
}
