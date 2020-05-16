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
	//���� ����
	m_iDepth = 1;

	//�θ��� �̴ϼȶ����� �θ�
	CImage::Initialize(L"inventory", Vector3(g_iWinCX >> 1, g_iWinCY >> 1), Vector2(PANELX, PANLEY), SCENE_STAGE);

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



	//m_pDescription = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, Vector3(), Vector2(), L"empty", SCENE_STATIC));

	//��ư�� �����Ѵ�.
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
	//�ڽĵ鵵 �Բ� 
	for (auto& btn : m_vecBtn)
	{
		btn->Set_Active(_bActive);
	}
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

	//�� ��ư�� �������� �� �� �ִ� �׼��� �����Ѵ�.
	for (size_t i = 0; i < actions->size(); ++i)
	{
		if (i >= m_vecBtn.size())
			break;

		//m_pDescription->Set_Text(_pItem->Get_Description());
		m_vecBtn[i]->Set_Text((*actions)[i]);
		//[&]�����ϸ� ���������� actions�� ĸ�ĵǹ����� �̻��� ���� ����Ű�Ե�. actions�� �����ʿ� ��Ƶΰ� ���߿� �θ��°Ŵϱ�.
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
