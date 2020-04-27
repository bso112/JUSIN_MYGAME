#include "stdafx.h"
#include "..\Headers\Editor.h"
#include "TilePalette.h"
#include "World.h"
#include "Terrain.h"
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


	if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
	
		if(m_pCurrTerrain != nullptr)
			m_pWorld->Set_Terrain(m_pCurrTerrain, pt);

		m_pCurrTerrain = (CTerrain*)m_pPalette->Pick_Tile(pt);
		
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
	Safe_Release(m_pCurrTerrain);

	if (0 != Safe_Release(m_pPalette))
		MSG_BOX("Fail to release Palette");

	Safe_Release(m_pWorld);

	if(0 != m_pWorld->Destroy_Instance())
		MSG_BOX("Fail to release m_pWorld");
	
	CScene::Free();

}
