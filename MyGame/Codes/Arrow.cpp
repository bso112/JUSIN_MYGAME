#include "stdafx.h"
#include "..\Headers\Arrow.h"
#include "Character.h"
#include "ObjMgr.h"
USING(MyGame)

HRESULT CArrow::Initialize(void * _param)
{
	CItem::Initialize(_param);

	ZeroMemory(&m_tDesc, sizeof(m_tDesc));

	if (FAILED(Set_Module(L"arrow", SCENE_STAGE, (CModule**)&m_pTexture)))
		return E_FAIL;

	m_pTextureTag = L"arrow";

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &m_tTransformDesc)))
		return E_FAIL;
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(STATEDESC));

	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.m_tBaseDesc.vSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);

	m_pDescription = m_tDesc.m_pDescription;
	m_iTextureID = m_tDesc.m_iTextureID;
	m_pItemName = m_tDesc.m_pItemName;

	m_bStackable = true;

	return S_OK;
}


CArrow * CArrow::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CArrow* pInstance = new CArrow(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CArrow");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CArrow::Clone(void * _param)
{
	CArrow* pInstance = new CArrow(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CArrow");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CArrow::Free()
{
	CItem::Free();
}

void CArrow::OnCollisionEnter(CGameObject * _pOther)
{
	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	//플레이어와 충돌은 무시
	if (nullptr != pCharacter && pCharacter != CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE) && m_bDamagable)
	{
		pCharacter->TakeDamage(m_tDesc.m_tStats.m_fAtt);
		m_bDead = true;
	}
}

void CArrow::OnThrowStart()
{
	m_bDamagable = true;


	if (nullptr != m_pTransform)
	{
		//회전각 구하기
		float fCosTheta = D3DXVec4Dot(&m_vDest.Nomalize(), &Vector4(1.f, 0.f, 0.f));
		float fRadian = 0.f;

		if (m_vDest.y >= m_pTransform->Get_Position().y)
			fRadian = acosf(fCosTheta);
		else
			fRadian = D3DXToRadian(360.0f) - acosf(fCosTheta);

		//fRadian += D3DXToRadian(20.f);

		m_pTransform->Set_Rotation(Vector3(0.f, 0.f, fRadian));

	}
}

void CArrow::OnThrowEnd()
{
	m_pTransform->Set_Rotation(Vector3(0.f, 0.f, 0.f));
	m_bDamagable = false;
	
}

Vector3 CArrow::Get_OriginalSize()
{
	return m_tDesc.m_tBaseDesc.vSize;
}
