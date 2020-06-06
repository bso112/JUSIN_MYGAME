#include "stdafx.h"
#include "..\Headers\ItemInfoPanel.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Item.h"
#include "Hero.h"
#include "Shader.h"
#include "KeyMgr.h"
USING(MyGame)


HRESULT CItemInfoPanel::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CItemInfoPanel::Initialize(void * _param)
{
	CKeyMgr::Get_Instance()->RegisterObserver(SCENE_STAGE, this);
	//렌더 깊이
	m_iDepth = 3;

	Vector3 vPanelPos = Vector3(g_iWinCX >> 1, g_iWinCY >> 1);
	//부모의 이니셜라이즈 부름
	CImage::Initialize_Prototype(L"inventory", vPanelPos, Vector2(PANELX, PANLEY), SCENE_STAGE);

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
	m_pItemIcon = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x - (PANELX * 0.5f) + 50.f, vPanelPos.y - (PANLEY * 0.5f) + 50.f), Vector2(50.f, 50.f), L"empty", SCENE_STATIC));
	m_pItemIcon->Set_Active(false);
	m_pItemIcon->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pItemIcon);
	//아이템이름 텍스트
	m_pItemNameText = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x - (PANELX * 0.5f) + 175.f, vPanelPos.y - (PANLEY * 0.5f) + 50.f), Vector2(200.f, 50.f), L"empty", SCENE_STATIC));
	m_pItemNameText->Set_Active(false);
	m_pItemNameText->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pItemNameText);
	//설명을 적어놓은 이미지클래스
	m_pDescription = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x, vPanelPos.y), Vector2(PANELX - 100.f, PANLEY - 180.f), L"empty", SCENE_STATIC));
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
	{
		MYFONT font;
		font.m_Color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		font.m_pFont = g_pFontX2;
		font.m_dwFormat = DT_LEFT ;
		font.m_pText = _pItem->Get_Name();
	
		m_pItemNameText->Set_Font(font);
	}

	//아이콘
	const _tchar* textureTag = _pItem->Get_TextureTag();
	_int textureID = _pItem->Get_TextureID();
	if (nullptr != textureTag)
		m_pItemIcon->Replace_Texture(textureTag, textureID, SCENE_STAGE);

	//설명
	if (nullptr != _pItem->Get_Description())
	{
		MYFONT font;
		font.m_dwFormat = DT_LEFT;
		font.m_pText = _pItem->Get_Description();
		m_pDescription->Set_Font(font);
	}

	//각 버튼에 아이템이 할 수 있는 액션을 연결한다.
	for (size_t i = 0; i < actions->size(); ++i)
	{
		if (i >= m_vecBtn.size())
			break;


		//[&]으로하면 지역변수인 actions가 캡쳐되버려서 이상한 곳을 가리키게됨. actions를 리스너에 담아두고 나중에 부르는거니까.
		//Add_Listener로 하면 삭제된 _pItem을 리스너에서 해제하는게 애매하게 됨. 그냥 덮어쓰기가 편함.
		m_vecBtn[i]->Set_Listener([=] { if (_pItem) { _pItem->Use(pHero, &(*actions)[i]); } });

		//버튼
		m_vecBtn[i]->Set_Text((*actions)[i]);


	}

	//셋팅이 안된 버튼은 안보이게한다.
	for (size_t i = actions->size(); i < m_vecBtn.size(); ++i)
		m_vecBtn[i]->Set_Active(false);

}

HRESULT CItemInfoPanel::Add_ButtonListener(function<void()> _func)
{
	for (auto& btn : m_vecBtn)
	{
		btn->Add_Listener(_func);
	}
	return S_OK;
}



HRESULT CItemInfoPanel::OnKeyDown(_int KeyCode)
{
	if (!m_bActive	||
		nullptr == m_pTransform)
		return E_FAIL;


	if (KeyCode == VK_LBUTTON)
	{

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		//버튼영역은 제외
		for (auto& btn : m_vecBtn)
		{
			CTransform* pBtnTransform = (CTransform*)btn->Get_Module(L"Transform");
			RETURN_FAIL_IF_NULL(pBtnTransform);
			if (PtInRect(&pBtnTransform->Get_RECT(), pt))
				return E_FAIL;
		}
		//눌었을때 판넬꺼지게
		if (PtInRect(&m_pTransform->Get_RECT(), pt))
		{
			Set_Active(false);
		}
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
	int a = Safe_Release(m_pItemIcon);
	int b = Safe_Release(m_pItemNameText);
	int c = Safe_Release(m_pDescription);

	for (auto& btn : m_vecBtn)
	{
		int d = Safe_Release(btn);
	}
	CImage::Free();
	CKeyMgr::Get_Instance()->UnRegisterObserver(SCENE_STAGE, this);

}
