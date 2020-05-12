#include "stdafx.h"
#include "..\Headers\ItemInfoPanel.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Item.h"
#include "Hero.h"
USING(MyGame)


HRESULT CItemInfoPanel::Initialize(Vector3 _vPos)
{
	CImage::Initialize(L"Texture_chrom", _vPos, Vector2(600.f, 400.f), SCENE_STAGE);

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	
	m_vecBtn.push_back((CMyButton*)pObjMgr->Add_GO_To_Layer(L"RedButton", SCENE_STAGE, L"UI", SCENE_STAGE, &BASEDESC(Vector3(), Vector2())));
	m_vecBtn.push_back((CMyButton*)pObjMgr->Add_GO_To_Layer(L"RedButton", SCENE_STAGE, L"UI", SCENE_STAGE, &BASEDESC(Vector3(), Vector2())));
	m_vecBtn.push_back((CMyButton*)pObjMgr->Add_GO_To_Layer(L"RedButton", SCENE_STAGE, L"UI", SCENE_STAGE, &BASEDESC(Vector3(), Vector2())));

	m_pDescription = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(), Vector2(), L"empty", SCENE_STATIC));

	for (auto& btn : m_vecBtn)
	{
		Safe_AddRef(btn);
	}
	Safe_AddRef(m_pDescription);

	return S_OK;
}




HRESULT CItemInfoPanel::Set_Item(CItem * _pItem)
{
	m_pItem = _pItem;
	vector<const _tchar*>* actions = _pItem->Get_Actions();

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CHero* pHero = dynamic_cast<CHero*>(pObjMgr->Get_Player(SCENE_STAGE));
	if (nullptr == pHero)
		return E_FAIL;

	for (size_t i = 0; i < actions->size(); ++i)
	{
		if (i >= m_vecBtn.size())
			break;

		m_pDescription->Set_Text(_pItem->Get_Description());
		m_vecBtn[i]->Set_Text((*actions)[i]);
		m_vecBtn[i]->Add_Listener([&] { _pItem->Use(pHero, (*actions)[i]);});

	}

	return S_OK;
}



CItemInfoPanel * CItemInfoPanel::Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector3 _vPos)
{
	CItemInfoPanel* pInstance = new CItemInfoPanel(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_vPos)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CItemInfoPanel::Clone(void * _param = nullptr)
{
	return nullptr;
}

void CItemInfoPanel::Free()
{

	Safe_Release(m_pDescription);
	for (auto& btn : m_vecBtn)
	{
		Safe_Release(btn);
	}
	CImage::Free();
}
