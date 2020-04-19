#include "stdafx.h"
#include "..\Headers\Editor.h"
#include "Texture.h"
#include "VIBuffer.h"

USING(MyGame)

CEditor::CEditor(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device)
{

}

HRESULT CEditor::Initalize()
{

	return S_OK;	
}

_int CEditor::Update(_double _timeDelta)
{
	return 0;
}

HRESULT CEditor::Render()
{

	return S_OK;
}

void CEditor::Free()
{

	CScene::Free();

}
