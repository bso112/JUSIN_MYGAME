#include "stdafx.h"
#include "..\Headers\Character.h"
#include "Stat.h"
#include "Clock.h"
USING(MyGame)


void CCharacter::Free()
{
}


void CCharacter::TakeDamage(float _fDamage)
{

	m_tStat.m_fHP -= _fDamage;

	if (m_tStat.m_fHP < 0)
	{
		OnDead();
		m_tStat.m_fHP = 0.f;
	}
	else
		OnTakeDamage();

}


bool CCharacter::IsAlive()
{
	return m_tStat.m_fHP > 0;
}

bool CCharacter::IsImmune(IMMUNE _eImmune)
{
	for (auto& immune : m_vecImmune)
	{
		if (immune == _eImmune)
			return true;
	}
	return false;
}

HRESULT CCharacter::MoveToDst(Vector2 _vDst, _double _timeDelta)
{

	if ((_vDst.x == 0 && _vDst.y == 0))
		return E_FAIL;

	Vector2 toTarget = (_vDst - m_tInfo.vPos);
	float dist = toTarget.magnitude();
	if (dist > 0.5f)
	{
		Vector2 dir = toTarget.Nomalize();
		m_tInfo.vPos.x += dir.x * m_fSpeed * (float)_timeDelta;
		m_tInfo.vPos.y += dir.y * m_fSpeed * (float)_timeDelta;
	}

	return S_OK;

}


void CCharacter::MoveFrame()
{
}

