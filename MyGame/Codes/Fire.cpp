#include "stdafx.h"
#include "Fire.h"
#include "ObjMgr.h"
#include "Character.h"
#include "Clock.h"
#include "TurnMgr.h"
#include "Damage.h"

USING(MyGame)
CFire::CFire(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CEffect(_pGraphic_Device)
{
	ZeroMemory(&m_tDesc, sizeof(m_tDesc));
}

CFire::CFire(CFire & _rhs)
	: CEffect(_rhs)
{
	ZeroMemory(&m_tDesc, sizeof(m_tDesc));

}


//�������̶�� �����غ���.
HRESULT CFire::Initialize_Prototype(_tchar * _pFilePath)
{

	return S_OK;
}

HRESULT CFire::Initialize(void * _pArg)
{


	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform");

	//Fire�� ��ġ ����.
	if (nullptr != _pArg)
	{
		m_tDesc = *((STATEDESC*)_pArg);
		m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	}

	m_pTransform->Set_Size(Vector3(TILECX, TILECY, 1.f));
	m_pTransform->Set_ColliderSize(Vector3(TILECX, TILECY, 1.f));


	//����Ʈ ���ӽð� ����(��)
	m_iDuration = 3;
	//�� ��ƼŬ�ý��� ����
	//��ƼŬ���ӽð��� Fire���� �ϱ������� �����Ѵ�.
	m_tParticleDesc.m_dDuration = FLT_MAX;
	m_tParticleDesc.m_dLifeTime = 0.7f;
	m_tParticleDesc.m_eTextureSceneID = SCENE_STAGE;
	m_tParticleDesc.m_fSpeed = 80.f;
	m_tParticleDesc.m_pTextureTag = L"Fire";
	m_tParticleDesc.m_tBaseDesc.vPos = m_pTransform->Get_Position();
	m_tParticleDesc.m_tBaseDesc.vSize = m_pTransform->Get_Size();
	m_tParticleDesc.m_vParticleSize = Vector2(5.f, 5.f);
	m_tParticleDesc.m_iShaderPass = 4;

	m_pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &m_tParticleDesc));
	RETURN_FAIL_IF_NULL(m_pParticleSystem);
	//����? ���̾�� �ְ� ����������� �����ϱ�.
	Safe_AddRef(m_pParticleSystem);
	m_pParticleSystem->Set_FadeOut();

	//��ƼŬ �ý����� �θ� fire�� ����
	CTransform* pPsTransform = dynamic_cast<CTransform*>(m_pParticleSystem->Get_Module(L"Transform"));
	if (nullptr != pPsTransform)
	{
		pPsTransform->Set_Parent(m_pTransform);
	}

	m_pSpawnTimer = CClock_Trigger::Create();


	CDamage::STATS stats;
	m_BurnDesc.m_iDuration = m_iDuration;
	m_BurnDesc.m_tStats = stats;
	m_BurnDesc.m_eType = m_tDesc.m_tBuffType;

	return S_OK;
}

void CFire::Play()
{
	if (nullptr == m_pParticleSystem ||
		nullptr == m_pTransform)
		return;

	m_bPlaying = true;
}

HRESULT CFire::EffectOn(CCharacter * _pTarget)
{
	if (nullptr == _pTarget)
		return E_FAIL;
	//�÷���
	Play();
	//���󰡱�
	CTransform* pTargetTrasform = (CTransform*)_pTarget->Get_Module(L"Transform");
	if (nullptr == pTargetTrasform) return E_FAIL;
	Set_Target(pTargetTrasform);
	//ȭ��������
	_pTarget->Add_Buff(CDamage::Create(&m_BurnDesc));
	return S_OK;
}


_int CFire::Update(_double _timeDelta)
{
	if (m_bDead)
		return -1;


	if (nullptr == m_pSpawnTimer)
		return -1;

	if (!m_bPlaying)
		return 0;


	if (nullptr == m_pParticleSystem)
		return -1;

	//Ÿ���� ���ذ���.
	if (nullptr != m_pTarget)
	{
		m_pTransform->Set_Position(m_pTarget->Get_WorldPos());
	}

	//0.5�ʸ��� ����
	if (m_pSpawnTimer->isThreashHoldReached(0.2))
		m_pParticleSystem->FireUp(m_pTransform->Get_RECT(), 10);

	return 0;
}

_int CFire::LateUpate(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	m_pTransform->Update_Transform();


	return 0;
}

HRESULT CFire::Render()
{


	return S_OK;
}




void CFire::OnCollisionEnter(CGameObject * _pOther)
{
	if (!m_bCollidableEffect)
		return;

	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	if (nullptr != pCharacter)
	{
		//�Һٴ´�.
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		
		EffectOn(pCharacter);
		m_bCollidableEffect = false;

	}

}

CFire * CFire::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CFire* pInstance = new CFire(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CFire");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CFire::Clone(void * _param)
{
	CFire* pInstance = new CFire(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CFire");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CFire::Free()
{
	Safe_Release(m_pSpawnTimer);
	CEffect::Free();
}


