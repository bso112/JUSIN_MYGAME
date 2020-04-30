#include "stdafx.h"
#include "..\Headers\Editor.h"
#include "TilePalette.h"
#include "World.h"
#include "Terrain.h"
#include "KeyMgr.h"
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


	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		//현재꺼를 지우고
		Safe_Release(m_pCurrTerrain);
		//팔레트에서 타일을 다시 선택한다.
		m_pCurrTerrain = (CTerrain*)m_pPalette->Pick_Tile(pt);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		//지형을 찍는다.
		if (nullptr != m_pCurrTerrain)
			m_pWorld->Set_Terrain(m_pCurrTerrain, pt);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		m_pWorld->Save_World(L"../Bin/Data/level1.dat");
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		m_pWorld->Load_World(L"../Bin/Data/level1.dat");
	}

	return 0;
}

HRESULT CEditor::Render()
{
	m_pWorld->Render();
	m_pPalette->Render();
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

	CScene::Free();

}
