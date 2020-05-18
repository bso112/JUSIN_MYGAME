#include "stdafx.h"
#include "..\Headers\Hero.h"
#include "LevelMgr.h"
#include "Transform.h"
#include "TurnMgr.h"
#include "Terrain.h"
#include "ObjMgr.h"
#include "Layer.h"
#include "StageUIMgr.h"
#include "Monster.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "TimerMgr.h"
USING(MyGame)



CHero::CHero(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CCharacter(_pGraphic_Device)
{
	ZeroMemory(m_pAnimator, sizeof(m_pAnimator));
}

CHero::CHero(CHero & _hero)
	: CCharacter(_hero)
{

}


HRESULT CHero::OnKeyDown(_int KeyCode)
{
	if (KeyCode == VK_LBUTTON)
	{
		if (nullptr == m_pTransform)
			return E_FAIL;

		//�� ��ƼŬ ����
		//Vector3 vPos = m_pTransform->Get_Position();
		//CParticleSystem::STATEDESC desc;
		//desc.m_tBaseDesc.vPos = vPos;
		//desc.m_tBaseDesc.vSize = Vector2(100.f, 100.f);
		//desc.m_pTextureTag = L"Blood";
		//desc.m_eTextureSceneID = SCENE_STAGE;
		//desc.m_dDuration = 3.f;
		//desc.m_dLifeTime = 3.f;
		//desc.m_fSpeed = 500.f;
		//desc.m_vParticleSize = Vector2(25.f, 25.f);
		//CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		//CParticleSystem* pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STAGE, L"ParticleSystem", SCENE_STAGE, &desc));

		//pParticleSystem->Play(CTimerMgr::Get_Instance()->Get_TimeDelta(), 10);



		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

#pragma region ����ó��

		vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
		for (auto& rc : UIRect)
		{
			//���� ���콺 ����Ʈ�� UI���� ������ ����
			if (PtInRect(&rc, pt))
			{
				return E_FAIL;
			}
		}
#pragma endregion

		CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();

#pragma region �̵�

		vector<CTerrain*> route;
		CLevel* pLevel = pLevelMgr->Get_CurrLevel();
		RETURN_FAIL_IF_NULL(pLevel);
		pLevel->Get_Route(m_pTransform->Get_Position(), pt, route, m_pTransform);

		//�ش� ��Ʈ�� ���󰡱� ���� �ʿ��� �ϼ��� ���
		_int iTurnCnt = (_int)route.size() / m_pTransform->Get_Desc().movePerTurn;
		//�ּ� 1��
		if (iTurnCnt == 0) iTurnCnt = 1;
		m_pTransform->Go_Route(route, 1.f, iTurnCnt);
#pragma endregion

		//Ÿ����ŷ
		CTerrain* pTerrain = pLevel->Pick_Tile(pt);
		//���ͷ�Ʈ�Ѵ�.
		if (nullptr != pTerrain)
			pTerrain->Interact(this);

		//�׿� ������Ʈ ��ŷ
		CGameObject* pObj = pLevelMgr->PickObject(pt);
		if (nullptr != pObj)
		{
			//���ͷ�Ʈ�Ѵ�.
			Interact(pObj);
			pObj->Interact(this);
		}


		//�÷��̾ ������ �� �̵�
		CTurnMgr::Get_Instance()->MoveTurn_Simultaneously(iTurnCnt);

	}

	return S_OK;
}

HRESULT CHero::Set_InitialPos()
{
	if (m_pTransform == nullptr)
		return E_FAIL;

	CLevel* pLevel = CLevelMgr::Get_Instance()->Get_CurrLevel();

	if (nullptr == pLevel)
		return E_FAIL;

	m_pTransform->Set_Position(pLevel->Get_PlayerSpawnPos());



	return S_OK;


}

_int CHero::Interact(CGameObject * _pOther)
{
	CMonster* pMonster = dynamic_cast<CMonster*>(_pOther);
	if (nullptr == pMonster)
		return -1;

	pMonster->TakeDamage(m_tStat.m_fAtt->GetValue());
	return 0;
}

HRESULT CHero::PlayAnimation(const _tchar * _pTag)
{
	return m_pAnimator[m_eCurrCloth]->Play(_pTag);
}

bool CHero::Has_Key(TIER _tier)
{


	return true;
}

void CHero::Free()
{

	for (int i = 0; i < CLOTH_END; ++i)
		Safe_Release(m_pAnimator[i]);

	CCharacter::Free();
}


