#include "stdafx.h"
#include "..\Headers\Editor.h"
#include "TilePalette.h"
#include "Level.h"
#include "Terrain.h"
#include "KeyMgr.h"
#include "Transform.h"
#include "Renderer.h"
#include "ModuleMgr.h"
#include "Camera.h"
USING(MyGame)

CEditor::CEditor(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device),
	m_pPalette(CTilePalette::Create(_pGraphic_Device))
{

}

HRESULT CEditor::Initialize()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	CKeyMgr::Get_Instance()->RegisterObserver(SCENE_EDITOR, this);
	//ī�޶� ����
	m_pObjMgr->Add_Prototype(L"MainCamera", SCENE_STAGE, CCamera::Create(m_pGraphic_Device));
	m_pMainCam = dynamic_cast<CCamera*>(m_pObjMgr->Add_GO_To_Layer(L"MainCamera", SCENE_STAGE, L"Camera", SCENE_STAGE, &BASEDESC(Vector3(float((TILECX * WORLDX) >> 1), float((TILECY * WORLDY) >> 1)), Vector3(1.f, 1.f, 1.f))));
	RETURN_FAIL_IF_NULL(m_pMainCam);

	m_pWorld = CLevel::Create(m_pGraphic_Device, SCENE_EDITOR, L"../Bin/Data/level1.dat");
	RETURN_FAIL_IF_NULL(m_pWorld);


	return S_OK;
}

_int CEditor::Update(_double _timeDelta)
{
	if (nullptr == m_pPalette ||
		nullptr == m_pWorld)
		return E_FAIL;

	CScene::Update(_timeDelta);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//���� ���õ� Ÿ���� ���콺�� ���󰡰� �Ѵ�.
	if (nullptr != m_pCurrTerrain)
	{
		CTransform* pTransform = (CTransform*)m_pCurrTerrain->Get_Module(L"Transform");
		Vector4 vPos = Vector3(pt.x, pt.y, 0.f, 1.f);
		D3DXVec4Transform(&vPos, &vPos, &CPipline::Get_Instance()->Get_CameraMatrix());
		pTransform->Set_Position(vPos);
		pTransform->Update_Transform();
	}

	
	return 0;
}

HRESULT CEditor::Render()
{

	if (nullptr == m_pWorld ||
		nullptr == m_pPalette	||
		nullptr == m_pPipline	||
		nullptr == m_pMainCam)
		return E_FAIL;

	CScene::Render();

	m_pWorld->Render_ForEditor();
	m_pPalette->Render();

	CTransform* pCamTransform = (CTransform*)m_pMainCam->Get_Module(L"Transform");
	Vector2 vCamPos = pCamTransform->Get_Position();
	_tchar szBuff[MAX_PATH] = L"";
	wsprintf(szBuff, L"X: %d, Y: %d", (_int)vCamPos.x, (_int)vCamPos.y);

	g_pFont->DrawText(NULL, szBuff, -1, nullptr, DT_CENTER | DT_VCENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if (nullptr != m_pCurrTerrain)
		m_pCurrTerrain->Render();

	return S_OK;
}

CEditor * CEditor::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CEditor* pInstance = new CEditor(_pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to Create CEditor Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEditor::Free()
{

	Safe_Release(m_pCurrTerrain);

	Safe_Release(m_pPalette);

	Safe_Release(m_pWorld);
	CKeyMgr::Get_Instance()->UnRegisterObserver(SCENE_EDITOR, this);

	//���� ������Ʈ ������Ÿ�� �����, ���� ������Ʈ �ν��Ͻ��� ���� ���۷��� ����, ��� �ν��Ͻ� �����
	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_EDITOR)))
		MSG_BOX("Fail to Clear GameObject Prototypes");

	//��� ������Ÿ�� �����
	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_EDITOR)))
		MSG_BOX("Fail to Clear Module Prototypes");

	//���� ������Ʈ �ν��Ͻ� �����
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		MSG_BOX("Fail to Clear Module Prototypes");

	if (FAILED(CKeyMgr::Get_Instance()->ClearObservers(SCENEID::SCENE_EDITOR)))
		MSG_BOX("Fail to Clear Module Prototypes");


	CScene::Free();

}

HRESULT CEditor::OnKeyDown(_int KeyCode)
{
	if (KeyCode == VK_RBUTTON)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		//���粨�� �����
		Safe_Release(m_pCurrTerrain);
		//�ȷ�Ʈ���� Ÿ���� �ٽ� �����Ѵ�.
		m_pCurrTerrain = (CTerrain*)m_pPalette->Pick_Tile(pt);
	}

	if (KeyCode == (VK_LBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		//������ ��´�.
		if (nullptr != m_pCurrTerrain)
			m_pWorld->Set_Terrain(m_pCurrTerrain, pt);
	}

	//����ũ�� �����.
	if (KeyCode ==('E'))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (nullptr != m_pCurrTerrain)
			m_pWorld->Erase_Mask(pt);
	}


	//���� ���õ� Ÿ���� �������� �ڷ�
	if (KeyCode == ('A'))
	{
		if (nullptr != m_pCurrTerrain)
		{
			m_pCurrTerrain->Backward_Frame();
		}
	}
	//���� ���õ� Ÿ���� �������� ������
	else if (KeyCode == ('D'))
	{
		if (nullptr != m_pCurrTerrain)
		{
			m_pCurrTerrain->Forward_Frame();
		}
	}
	//���̺�
	if (KeyCode == ('S'))
	{
		m_pWorld->Save_World(L"../Bin/Data/level1dat");
	}
	//�ε�
	else if (KeyCode == ('L'))
	{
		m_pWorld->Load_World(SCENE_EDITOR);
	}

	return S_OK;
}

HRESULT CEditor::OnKeyPressing(_int KeyCode)
{
	if (KeyCode == ('F'))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		//������ ä���.
		if (nullptr != m_pCurrTerrain)
			m_pWorld->Fill_Terrain(m_pCurrTerrain, pt);
	}

	return S_OK;
}
