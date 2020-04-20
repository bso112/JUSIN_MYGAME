#include "stdafx.h"
#include "..\Headers\Editor.h"
#include "TilePalette.h"
USING(MyGame)

CEditor::CEditor(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device)
{

}

HRESULT CEditor::Initalize()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pPalette = CTilePalette::Create(m_pGraphic_Device);

	return S_OK;	
}

_int CEditor::Update(_double _timeDelta)
{
	return 0;
}

HRESULT CEditor::Render()
{
	m_pPalette->Render();
	return S_OK;
}

void CEditor::Free()
{
	CScene::Free();

}
