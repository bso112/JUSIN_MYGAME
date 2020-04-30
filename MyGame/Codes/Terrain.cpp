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
	: CGameObject(_rhs),
	m_pTexture(_rhs.m_pTexture),
	m_pVIBuffer(_rhs.m_pVIBuffer),
	m_pPrototypeTag(_rhs.m_pPrototypeTag)
{
	m_tInfo = _rhs.m_tInfo;
	Safe_AddRef(m_pTexture);
	Safe_AddRef(m_pVIBuffer);
}

HRESULT CTerrain::Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pPrototypeTag, _tchar * _pFilePath)
{
	m_pPrototypeTag = _pPrototypeTag;
	if(FAILED(Set_Module(_pTextureTag, _eTextureScene, (CModule**)&m_pTexture)))
		return E_FAIL;
	Set_Module(L"Transform", SCENEID::SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENEID::SCENE_STATIC, (CModule**)&m_pVIBuffer);
	m_tInfo = _tData;
	m_pTransform->Set_Size(Vector4(TILECX, TILECY));
	return S_OK;
}

HRESULT CTerrain::Initialize()
{
	Set_Module(L"Transform", SCENEID::SCENE_STATIC, (CModule**)&m_pTransform);
	m_pTransform->Set_Size(Vector4(TILECX, TILECY));
	return S_OK;
}

HRESULT CTerrain::Render()
{
	m_pTransform->Update();
	m_pTexture->Set_Texture(0);
	m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix());
	m_pVIBuffer->Render();
	return S_OK;
}

CTerrain::SAVE_DATA CTerrain::Get_SaveData()
{
	SAVE_DATA tSaveData;
	tSaveData.m_vPosition	= m_pTransform->Get_Position();
	tSaveData.m_vRotation	= m_pTransform->Get_Rotation();
	tSaveData.m_vSize = m_pTransform->Get_Size();

	ZeroMemory(&tSaveData.m_PrototypeTag, sizeof(tSaveData.m_PrototypeTag));
	memcpy(tSaveData.m_PrototypeTag, m_pPrototypeTag, sizeof(_tchar) * lstrlen(m_pPrototypeTag));

	return tSaveData;
}

HRESULT CTerrain::Load_Data(SAVE_DATA _eSaveData)
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	m_pTransform->Set_Position(_eSaveData.m_vPosition);
	m_pTransform->Set_Rotation(_eSaveData.m_vRotation);
	m_pTransform->Set_Size(_eSaveData.m_vSize);

	return S_OK;
}




CTerrain * CTerrain::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, _tchar* _pFilePath)
{
	CTerrain* pInstance = new CTerrain(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tData, _pTextureTag, _eTextureScene, _pTextureTag, _pFilePath)))
	{
		MSG_BOX("Fail to create CTile");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CTerrain::Clone(void * _param)
{
	CTerrain* pInstance = new CTerrain(*this);
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to clone CTile");
		Safe_Release(pInstance);

	}
	return pInstance;
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
