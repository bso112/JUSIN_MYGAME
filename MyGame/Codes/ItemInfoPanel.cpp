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
	//렌더 깊이
	m_iDepth = 1;

	Vector3 vPanelPos = Vector3(g_iWinCX >> 1, g_iWinCY >> 1);
	//부모의 이니셜라이즈 부름
	CImage::Initialize(L"inventory", vPanelPos, Vector2(PANELX, PANLEY), SCENE_STAGE);

	if (nullptr == m_pTransform)
		return E_FAIL;

	m_bActive = false;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();


	//버튼들을 생성하고 레이어에 등록한다. (업데이트, lateUpdate, render는 자동으로 불린다. lateUpdate에서 제대로 렌더그룹에 등록한다는 가정하에.)
	RECT rc = m_pTransform->Get_RECT();

	for (int i = 0; i < 3; ++i)
	{
		Vector3 vBtnPos = Vector2(rc.left + PADDING_LEFT + (BUTTONCX * 0.5f) + (i* BUTTONCX + i * MARGIN_BUTTON), rc.top + PADDING_TOP);
		CMyButton* pBtn = dynamic_cast<CMyButton*>(pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE,
			CMyButton::Create(m_pGraphic_Device, vBtnPos, Vector2(BUTTONCX, BUTTONCY), L"RedButton", SCENE_STAGE)));
		RETURN_FAIL_IF_NULL(pBtn);
		m_vecBtn.push_back(pBtn);

	}

	//아이콘
	m_pItemIcon = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x - (PANELX * 0.5f), vPanelPos.y - (PANLEY * 0.5f)), Vector2(PANELX - 100.f, PANLEY - 50.f), L"empty", SCENE_STATIC));
	m_pItemIcon->Set_Active(false);
	m_pItemIcon->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pItemIcon);
	//아이템이름 텍스트
	m_pItemNameText = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x - (PANELX * 0.5f) + 100, vPanelPos.y - (PANLEY * 0.5f)), Vector2(PANELX - 100.f, PANLEY - 50.f), L"empty", SCENE_STATIC));
	m_pItemNameText->Set_Active(false);
	m_pItemNameText->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pItemNameText);
	//설명을 적어놓은 이미지클래스
	m_pDescription = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x, vPanelPos.y), Vector2(PANELX - 100.f, PANLEY - 50.f), L"empty", SCENE_STATIC));
	m_pDescription->Set_Active(false);
	m_pDescription->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pDescription);
	//버튼을 설정한다.
	for (auto& btn : m_vecBtn)
	{
		Safe_AddRef(btn);
		btn->Set_Active(false);
		btn->Set_Depth(m_iDepth + 1);
		btn->Add_Listener([&] { this->Set_Active(false);});
	}


	return S_OK;
}



HRESULT CItemInfoPanel::OnRender()
{

	return S_OK;
}

void CItemInfoPanel::OnSetActive(bool _bActive)
{
	//자식들도 함께 
	for (auto& btn : m_vecBtn)
	{
		btn->Set_Active(_bActive);
	}
	m_pDescription->Set_Active(_bActive);
	m_pItemIcon->Set_Active(_bActive);
	m_pItemNameText->Set_Active(_bActive);
}




void CItemInfoPanel::Set_Item(CItem * _pItem)
{

	//아이템의 액션을 가져온다.
	vector<const _tchar*>* actions = _pItem->Get_Actions();

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return;

	CHero* pHero = dynamic_cast<CHero*>(pObjMgr->Get_Player(SCENE_STAGE));
	if (nullptr == pHero)
		return;

	//이름
	if (nullptr != _pItem->Get_Name())
		m_pItemNameText->Set_Text(_pItem->Get_Name());

	//아이콘
	const _tchar* textureTag = _pItem->Get_TextureTag();
	_int textureID = _pItem->Get_TextureID();
	if (nullptr != textureTag)
		m_pItemIcon->Replace_Texture(textureTag, textureID, SCENE_STAGE);

	//설명
	if (nullptr != _pItem->Get_Description())
		m_pDescription->Set_Text(_pItem->Get_Description());

	//각 버튼에 아이템이 할 수 있는 액션을 연결한다.
	for (size_t i = 0; i < actions->size(); ++i)
	{
		if (i >= m_vecBtn.size())
			break;

		//버튼
		m_vecBtn[i]->Set_Text((*actions)[i]);
		//[&]으로하면 지역변수인 actions가 캡쳐되버려서 이상한 곳을 가리키게됨. actions를 리스너에 담아두고 나중에 부르는거니까.
		m_vecBtn[i]->Add_Listener([=] { _pItem->Use(pHero, (*actions)[i]); });

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
	Safe_Release(m_pItemIcon);
	Safe_Release(m_pItemNameText);
	Safe_Release(m_pDescription);
	for (auto& btn : m_vecBtn)
	{
		Safe_Release(btn);
	}
	CImage::Free();
}
