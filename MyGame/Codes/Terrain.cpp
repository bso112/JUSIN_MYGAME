#include "stdafx.h"
#include "Terrain.h"
#include "Transform.h"
#include "ModuleMgr.h"	
#include "VIBuffer.h"
#include "Character.h"
#include "Shader.h"

USING(MyGame)

CTerrain::CTerrain(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
	ZeroMemory(m_PrototypeTag, sizeof(m_PrototypeTag));
}

//Terrain의 SaveData에 새로 추가한 항목이 있다면 반드시 클론에서 넘겨줘야한다.
CTerrain::CTerrain(CTerrain & _rhs)
	: CGameObject(_rhs),
	m_pTexture(_rhs.m_pTexture),
	m_iCurFrame(_rhs.m_iCurFrame),
	m_eState(_rhs.m_eState),
	m_tInfo(_rhs.m_tInfo),
	m_bMaskable(_rhs.m_bMaskable)
{
	memcpy(m_PrototypeTag, _rhs.m_PrototypeTag, sizeof(m_PrototypeTag));
	memcpy(m_LayerTag, _rhs.m_LayerTag, sizeof(m_LayerTag));
	Safe_AddRef(m_pTexture);
	Safe_AddRef(m_pVIBuffer);
}

HRESULT CTerrain::Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pPrototypeTag, const _tchar* _pLayerTag, _tchar * _pFilePath)
{
	memcpy(m_PrototypeTag, _pPrototypeTag, sizeof(_tchar) * lstrlen(_pPrototypeTag));

	if (FAILED(Set_Module(_pTextureTag, _eTextureScene, (CModule**)&m_pTexture)))
		return E_FAIL;

	Set_Module(L"Transform", SCENEID::SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENEID::SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Shader", SCENEID::SCENE_STATIC, (CModule**)&m_pShader);

	m_tInfo = _tData;

	ZeroMemory(&m_LayerTag, sizeof(m_LayerTag));
	if (nullptr != _pLayerTag)
	{
		memcpy(m_LayerTag, _pLayerTag, sizeof(_tchar) * lstrlen(_pLayerTag));
	}


	m_pTransform->Set_Size(Vector4(TILECX, TILECY));
	return S_OK;
}

HRESULT CTerrain::Initialize()
{
	Set_Module(L"Transform", SCENEID::SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENEID::SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Shader", SCENEID::SCENE_STATIC, (CModule**)&m_pShader);

	m_pTransform->Set_Size(Vector4(TILECX, TILECY));
	m_pTransform->Set_ColliderSize(Vector3(5.f, 5.f));
	return S_OK;
}

_int CTerrain::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	m_pTransform->Update_Transform();

	if (nullptr == m_pPipline ||
		nullptr == m_pTransform)
		return -1;

	_matrix camMatrix = m_pPipline->Get_CameraMatrix();
	Vector3 vPos = m_pTransform->Get_Position();
	D3DXVec4Transform(&vPos, &vPos, &camMatrix);

	//컬링
	if (-100.f <= vPos.x && g_iWinCX + 100.f >= vPos.x)
	{
		if (-100.f <= vPos.y && g_iWinCY + 100.f >= vPos.y)
		{
			if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_PRIOR)))
				return -1;
		}
	}
	return 0;
}



