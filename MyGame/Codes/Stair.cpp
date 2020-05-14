#include "stdafx.h"
#include "..\Headers\Stair.h"
#include "ObjMgr.h"
#include "Transform.h"
#include "Hero.h"
#include "World.h"

USING(MyGame)

HRESULT CStair::Initialize()
{
	CTerrain::Initialize();

	if (nullptr == m_pTransform)
		return E_FAIL;

	if (m_eType == TYPE_UP)
	{
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();

		if (nullptr == pObjMgr)
			return E_FAIL;

		CGameObject* pPlayer = pObjMgr->Get_Player(SCENE_STAGE);

		if (nullptr == pPlayer)
			return E_FAIL;

		CTransform* pTransform = (CTransform*)pPlayer->Get_Module(L"Transform");
		pTransform->Set_Position(m_pTransform->Get_Position());
	}

	return S_OK;
}

void CStair::OnCollisionEnterTerrain(CGameObject * _pOther)
{
	if (nullptr == _pOther)
		return;

	if (nullptr != dynamic_cast<CHero*>(_pOther))
	{
		//플레이어와 닿은 적이 있으면
		if (m_bContacted)
		{
			CWorld* pWorld = CWorld::Get_Instance();
			//다음 층으로
			if (m_eType == TYPE_DOWN)
				pWorld->Next_Level();
			//이전 층으로
			else
				pWorld->Prv_Level();

		}

		m_bContacted = true;
	}
}

