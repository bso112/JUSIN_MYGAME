#include "stdafx.h"
#include "Scroll.h"
#include "Laser.h"
#include "Hero.h"
#include "ObjMgr.h"
#include "DialogMgr.h"
#include "Equipment.h"
USING(MyGame)
CScroll::CScroll(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
	//혹시 모르니까
	m_iUseCnt = 0;
	m_bRunOut = false;
	ZeroMemory(&m_tStateDesc, sizeof(m_tStateDesc));
}

CScroll::CScroll(CScroll & _rhs)
	: CItem(_rhs)
{
	m_iUseCnt = 0;
	m_bRunOut = false;
	ZeroMemory(&m_tStateDesc, sizeof(m_tStateDesc));
}

HRESULT CScroll::Initialize(void * _param)
{
	if (nullptr != _param)
		memcpy(&m_tStateDesc, _param, sizeof(STATEDESC));

	CItem::Initialize(_param);
	m_vecActions.push_back(AC_READ);

	if (FAILED(Set_Module(L"scroll", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTextureTag = L"scroll";

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

HRESULT CScroll::Use(CHero * _pHero, const _tchar ** _pAction)
{
	CItem::Use(_pHero, _pAction);

	if (0 == lstrcmp(*_pAction, AC_READ))
	{
		//마법부여
		_pHero->SelectItemToEnchant(this);

	}

	return S_OK;
}

HRESULT CScroll::Enchant(CEquipment* _pItem)
{
	if (nullptr == _pItem)
		return E_FAIL;

	_pItem->Set_Immune(m_tStateDesc.m_eImmune);
	

	return S_OK;
}


CScroll * CScroll::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CScroll* pInstance = new CScroll(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CScroll::Clone(void * _param)
{
	CScroll* pInstance = new CScroll(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create wand");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CScroll::Free()
{
	CItem::Free();
}

Vector3 CScroll::Get_OriginalSize()
{
	return m_tStateDesc.m_tItemDesc.m_tBaseDesc.vSize;
}

