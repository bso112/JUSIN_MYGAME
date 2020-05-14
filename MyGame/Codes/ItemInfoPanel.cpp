#include "stdafx.h"
#include "..\Headers\ItemInfoPanel.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Item.h"
#include "Hero.h"
USING(MyGame)


HRESULT CItemInfoPanel::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CItemInfoPanel::Initialize(void * _param)
{

	CImage::Initialize(L"inventory", Vector3(g_iWinCX >> 1, g_iWinCY >> 1), Vector2(600.f, 400.f), SCENE_STAGE);

	m_bActive = false;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();

	m_vecBtn.push_back((CMyButton*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CMyButton::Create(m_pGraphic_Device, Vector3(0.f, 0.f, 0.f), Vector2(10.f, 10.f), L"RedButton", SCENE_STAGE)));
	m_vecBtn.push_back((CMyButton*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CMyButton::Create(m_pGraphic_Device, Vector3(0.f, 0.f, 0.f), Vector2(10.f, 10.f), L"RedButton", SCENE_STAGE)));
	m_vecBtn.push_back((CMyButton*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CMyButton::Create(m_pGraphic_Device, Vector3(0.f, 0.f, 0.f), Vector2(10.f, 10.f), L"RedButton", SCENE_STAGE)));

	m_pDescription = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(), Vector2(), L"empty", SCENE_STATIC));

	for (auto& btn : m_vecBtn)
	{
		Safe_AddRef(btn);
		btn->Add_Listener([&] { this->Set_Active(false);});
	}

	Safe_AddRef(m_pDescription);

	return S_OK;
}




void CItemInfoPanel::Set_Item(CItem * _pItem)
{

	////판넬을 켠다.
	//Set_Active(true);

	//아이템의 액션을 가져온다.
	vector<const _tchar*>* actions = _pItem->Get_Actions();

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return;

	CHero* pHero = dynamic_cast<CHero*>(pObjMgr->Get_Player(SCENE_STAGE));
	if (nullptr == pHero)
		return;

	//각 버튼에 아이템이 할 수 있는 액션을 연결한다.
	for (size_t i = 0; i < actions->size(); ++i)
	{
		if (i >= m_vecBtn.size())
			break;

		m_pDescription->Set_Text(_pItem->Get_Description());
		m_vecBtn[i]->Set_Text((*actions)[i]);
		m_vecBtn[i]->Add_Listener([&] { _pItem->Use(pHero, (*actions)[i]);});

	}

}

HRESULT CItemInfoPanel::Add_ButtonListener(function<void()> _func)
{
	for (auto& btn : m_vecBtn)
	{
		btn->Add_Listener(_func);
	}
	return S_OK;
}



CItemInfoPanel * CItemInfoPanel::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CItemInfoPanel* pInstance = new CItemInfoPanel(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(nullptr)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CItemInfoPanel::Clone(void * _param)
{
	CItemInfoPanel* pInstance = new CItemInfoPanel(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
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
