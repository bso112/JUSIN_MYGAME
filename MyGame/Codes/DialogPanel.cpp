#include "stdafx.h"
#include "DialogPanel.h"
#include "Image.h"
#include "ObjMgr.h"
#include "Transform.h"
USING(MyGame)

CDialogPanel::CDialogPanel(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CDialogPanel::CDialogPanel(CDialogPanel & _rhs)
	: CGameObject(_rhs)
{
}

HRESULT CDialogPanel::Initialize(void * _pArg)
{
	 CObjMgr* pObjMgr = CObjMgr::Get_Instance();

	 //�гθ����
	 RETURN_FAIL_IF_NULL(pObjMgr);
	 CImage::STATEDESC tPanelDesc;
	 tPanelDesc.m_eTextureSceneID = SCENE_STAGE;
	 tPanelDesc.m_pTextureTag = L"inventory";
	 tPanelDesc.m_iTextureID = 1;
	 tPanelDesc.m_tBaseDesc.vPos = Vector2((_float)(g_iWinCX >> 1),_float( g_iWinCY >> 1));
	 tPanelDesc.m_tBaseDesc.vSize = Vector2(DIALOG_PANELCX, DIALOG_PANELCY);
	 m_pPanel = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &tPanelDesc));
	 RETURN_FAIL_IF_NULL(m_pPanel);
	 m_pPanel->Set_UI(true);
	 CTransform* pPanelTransform = (CTransform*)m_pPanel->Get_Module(L"Transform");
	 RETURN_FAIL_IF_NULL(pPanelTransform);
	 RECT pPanelRect = pPanelTransform->Get_RECT();
	 Safe_AddRef(m_pPanel);

	 //specker ������ �����
	 CImage::STATEDESC tIconDesc;
	 tIconDesc.m_pTextureTag = L"empty";
	 tIconDesc.m_iTextureID = 1;
	 tIconDesc.m_eTextureSceneID = SCENE_STATIC;
	 tIconDesc.m_tBaseDesc.vPos = Vector2((_float)pPanelRect.left + DIALOG_ICONCX * 0.5f + DIALOG_PADDING, (_float)pPanelRect.top + DIALOG_ICONCY * 0.5f + DIALOG_PADDING);
	 tIconDesc.m_tBaseDesc.vSize = Vector2(DIALOG_ICONCX, DIALOG_ICONCY);
	 m_pIcon = (CImage*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &tIconDesc));
	 Safe_AddRef(m_pIcon);
	 RETURN_FAIL_IF_NULL(m_pIcon);
	 m_pIcon->Set_UI(true);

	//����Ŀ �̸�
	 m_tFont[0].m_tRC = Make_Rect(Vector2(g_iWinCX * 0.5f, pPanelRect.top + DIALOG_PADDING), Vector2(200.f, 36.f));
	 m_tFont[0].m_Color = COLOR_ORANGE;
	 m_tFont[0].m_pFont = g_pFontX2;
	 m_tFont[0].m_dwFormat = DT_LEFT;
	 m_tFont[0].m_pString = L"����";
	 //���ϴ� ����
	 m_tFont[1].m_tRC = Make_Rect(Vector2(g_iWinCX * 0.5f, pPanelRect.top + 50.f), Vector2(DIALOG_PANELCX - DIALOG_PADDING * 2, DIALOG_PANELCY - DIALOG_ICONCY - DIALOG_PADDING * 2));
	 m_tFont[1].m_pFont = g_pFont;
	 m_tFont[1].m_dwFormat = DT_LEFT;
	 m_tFont[1].m_pString = L"�ݰ��� ���翩... �Ѷ� �� ���ó�� �ڽŰ� ��ġ�� ���� ���谡���ٳ�... ������ �� ����� ������ �׾���ȳ�.. �׷��� �� �� ���� ���� �� ����... ������ �ϱ� ������ ����.. ���� �������� �׿���.. ���� �� ����� �Ѿư�����..";
	 
	return S_OK;
}

_int CDialogPanel::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pRenderer)
		return -1;

	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI);

	return 0;
}

HRESULT CDialogPanel::Render()
{
	if (!m_bActive)
		return 0;

	for (auto& font : m_tFont)
	{
		font.m_pFont->DrawText(NULL, font.m_pString.c_str(), -1, &font.m_tRC, font.m_dwFormat, font.m_Color);
	}
}


void CDialogPanel::OnSetActive(_bool _bActive)
{
	if (nullptr == m_pIcon ||
		nullptr == m_pPanel)
		return;

	m_pIcon->Set_Active(_bActive);
	m_pPanel->Set_Active(_bActive);
}

CDialogPanel * CDialogPanel::Create(PDIRECT3DDEVICE9 _pGrahic_Device)
{
	CDialogPanel* pInstance = new CDialogPanel(_pGrahic_Device);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to create CDialogPanel");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CDialogPanel::Free()
{
	Safe_Release(m_pIcon);
	Safe_Release(m_pPanel);
	CGameObject::Free();
}

CGameObject * CDialogPanel::Clone(void * _pArg)
{
	return nullptr;
}
