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

	//부모의 이니셜라이즈 부름
	CImage::Initialize(L"inventory", Vector3(g_iWinCX >> 1, g_iWinCY >> 1), Vector2(PANELX, PANLEY), SCENE_STAGE);

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



	//m_pDescription = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(), Vector2(), L"empty", SCENE_STATIC));

	//버튼을 설정한다.
	for (auto& btn : m_vecBtn)
	{
		Safe_AddRef(btn);
		btn->Set_Active(false);
		btn->Set_Depth(m_iDepth + 1);
		btn->Add_Listener([&] { this->Set_Active(false);});
	}

	//Safe_AddRef(m_pDescription);

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

	//각 버튼에 아이템이 할 수 있는 액션을 연결한다.
	for (size_t i = 0; i < actions->size(); ++i)
	{
		if (i >= m_vecBtn.size())
			break;

		//m_pDescription->Set_Text(_pItem->Get_Description());
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

	//Safe_Release(m_pDescription);
	for (auto& btn : m_vecBtn)
	{
		Safe_Release(btn);
	}
	CImage::Free();
}
