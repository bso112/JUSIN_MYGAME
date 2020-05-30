#include "stdafx.h"
#include "..\Headers\Potion.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "TimerMgr.h"
#include "Character.h"
#include "Hero.h"
USING(MyGame)

CPotion::CPotion(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
}

CPotion::CPotion(CPotion & _rhs)
	:CItem(_rhs)
{
}

HRESULT CPotion::Initialize(void * _param)
{
	CItem::Initialize(_param);
	m_vecActions.push_back(AC_DRINK);

	Set_Module(L"potion", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"potion";
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);


	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(STATEDESC));

	m_vOriginalSize = Vector2(30.f, 25.f);
	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_vOriginalSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);


	m_pDescription = m_tDesc.m_pDescription;
	m_iTextureID = m_tDesc.m_iTextureID;
	m_pItemName = m_tDesc.m_pItemName;


	return S_OK;
}

HRESULT CPotion::Use(CHero * _pHero, const _tchar ** _pAction)
{
	if (nullptr == _pHero)
		return E_FAIL;
	CItem::Use(_pHero, _pAction);
	if (0 == lstrcmp(*_pAction, AC_DRINK))
	{
		//����
		m_bUsed = true;
		m_bDead = true;
		_pHero->Heal(m_tDesc.m_tStats.m_fHp);
	}
	return S_OK;
}

void CPotion::OnThrowEnd()
{
	if (nullptr == m_pTransform)
		return;

#pragma region ������ ��ƼŬ
	//�� ��ƼŬ ����
	Vector3 vPos = m_pTransform->Get_Position();
	CParticleSystem::STATEDESC desc;
	desc.m_tBaseDesc.vPos = m_pTransform->Get_Position();
	desc.m_pTextureTag = L"Blood";
	desc.m_eTextureSceneID = SCENE_STAGE;
	desc.m_dDuration = 0.2f;
	desc.m_dLifeTime = 0.2f;
	desc.m_fSpeed = 300.f;
	desc.m_vParticleSize = Vector2(10.f, 10.f);
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	CParticleSystem* pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &desc));

	//�ǰ� Ƣ���.
	pParticleSystem->Spread(Vector3(0.f,-1.f,0.f), CTimerMgr::Get_Instance()->Get_TimeDelta(), 5);
#pragma endregion

	m_bDead = true;


}

HRESULT CPotion::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer ||
		nullptr == m_pTransform ||
		nullptr == m_pPipline)
		return E_FAIL;

	_matrix matrix;

	if (m_bDrop)
		matrix = m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix();
	//���Կ� ���������� ī�޶� ��Ʈ���� ����ȹ��� 
	else
	{
		matrix = m_pTransform->Get_Matrix();
	}

	ALPHABLEND;

	if (FAILED(m_pVIBuffer->Set_Transform(matrix)))
		return E_FAIL;

	//�ؽ���ID�� 1���� ����
	if (FAILED(m_pTexture->Set_Texture(m_iTextureID - 1)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	ALPHABLEND_END;

#ifdef MYDEBUG

	m_pTransform->Render_Collider();
#endif // MYDEBUG

}

Vector3 CPotion::Get_OriginalSize()
{
	return m_vOriginalSize;
}

void CPotion::OnCollisionEnter(CGameObject * _pOther)
{
	if (nullptr == _pOther)
		return;
	
	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);

	if (nullptr == pCharacter)
		return;

	pCharacter->TakeDamage(3.f);
	m_bDead = true;
}

CPotion* CPotion::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CPotion* pInstance = new CPotion(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CPotion");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CPotion * CPotion::Clone(void * _param)
{
	CPotion* pInstance = new CPotion(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CPotion");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CPotion::Free()
{
}
