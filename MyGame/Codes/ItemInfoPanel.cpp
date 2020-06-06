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
	//���� ����
	m_iDepth = 3;

	Vector3 vPanelPos = Vector3(g_iWinCX >> 1, g_iWinCY >> 1);
	//�θ��� �̴ϼȶ����� �θ�
	CImage::Initialize_Prototype(L"inventory", vPanelPos, Vector2(PANELX, PANLEY), SCENE_STAGE);

	if (nullptr == m_pTransform)
		return E_FAIL;

	m_bActive = false;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();


	//��ư���� �����ϰ� ���̾ ����Ѵ�. (������Ʈ, lateUpdate, render�� �ڵ����� �Ҹ���. lateUpdate���� ����� �����׷쿡 ����Ѵٴ� �����Ͽ�.)
	RECT rc = m_pTransform->Get_RECT();

	for (int i = 0; i < 3; ++i)
	{
		Vector3 vBtnPos = Vector2(rc.left + PADDING_LEFT + (BUTTONCX * 0.5f) + (i* BUTTONCX + i * MARGIN_BUTTON), rc.top + PADDING_TOP);
		CMyButton* pBtn = dynamic_cast<CMyButton*>(pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE,
			CMyButton::Create(m_pGraphic_Device, vBtnPos, Vector2(BUTTONCX, BUTTONCY), L"RedButton", SCENE_STAGE)));
		RETURN_FAIL_IF_NULL(pBtn);
		m_vecBtn.push_back(pBtn);

	}
	
	//������
	m_pItemIcon = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x - (PANELX * 0.5f) + 50.f, vPanelPos.y - (PANLEY * 0.5f) + 50.f), Vector2(50.f, 50.f), L"empty", SCENE_STATIC));
	m_pItemIcon->Set_Active(false);
	m_pItemIcon->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pItemIcon);
	//�������̸� �ؽ�Ʈ
	m_pItemNameText = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x - (PANELX * 0.5f) + 175.f, vPanelPos.y - (PANLEY * 0.5f) + 50.f), Vector2(200.f, 50.f), L"empty", SCENE_STATIC));
	m_pItemNameText->Set_Active(false);
	m_pItemNameText->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pItemNameText);
	//������ ������� �̹���Ŭ����
	m_pDescription = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(vPanelPos.x, vPanelPos.y), Vector2(PANELX - 100.f, PANLEY - 180.f), L"empty", SCENE_STATIC));
	m_pDescription->Set_Active(false);
	m_pDescription->Set_Depth(m_iDepth + 1);
	Safe_AddRef(m_pDescription);
	//��ư�� �����Ѵ�.
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
	//�ڽĵ鵵 �Բ� 
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

	//�������� �׼��� �����´�.
	vector<const _tchar*>* actions = _pItem->Get_Actions();

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return;

	CHero* pHero = dynamic_cast<CHero*>(pObjMgr->Get_Player(SCENE_STAGE));
	if (nullptr == pHero)
		return;

	//�̸�
	if (nullptr != _pItem->Get_Name())
	{
		MYFONT font;
		font.m_Color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		font.m_pFont = g_pFontX2;
		font.m_dwFormat = DT_LEFT ;
		font.m_pText = _pItem->Get_Name();
	
		m_pItemNameText->Set_Font(font);
	}

	//������
	const _tchar* textureTag = _pItem->Get_TextureTag();
	_int textureID = _pItem->Get_TextureID();
	if (nullptr != textureTag)
		m_pItemIcon->Replace_Texture(textureTag, textureID, SCENE_STAGE);

	//����
	if (nullptr != _pItem->Get_Description())
	{
		MYFONT font;
		font.m_dwFormat = DT_LEFT;
		font.m_pText = _pItem->Get_Description();
		m_pDescription->Set_Font(font);
	}

	//�� ��ư�� �������� �� �� �ִ� �׼��� �����Ѵ�.
	for (size_t i = 0; i < actions->size(); ++i)
	{
		if (i >= m_vecBtn.size())
			break;


		//[&]�����ϸ� ���������� actions�� ĸ�ĵǹ����� �̻��� ���� ����Ű�Ե�. actions�� �����ʿ� ��Ƶΰ� ���߿� �θ��°Ŵϱ�.
		//Add_Listener�� �ϸ� ������ _pItem�� �����ʿ��� �����ϴ°� �ָ��ϰ� ��. �׳� ����Ⱑ ����.
		m_vecBtn[i]->Set_Listener([=] { if (_pItem) { _pItem->Use(pHero, &(*actions)[i]); } });

		//��ư
		m_vecBtn[i]->Set_Text((*actions)[i]);


	}

	//������ �ȵ� ��ư�� �Ⱥ��̰��Ѵ�.
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

		//��ư������ ����
		for (auto& btn : m_vecBtn)
		{
			CTransform* pBtnTransform = (CTransform*)btn->Get_Module(L"Transform");
			RETURN_FAIL_IF_NULL(pBtnTransform);
			if (PtInRect(&pBtnTransform->Get_RECT(), pt))
				return E_FAIL;
		}
		//�������� �ǳڲ�����
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
