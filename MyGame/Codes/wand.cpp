#include "stdafx.h"
#include "wand.h"
#include "Laser.h"
#include "Hero.h"
#include "ObjMgr.h"
#include "DialogMgr.h"
USING(MyGame)
CWand::CWand(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
	//혹시 모르니까
	m_iUseCnt = 0;
	m_bRunOut = false;
	ZeroMemory(&m_tStateDesc, sizeof(m_tStateDesc));
}

CWand::CWand(CWand & _rhs)
	: CItem(_rhs)
{
	m_iUseCnt = 0;
	m_bRunOut = false;
	ZeroMemory(&m_tStateDesc, sizeof(m_tStateDesc));
}

HRESULT CWand::Initialize(void * _param)
{
	if (nullptr != _param)
		memcpy(&m_tStateDesc, _param, sizeof(STATEDESC));

	CItem::Initialize(_param);
	m_vecActions.push_back(AC_ZAP);

	if (FAILED(Set_Module(L"wand", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTextureTag = L"wand";

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &m_tTransformDesc)))
		return E_FAIL;
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;


	m_pTransform->Set_Position(m_tStateDesc.m_tItemDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tStateDesc.m_tItemDesc.m_tBaseDesc.vSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);

	m_pDescription = m_tStateDesc.m_tItemDesc.m_pDescription;
	m_iTextureID = m_tStateDesc.m_tItemDesc.m_iTextureID;
	m_pItemName = m_tStateDesc.m_tItemDesc.m_pItemName;
	return S_OK;
}

HRESULT CWand::Use(CHero * _pHero, const _tchar ** _pAction)
{
	CItem::Use(_pHero, _pAction);

	if (0 == lstrcmp(*_pAction, AC_ZAP))
	{
		if (nullptr == m_pTransform)
			return E_FAIL;

		//다쓰면 
		if (m_iUseCnt >= m_tStateDesc.m_iMaxZapCnt)
		{
			CDialogMgr::Get_Instance()->Log_Main(MSG_EXHAUST(m_pItemName), 0xffded716);
			m_bRunOut = true;
			return S_OK;
		}
		
		_pHero->Zap(this);
		++m_iUseCnt;
	}

	return S_OK;
}

HRESULT CWand::Zap(Vector2 _vOrigin, POINT _pt)
{
	switch (m_tStateDesc.m_eType)
	{
	case MyGame::CWand::TYPE_LIGHTING:
		Zap_Lighting(_vOrigin, _pt);
		break;
	}
	return S_OK;
}

HRESULT CWand::Zap_Lighting(Vector2 _vOrigin, POINT _pt)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);
	CLaser::STATEDESC desc;
	desc.m_dLifeTime = 0.5f;
	desc.m_eTextureSceneID = SCENE_STAGE;
	desc.m_iTextureID = 1;
	desc.m_pTextureTag = L"laser";
	desc.m_iDamage = 10;

	//충돌처리를 위해 레이어를 따로 뺀다.
	CLaser* pLaser = (CLaser*)pObjMgr->Add_GO_To_Layer(L"Laser", SCENE_STAGE, CLaser::Create(m_pGraphic_Device, desc));
	pLaser->Beam(_vOrigin, _pt);

	return S_OK;
}

CWand * CWand::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CWand* pInstance = new CWand(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CWand::Clone(void * _param)
{
	CWand* pInstance = new CWand(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CWand::Free()
{
	CItem::Free();
}

Vector3 CWand::Get_OriginalSize()
{
	return m_tStateDesc.m_tItemDesc.m_tBaseDesc.vSize;
}

