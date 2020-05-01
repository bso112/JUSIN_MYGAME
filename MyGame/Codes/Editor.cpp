#include "stdafx.h"
#include "..\Headers\Editor.h"
#include "TilePalette.h"
#include "World.h"
#include "Terrain.h"
#include "KeyMgr.h"
#include "Transform.h"
#include "Renderer.h"
#include "ModuleMgr.h"
USING(MyGame)

CEditor::CEditor(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device), m_pWorld(CWorld::Get_Instance()),
	m_pPalette(CTilePalette::Create(_pGraphic_Device))
{
	Safe_AddRef(m_pWorld);
}

HRESULT CEditor::Initialize()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pWorld->Initialize(m_pGraphic_Device, SCENE_EDITOR);

	return S_OK;
}

_int CEditor::Update(_double _timeDelta)
{
	if (nullptr == m_pPalette ||
		nullptr == m_pWorld)
		return E_FAIL;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//현재 선택된 타일이 마우스를 따라가게 한다.
	if (nullptr != m_pCurrTerrain)
	{
		CTransform* pTransform = (CTransform*)m_pCurrTerrain->Get_Module(L"Transform");
		pTransform->Set_Position(Vector3((float)pt.x, (float)pt.y, 0.f, 1.f));
		pTransform->Late_Update();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		//현재꺼를 지우고
		Safe_Release(m_pCurrTerrain);
		//팔레트에서 타일을 다시 선택한다.
		m_pCurrTerrain = (CTerrain*)m_pPalette->Pick_Tile(pt);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		//지형을 찍는다.
		if (nullptr != m_pCurrTerrain)
			m_pWorld->Set_Terrain(m_pCurrTerrain, pt);
	}

	//현재 선택된 타일의 프레임을 뒤로
	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		if (nullptr != m_pCurrTerrain)
		{
			m_pCurrTerrain->Backward_Frame();
		}
	}
	//현재 선택된 타일의 프레임을 앞으로
	else if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		if (nullptr != m_pCurrTerrain)
		{
			m_pCurrTerrain->Forward_Frame();
		}
	}
	//세이브
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		m_pWorld->Save_World(L"../Bin/Data/level1.dat");
	}
	//로드
	else if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		m_pWorld->Load_World(L"../Bin/Data/level1.dat", SCENE_EDITOR);
	}

	return 0;
}

HRESULT CEditor::Render()
{

	if (nullptr == m_pWorld ||
		nullptr == m_pPalette)
		return E_FAIL;

	m_pWorld->Render();
	m_pPalette->Render();

	if(nullptr != m_pCurrTerrain)
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

	if (0 != Safe_Release(m_pCurrTerrain))
		MSG_BOX("Fail to release m_pCurrTerrain");

	if (0 != Safe_Release(m_pPalette))
		MSG_BOX("Fail to release Palette");

	Safe_Release(m_pWorld);

	if (0 != m_pWorld->Destroy_Instance())
		MSG_BOX("Fail to release m_pWorld");

	//게임 오브젝트 프로토타입 지우기, 게임 오브젝트 인스턴스에 대한 레퍼런스 끊기, 모듈 인스턴스 지우기
	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_EDITOR)))
		MSG_BOX("Fail to Clear GameObject Prototypes");

	//모듈 프로토타입 지우기
	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_EDITOR)))
		MSG_BOX("Fail to Clear Module Prototypes");

	//게임 오브젝트 인스턴스 지우기
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		MSG_BOX("Fail to Clear Module Prototypes");


	CScene::Free();

}
