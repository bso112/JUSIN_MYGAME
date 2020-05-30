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



//����Ʈ�� ����Ʈ�Ŵ����� ���� �̿����� ����. ���� ���ϰ��� ���� �ǹ̴� ����.
_int CEffect::Act()
{
	if (m_iDuration < m_iTurnCnt)
	{
		m_bDead = true;
		//��ƼŬ �ý����� �����Ѵ�.
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
