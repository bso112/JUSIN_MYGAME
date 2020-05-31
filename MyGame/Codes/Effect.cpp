#include "stdafx.h"
#include "..\Headers\Effect.h"
#include "Clock.h"
USING(MyGame)

CEffect::CEffect(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CEffect::CEffect(CEffect & _rhs)
	: CGameObject(_rhs)
{
}





_int CEffect::StartAct()
{
	if (m_bDead)
	{
		m_bTurnEnd = true;
		return -1;
	}
	
	//일단 턴 늘리고 (턴이 이동한 순간 사라질지말지 판단해야하기 때문) 
	++m_iTurnCnt;

	//늘어난 턴과 지속시간을 비교
	if (m_iDuration <= m_iTurnCnt)
	{
		m_bDead = true;
		OnDead();
		m_pParticleSystem->Set_Dead();
	}

	m_bTurnEnd = true;

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
