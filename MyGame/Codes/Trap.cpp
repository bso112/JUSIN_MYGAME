#include "stdafx.h"
#include "..\Headers\Trap.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "Transform.h"
USING(MyGame)

_int CTrap::Interact(CGameObject * _pOther)
{
	if (m_eType >= TYPE_END	||
		m_pTransform == nullptr)
		return -1;

	m_eType = TYPE::TYPE_FIRE;
	switch (m_eType)
	{
	case TYPE_FIRE:
	{
		//불 파티클 생성
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		CParticleSystem::STATEDESC tPsDesc;
		tPsDesc.m_dDuration = 3.f;
		tPsDesc.m_eTextureSceneID = SCENE_STAGE;
		tPsDesc.m_fSpeed = 1.f;
		tPsDesc.m_pTextureTag = L"Fire";
		tPsDesc.m_tBaseDesc.vPos = m_pTransform->Get_Position();
		tPsDesc.m_vParticleSize = Vector2(15.f, 15.f);
		tPsDesc.m_tBaseDesc.vSize = Vector2(TILECX, TILECY);

		CParticleSystem* pPs = (CParticleSystem*)pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STAGE, L"ParticleSystem", SCENE_STAGE, &tPsDesc);

		pPs->RollUp(m_pTransform->Get_RECT(), 10);
		//타겟 지속 데미지
	}
	}


	return _int();
}
