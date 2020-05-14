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
	:CTerrain(_rhs),
	m_eType(_rhs.m_eType)
{
}

HRESULT CStair::Initialize()
{
	CTerrain::Initialize();

	//�̰� ���� ü�����ɶ�, 1���� �����Ҷ� �ҷ�����.
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
	if (nullptr == _pOther)
		return;

	if (nullptr != dynamic_cast<CHero*>(_pOther))
	{
		//�÷��̾�� ���� ���� ������
		if (m_bContacted)
		{
			CLevel* pWorld = CLevelMgr::Get_Instance()->Get_CurrLevel();
			RETURN_IF_NULL(pWorld);
			//���� ������
			if (m_eType == TYPE_DOWN)
				pWorld->Next_Level();
			//���� ������
			else
				pWorld->Prv_Level();

		}

		m_bContacted = true;
	}
}

CStair * CStair::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar * _pTextureTag, SCENEID _eTextureScene, _tchar * _pFilePath)
{
	CStair* pInstance = new CStair(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tData, _pTextureTag, _eTextureScene, _pTextureTag, _pFilePath)))
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

