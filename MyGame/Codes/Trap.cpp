#include "stdafx.h"
#include "..\Headers\Trap.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "Transform.h"
USING(MyGame)

_int CTrap::Interact(CGameObject * _pOther)
{
	m_eType = TYPE::TYPE_FIRE;
	if (m_eType >= TYPE_END	||
		m_pTransform == nullptr)
		return -1;

	switch (m_eType)
	{
	case TYPE_FIRE:
	{
		//불 파티클 생성
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		CParticleSystem::STATEDESC tPsDesc;
		tPsDesc.m_dDuration = 3.f;
		tPsDesc.m_dLifeTime = 1.f;
		tPsDesc.m_eTextureSceneID = SCENE_STAGE;
		tPsDesc.m_fSpeed = 1.f;
		tPsDesc.m_pTextureTag = L"Fire";
		tPsDesc.m_tBaseDesc.vPos = m_pTransform->Get_Position();
		tPsDesc.m_vParticleSize = Vector2(5.f, 5.f);
		tPsDesc.m_tBaseDesc.vSize = Vector2(TILECX, TILECY);

		CParticleSystem* pPs = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STATIC, &tPsDesc));
		if (nullptr == pPs)
			return -1;

		pPs->RollUp(m_pTransform->Get_RECT(), 10);
		//타겟 지속 데미지
	}
	}


	return _int();
}
