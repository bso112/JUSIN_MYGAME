#include "stdafx.h"
#include "..\Headers\Buff.h"
#include "Character.h"
USING(MyGame)

HRESULT CBuff::Initialize(void* _pArg)
{
	return S_OK;
}

_int CBuff::Act(CCharacter* _pTarget)
{
	//�ϴ� �� �ø���
	++m_iTurnCnt;
	
	//�������� ���� �ϼ��� 0, �ƹ��͵� ����.
	if (m_tStateDesc.m_iDuration < m_iTurnCnt)
		return 0;

	//�ൿ
	OnAct(_pTarget);

	return 1;
}

HRESULT CBuff::End_Buff()
{
	m_iTurnCnt = m_tStateDesc.m_iDuration;
	return S_OK;
}



void CBuff::Free()
{
	m_tStateDesc.m_tStats.Free();
}

