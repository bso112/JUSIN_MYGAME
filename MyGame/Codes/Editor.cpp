#include "stdafx.h"
#include "..\Headers\Editor.h"
#include "TilePalette.h"
USING(MyGame)

CEditor::CEditor(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device)
{

}

HRESULT CEditor::Initialize()
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
	if (0 != Safe_Release(m_pPalette))
		MSG_BOX("Fail to release Palette");
	CScene::Free();

}
