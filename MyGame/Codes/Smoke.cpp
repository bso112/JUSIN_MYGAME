#include "stdafx.h"
#include "Smoke.h"
#include "ObjMgr.h"
#include "Character.h"
#include "Clock.h"
#include "TurnMgr.h"
#include "Damage.h"
#include "Paralyze.h"

USING(MyGame)
CSmoke::CSmoke(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CEffect(_pGraphic_Device)
{
	ZeroMemory(&m_tDesc, sizeof(m_tDesc));
}

CSmoke::CSmoke(CSmoke & _rhs)
	: CEffect(_rhs)
{
	ZeroMemory(&m_tDesc, sizeof(m_tDesc));

}


//프리펩이라고 생각해보자.
HRESULT CSmoke::Initialize_Prototype(_tchar * _pFilePath)
{

	return S_OK;
}

HRESULT CSmoke::Initialize(void * _pArg)
{


	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform");

	//Fire의 위치 정함.
	if (nullptr != _pArg)
	{
		m_tDesc = *((STATEDESC*)_pArg);
		m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);

	}

	m_pTransform->Set_Size(Vector3((_float)TILECX * RANGE, (_float)TILECY * RANGE, 1.f));
	m_pTransform->Set_ColliderSize(Vector3((_float)TILECX* RANGE, (_float)TILECY* RANGE, 1.f));

	const _tchar* pTextureTag = L"";
	switch (m_tDesc.m_tBuffType)
	{
	case CBuff::TYPE_POISION:
		pTextureTag = L"poision";
		break;
	case CBuff::TYPE_PARALIZE:
		pTextureTag = L"paralize";
		break;
	default:
		break;
	}

	//이펙트 지속시간 설정(턴)
	m_iDuration = DURAION_IN_TURN;
	m_tParticleDesc.m_dDuration = FLT_MAX;
	m_tParticleDesc.m_dLifeTime = 2.f;
	m_tParticleDesc.m_eTextureSceneID = SCENE_STAGE;
	m_tParticleDesc.m_fSpeed = 50.f;
	m_tParticleDesc.m_pTextureTag = pTextureTag;
	m_tParticleDesc.m_tBaseDesc.vPos = m_pTransform->Get_Position();
	m_tParticleDesc.m_tBaseDesc.vSize = m_pTransform->Get_Size();
	m_tParticleDesc.m_vParticleSize = Vector2(25.f, 25.f);
	m_tParticleDesc.m_iShaderPass = 4;

	m_pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &m_tParticleDesc));
	RETURN_FAIL_IF_NULL(m_pParticleSystem);
	//맞지? 레이어에도 있고 멤버변수에도 있으니까.
	Safe_AddRef(m_pParticleSystem);
	m_pParticleSystem->Set_FadeOut();

	//파티클 시스템의 부모를 fire로 지정
	CTransform* pPsTransform = dynamic_cast<CTransform*>(m_pParticleSystem->Get_Module(L"Transform"));
	if (nullptr != pPsTransform)
	{
		pPsTransform->Set_Parent(m_pTransform);
	}

	m_pSpawnTimer = CClock_Trigger::Create();


	CBuff::STATS stats;
	if(m_tDesc.m_tBuffType == CBuff::TYPE_POISION)
		m_BuffDesc.m_iDuration = DURAION_IN_TURN;
	else if(m_tDesc.m_tBuffType == CBuff::TYPE_PARALIZE)
		m_BuffDesc.m_iDuration = DURAION_IN_TURN;
	m_BuffDesc.m_tStats = stats;
	m_BuffDesc.m_eType = m_tDesc.m_tBuffType;

	return S_OK;
}

void CSmoke::Play()
{
	if (nullptr == m_pParticleSystem ||
		nullptr == m_pTransform)
		return;

	m_bPlaying = true;
}

HRESULT CSmoke::EffectOn(CCharacter * _pTarget)
{
	if (nullptr == _pTarget)
		return E_FAIL;

	switch (m_BuffDesc.m_eType)
	{
	case CBuff::TYPE_PARALIZE:
		_pTarget->Add_Buff(CParalyze::Create(&m_BuffDesc));
		break;
	default:
		_pTarget->Add_Buff(CDamage::Create(&m_BuffDesc));
		break;
	}
	return S_OK;
}


_int CSmoke::Update(_double _timeDelta)
{
	if (m_bDead)
		return -1;


	if (nullptr == m_pSpawnTimer)
		return -1;

	if (!m_bPlaying)
		return 0;


	if (nullptr == m_pParticleSystem)
		return -1;


	//0.5초마다 생성
	if (m_pSpawnTimer->isThreashHoldReached(0.5f))
		m_pParticleSystem->SmokeUp(m_pTransform->Get_RECT(), 5);

	return 0;
}

_int CSmoke::LateUpate(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	m_pTransform->Update_Transform();


	return 0;
}

HRESULT CSmoke::Render()
{


	return S_OK;
}




void CSmoke::OnCollisionEnter(CGameObject * _pOther)
{

	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	if (nullptr != pCharacter)
	{
		EffectOn(pCharacter);
	}

}

CSmoke * CSmoke::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CSmoke* pInstance = new CSmoke(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CSmoke");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CSmoke::Clone(void * _param)
{
	CSmoke* pInstance = new CSmoke(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CSmoke");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CSmoke::Free()
{

	Safe_Release(m_pSpawnTimer);
	CEffect::Free();
}


