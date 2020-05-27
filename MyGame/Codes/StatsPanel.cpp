#include "stdafx.h"
#include "StatsPanel.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Item.h"
#include "Hero.h"
#include "Shader.h"
#include "ObjMgr.h"
USING(MyGame)


HRESULT CStatsPanel::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CStatsPanel::Initialize(void * _param)
{
	//////렌더 깊이
	//m_iDepth = 1;

	Vector3 vPanelPos = Vector3(g_iWinCX >> 1, g_iWinCY >> 1);
	////부모의 이니셜라이즈 부름
	CImage::Initialize_Prototype(L"inventory", vPanelPos, Vector2(PANELX, PANLEY), SCENE_STAGE);

	if (nullptr == m_pTransform)
		return E_FAIL;

	m_bActive = false;
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();


	//버튼들을 생성하고 레이어에 등록한다. (업데이트, lateUpdate, render는 자동으로 불린다. lateUpdate에서 제대로 렌더그룹에 등록한다는 가정하에.)
	RECT rc = m_pTransform->Get_RECT();

	for (int i = 0; i < 2; ++i)
	{
		Vector3 vBtnPos = Vector2(rc.left + PADDING + (BUTTONCX * 0.5f) + (i* BUTTONCX + i * MARGIN_BUTTON), rc.top + 70.f);
		CMyButton* pBtn = dynamic_cast<CMyButton*>(pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE,
			CMyButton::Create(m_pGraphic_Device, vBtnPos, Vector2(BUTTONCX, BUTTONCY), L"RedButton", SCENE_STAGE)));
		RETURN_FAIL_IF_NULL(pBtn);
		m_vecBtn.push_back(pBtn);

	}
	//버튼을 설정한다.
	for (auto& btn : m_vecBtn)
	{
		Safe_AddRef(btn);
		btn->Set_Active(false);
		btn->Set_Depth(m_iDepth + 1);
	}

	_float fCX = 200.f;
	_float fCY = 35.f;
	RECT panel = m_pTransform->Get_RECT();
	Vector2 fBasePos = Vector2(panel.left + PADDING, panel.top + 100);

	for (int i = 0; i < TEXT_COL; ++i)
	{
		Vector2 vPos = Vector2(fBasePos.x + (fCX * 0.5f), fBasePos.y + (fCY * 0.5f) + i * fCY);
		m_Texts[0][i].m_tRC = Make_Rect(vPos, Vector2(fCX, fCY));
	}
	m_Texts[0][0].m_pString = L"공격력";
	m_Texts[0][1].m_pString = L"체력";
	m_Texts[0][2].m_pString = L"방어력";
	m_Texts[0][3].m_pString = L"경험치";
	m_Texts[0][4].m_pString = L"골드";

	for (int i = 0; i < TEXT_COL; ++i)
	{
		Vector2 vPos = Vector2(fBasePos.x + (fCX * 0.5f) + fCX, fBasePos.y + (fCY * 0.5f) + i * fCY);
		m_Texts[1][i].m_tRC = Make_Rect(vPos, Vector2(fCX, fCY));
	}


	return S_OK;
}




void CStatsPanel::OnSetActive(bool _bActive)
{
	//자식들도 함께 
	for (auto& btn : m_vecBtn)
	{
		btn->Set_Active(_bActive);
	}
}

HRESULT CStatsPanel::Render()
{
	CImage::Render();

	for (int i = 0; i < TEXT_ROW; ++i)
	{
		for (int j = 0; j < TEXT_COL; ++j)
			g_pFontX2->DrawText(NULL, m_Texts[i][j].m_pString.c_str(), -1, &m_Texts[i][j].m_tRC, DT_LEFT, 0xffffffff);
	}

	return 0;
}



void CStatsPanel::Set_Player()
{
	CHero* pHero = dynamic_cast<CHero*>(CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE));
	if (nullptr == pHero)
		return;

	CCharacter::STATS tStats = pHero->Get_Stat();
	_tchar szBuff[MAX_PATH] = L"";
	wsprintf(szBuff, L"%d ~ %d", (_int)tStats.m_fAtt->GetMinValue(), (_int)tStats.m_fAtt->GetMaxValue());
	m_Texts[1][0].m_pString = szBuff;
	wsprintf(szBuff, L"%d / %d", (_int)tStats.m_fHP, (_int)tStats.m_fMaxHp->GetValue());
	m_Texts[1][1].m_pString = szBuff;
	wsprintf(szBuff, L"%d", (_int)tStats.m_fArmor->GetValue());
	m_Texts[1][2].m_pString = szBuff;
	wsprintf(szBuff, L"%d / %d", (_int)tStats.m_fExp, (_int)tStats.m_fMaxExp);
	m_Texts[1][3].m_pString = szBuff;
	wsprintf(szBuff, L"%d", (_int)tStats.m_iGold);
	m_Texts[1][4].m_pString = szBuff;
}

HRESULT CStatsPanel::Add_ButtonListener(function<void()> _func)
{
	for (auto& btn : m_vecBtn)
	{
		btn->Add_Listener(_func);
	}
	return S_OK;
}



CStatsPanel * CStatsPanel::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CStatsPanel* pInstance = new CStatsPanel(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(nullptr)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CStatsPanel::Clone(void * _param)
{
	CStatsPanel* pInstance = new CStatsPanel(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CMyButton");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CStatsPanel::Free()
{

	for (auto& btn : m_vecBtn)
		int i = Safe_Release(btn);

	CImage::Free();
}