HRESULT CTerrain::Render()
{
	if (!m_bActive)
		return 0;

	m_pTransform->Update_Transform();

	ALPHATEST;


	if (m_bUI)
	{
		if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
			return E_FAIL;
	}
	else
	{
		if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
			return E_FAIL;

	}

	int pass = 0;
	//보이지 않으면
	if (!m_bVisuable)
	{
		if (m_bVisited)
		{
			pass = 6; //반투명
		}
		else
			pass = 7; //불투명
	}
	//보이면
	else
	{
		pass = 0;
	}


	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", m_iCurFrame)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin()))
		return E_FAIL;

	//if (m_bMarked || !m_tInfo.m_bMovable) pass = 2;
	if (FAILED(m_pShader->Begin_Pass(pass)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;



	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;

	ALPHATEST_END;


	m_bVisuable = false;

	return S_OK;
}



CTerrain::SAVE_DATA CTerrain::Get_SaveData()
{
	SAVE_DATA tSaveData;
	tSaveData.m_vPosition = m_pTransform->Get_Position();
	tSaveData.m_vRotation = m_pTransform->Get_Rotation();
	tSaveData.m_vSize = m_pTransform->Get_Size();
	tSaveData.m_iCurFrame = m_iCurFrame;

	ZeroMemory(&tSaveData.m_PrototypeTag, sizeof(tSaveData.m_PrototypeTag));
	memcpy(tSaveData.m_PrototypeTag, m_PrototypeTag, sizeof(_tchar) * lstrlen(m_PrototypeTag));

	ZeroMemory(&tSaveData.m_LayerTag, sizeof(tSaveData.m_LayerTag));
	memcpy(tSaveData.m_LayerTag, m_LayerTag, sizeof(_tchar) * lstrlen(m_LayerTag));

	return tSaveData;
}

HRESULT CTerrain::Load_Data(SAVE_DATA& _eSaveData)
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	m_pTransform->Set_Position(_eSaveData.m_vPosition);
	m_pTransform->Set_Rotation(_eSaveData.m_vRotation);
	m_pTransform->Set_Size(_eSaveData.m_vSize);
	memcpy(m_PrototypeTag, _eSaveData.m_PrototypeTag, sizeof(m_PrototypeTag));
	m_iCurFrame = _eSaveData.m_iCurFrame;
	m_eState = _eSaveData.m_eState;

	OnLoadData();
	return S_OK;
}




bool CTerrain::IsMovable(CTransform * _pTransform)
{

	if (nullptr == _pTransform)
		return m_tInfo.m_bMovable;

	return  m_tInfo.m_bMovable && (m_pCharacterTranform == nullptr || m_pCharacterTranform == _pTransform);
}



HRESULT CTerrain::Forward_Frame()
{

	++m_iCurFrame;


	if (m_iCurFrame < 0)
		m_iCurFrame = 0;

	if (m_iCurFrame >= (_int)m_pTexture->Get_TextureSize())
		m_iCurFrame = (_int)m_pTexture->Get_TextureSize() - 1;

	if (FAILED(OnMoveFrame()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrain::Backward_Frame()
{
	--m_iCurFrame;

	if (FAILED(OnMoveFrame()))
		return E_FAIL;

	if (m_iCurFrame < 0)
		m_iCurFrame = 0;

	if (m_iCurFrame >= (_int)m_pTexture->Get_TextureSize())
		m_iCurFrame = (_int)m_pTexture->Get_TextureSize() - 1;

	return S_OK;
}

void CTerrain::OnCollisionEnter(CGameObject * _pOther)
{
	if (!m_bActive)
		return;

	if (nullptr != dynamic_cast<CCharacter*>(_pOther))
	{
		CTransform* pTransform = (CTransform*)_pOther->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return;
		m_pCharacterTranform = pTransform;
	}

	OnCollisionEnterTerrain(_pOther);
}

void CTerrain::OnCollisionStay(CGameObject * _pOther)
{
	if (!m_bActive)
		return;
	OnCollisionStayTerrain(_pOther);
}

void CTerrain::OnCollisionExit(CGameObject * _pOther)
{
	if (!m_bActive)
		return;
	if (nullptr != dynamic_cast<CCharacter*>(_pOther))
	{
		m_pCharacterTranform = nullptr;
	}

	OnCollisionExitTerrain(_pOther);
}

void CTerrain::OnCollisionEnterTerrain(CGameObject * _pOther)
{

}

void CTerrain::OnCollisionStayTerrain(CGameObject * _pOther)
{
}

void CTerrain::OnCollisionExitTerrain(CGameObject * _pOther)
{
}

HRESULT CTerrain::OnMoveFrame()
{
	return S_OK;
}

HRESULT CTerrain::OnLoadData()
{
	return S_OK;
}





CTerrain * CTerrain::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pLayerTag, _tchar* _pFilePath)
{
	CTerrain* pInstance = new CTerrain(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_tData, _pTextureTag, _eTextureScene, _pTextureTag, _pLayerTag, _pFilePath)))
	{
		MSG_BOX("Fail to create CTerrain");
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
	Safe_Release(m_pShader);
	CGameObject::Free();
}


