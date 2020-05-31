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
	
	//�ϴ� �� �ø��� (���� �̵��� ���� ����������� �Ǵ��ؾ��ϱ� ����) 
	++m_iTurnCnt;

	//�þ �ϰ� ���ӽð��� ��
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
