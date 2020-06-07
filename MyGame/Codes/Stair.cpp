#include "stdafx.h"
#include "..\Headers\Stair.h"
#include "ObjMgr.h"
#include "Transform.h"
#include "Hero.h"
#include "LevelMgr.h"

USING(MyGame)

CStair::CStair(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CTerrain(_pGraphic_Device)
{
}

CStair::CStair(CStair & _rhs)
	: CTerrain(_rhs),
	m_eType(_rhs.m_eType)
{
}

HRESULT CStair::Initialize()
{
	CTerrain::Initialize();

	//이건 레벨 체인지될때, 1레벨 시작할때 불러야함.
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

HRESULT CStair::OnMoveFrame()
{
	if (TYPE_END <= (TYPE)m_iCurFrame)
		return E_FAIL;

	m_eType = (TYPE)m_iCurFrame;

	return S_OK;
}

HRESULT CStair::OnLoadData()
{
	OnMoveFrame();
	return S_OK;
}

void CStair::OnCollisionEnterTerrain(CGameObject * _pOther)
{
	if (!m_bActive)
		return;

	if (nullptr == _pOther)
		return;

	if (nullptr != dynamic_cast<CHero*>(_pOther))
	{
		CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();

		if (m_eType == TYPE_UP)
		{
			//플레이어와 닿은 적이 있으면
			//if (m_bContacted)
		//	{
			RETURN_IF_NULL(pLevelMgr);
			//다음 층으로
			if (m_eType == TYPE_DOWN)
				pLevelMgr->Next_Level();
			//이전 층으로
			else
				pLevelMgr->Prv_Level();
			//}

		}
		else
		{
			//내려갈때는 무조건 다음 층으로
			pLevelMgr->Next_Level();
		}

		m_bContacted = true;
	}
}

CStair * CStair::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar * _pTextureTag, SCENEID _eTextureScene, const _tchar* _pLayerTag, _tchar * _pFilePath)
{
	CStair* pInstance = new CStair(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tData, _pTextureTag, _eTextureScene, _pTextureTag, _pLayerTag, _pFilePath)))
	{
		MSG_BOX("Fail to create CStair");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CStair::Clone(void * _param)
{
	CStair* pInstance = new CStair(*this);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to clone CStair");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CStair::Free()
{
	CTerrain::Free();
}

