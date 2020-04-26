#include "stdafx.h"
#include "Terrain.h"
#include "Transform.h"
#include "ModuleMgr.h"	
#include "VIBuffer.h"

USING(MyGame)

CTerrain::CTerrain(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CTerrain::CTerrain(CTerrain & _rhs)
	:CGameObject(_rhs)
{
}

HRESULT CTerrain::Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, _tchar * _pFilePath)
{
	Set_Module(_pTextureTag, SCENEID::SCENE_EDITOR, (CModule**)&m_pTexture);
	Set_Module(L"Transform", SCENEID::SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENEID::SCENE_STATIC, (CModule**)&m_pVIBuffer);
	m_pTransform->Set_Size(Vector4(TILECX, TILECY));
	m_tData = _tData;
	return S_OK;
}

HRESULT CTerrain::Render()
{
	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix());
	m_pVIBuffer->Render();
	return S_OK;
}




CTerrain * CTerrain::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag,_tchar* _pFilePath)
{
	CTerrain* pInstance = new CTerrain(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tData, _pTextureTag, _pFilePath)))
	{
		MSG_BOX("Fail to create CTile");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CTerrain::Clone(void * _param)
{
	return nullptr;
}

void CTerrain::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);

	CGameObject::Free();
}

HRESULT CTerrain::Initalize_Module()
{

	return E_NOTIMPL;
}
