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

HRESULT CTerrain::Initialize_Prototype(TERRAIN _tData, MODULE _eTextureKey, _tchar * _pFilePath)
{
	Set_Module(_eTextureKey, SCENEID::SCENE_STATIC, (CModule**)m_pTexture);
	Set_Module(MODULE_TRANSFORM, SCENEID::SCENE_STATIC, (CModule**)m_pTransform);
	Set_Module(MODULE_VIBUFFER, SCENEID::SCENE_STATIC, (CModule**)m_pVIBuffer);
	m_pTransform->Set_Size(Vector4(TILECX, TILECY));
	m_tData = _tData;
	return S_OK;
}

HRESULT CTerrain::Render()
{
	m_pTexture->Set_Textrue(0);
	m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix());
	m_pVIBuffer->Render();
	return S_OK;
}




CTerrain * CTerrain::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, MODULE _eTextureKey, _tchar* _pFilePath)
{
	CTerrain* pInstance = new CTerrain(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tData, _eTextureKey, _pFilePath)))
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
}

HRESULT CTerrain::Initalize_Module()
{

	return E_NOTIMPL;
}
