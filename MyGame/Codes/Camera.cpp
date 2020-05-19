#include "stdafx.h"
#include "..\Headers\Camera.h"
#include "Transform.h"

USING(MyGame)

CCamera::CCamera(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
}

CCamera::CCamera(CCamera & _rhs)
	: CGameObject(_rhs)
{
}

HRESULT CCamera::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CCamera::Initialize(void * _pArg)
{	
	CTransform::STATEDESC transformDesc;
	transformDesc.speedPerSec = 100.f;
	transformDesc.radianPerSec = 100.f;
	if(FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &transformDesc)))
		return E_FAIL;

	if (nullptr != _pArg)
	{
		BASEDESC* desc = (BASEDESC*)_pArg;
		m_pTransform->Set_Position(Vector2(desc->vPos.x - (g_iWinCX >> 1), desc->vPos.y - (g_iWinCY >> 1)));

		
	}

	return S_OK;
}

_int CCamera::Update(_double _timeDelta)
{
	if (nullptr == m_pTransform	||
		nullptr == m_pTarget)
		return -1;

	
	Vector3 vTargetPos = m_pTarget->Get_Position();
	m_pTransform->Set_Position(Vector3(vTargetPos.x - (g_iWinCX >> 1), vTargetPos.y - (g_iWinCY >> 1)));


	_matrix scalingMatrix, rotationXMatrix, rotationYMatrix, rotationZMatrix, translationMatrix,
		revolveXMatrix, revolveYMatrix, revolveZMatrix;

	D3DXMatrixTranslation(&translationMatrix, -1.f * vTargetPos.x, -1.f * vTargetPos.y, -1.f * vTargetPos.z);
	D3DXMatrixScaling(&scalingMatrix, 1.f, 1.f, 1.f);


	_matrix matrix = m_pTransform->Get_Matrix() * translationMatrix * scalingMatrix;

	m_pTransform->Update_Transform();
	m_pPipline->Set_CameraMatrix(matrix);
	return 0;
}

_int CCamera::LateUpate(_double _timeDelta)
{
	return _int();
}

CCamera * CCamera::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CCamera* pInstance = new CCamera(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CCamera");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CCamera::Clone(void * _pArg)
{

	CCamera* pInstance = new CCamera(*this);
	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to create CCamera");
		Safe_Release(pInstance);

	}

	return pInstance;
}

void CCamera::Free()
{
	Safe_Release(m_pTransform);

	CGameObject::Free();
}
