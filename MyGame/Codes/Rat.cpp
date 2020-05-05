#include "stdafx.h"
#include "..\Headers\Rat.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "World.h"
#include "Hero.h"
#include "Clock.h"
#include "StateCon.h"

USING(MyGame)

CRat::CRat(CRat & _rhs)
	:CMonster(_rhs)
{
	m_tStat = _rhs.m_tStat;
}

HRESULT CRat::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Rat/");



	return S_OK;
}

HRESULT CRat::Initialize(void * _param)
{

#pragma region 스텟셋팅

	//스텟셋팅
	m_tStat.m_fExp = 10.f;
	m_tStat.m_fMaxHp = CStat::Create(16.f);
	m_tStat.m_fAtt = CStat::Create(5.f);
	m_tStat.m_iGold = 5;
	m_tStat.m_fArmor = CStat::Create(2.f);
	m_tStat.m_fHP = 16.f;
#pragma endregion

#pragma region 모듈셋팅
	//모듈셋팅
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, &CTransform::STATEDESC(100.0, 100.0))))
		return E_FAIL;
	if (FAILED(Set_Module(L"StateCon", SCENE_STATIC, (CModule**)&m_pStateCon)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator)))
		return E_FAIL;

#pragma endregion

#pragma region 상태셋팅
	//상태 셋팅
	m_pHUNTING = CHunting_Jump::Create(this, Vector3(0.f, -7.f, 0.f));
	m_pWANDERING = Wandering::Create(this);
	m_pSLEEPING = Sleeping::Create(this);

	m_pStateCon->AddState(m_pHUNTING);
	m_pStateCon->AddState(m_pWANDERING);
	m_pStateCon->AddState(m_pSLEEPING);

	m_pHUNTING->SetNextState(m_pWANDERING);
	m_pStateCon->Set_Defualt_State(m_pHUNTING);

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	Set_Module(L"rat_att", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	Set_Module(L"rat_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);

	Set_Module(L"rat_dead", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	Set_Module(L"rat_jump", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pJumpAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator->Add_Animation(L"jump", pJumpAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pIdleAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"idle");

#pragma endregion


	//위치 셋팅
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 20.f));


	//멤버변수 셋팅
	m_iRecogRange = 5;
	m_iAttackRange = 1;




	return S_OK;
}

_int CRat::Update(_double _timeDelta)
{
	m_pTransform->Update(_timeDelta);
	m_pStateCon->Update(_timeDelta);
	return 0;
}

_int CRat::LateUpate(_double _timeDelta)
{
	m_pTransform->Late_Update();
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;

}

HRESULT CRat::Act(_int _iTurnCnt)
{
	if (nullptr == m_pHero)
		return E_FAIL;

	//타깃이 인식범위 안에 있으면
	if (IsTargetInRange(m_pHero, m_iRecogRange))
	{
		CTransform* pHeroTransform = (CTransform*)m_pHero->Get_Module(L"Transform");
		if (nullptr == pHeroTransform)
			return E_FAIL;

		//타깃을 향해 간다.
		m_pTransform->Go_Target(pHeroTransform, 1.f, _iTurnCnt);
		m_pAnimator->Play(L"jump");

	}


	//만약 타깃이 공격범위 안에 들어오면 공격한다.
	if (IsTargetInRange(m_pHero, m_iAttackRange))
	{
		m_pHero->TakeDamage(m_tStat.m_fAtt->GetValue());
		m_pAnimator->Play(L"attack");
	}


	return S_OK;
}




HRESULT CRat::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pAnimator ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pAnimator->Render()))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	ALPHABLEND_END;

	return S_OK;
}

CRat * CRat::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CRat* pInstance = new CRat(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CRat");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CRat::Clone(void * _param)
{
	CRat* pInstance = new CRat(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CRat");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CRat::Process()
{
}

void CRat::Update_State()
{
}

void CRat::OnDead()
{
}

void CRat::OnTakeDamage()
{
}

void CRat::Scene_Change()
{
}

void CRat::Free()
{
	Safe_Release(m_pStateCon);
	Safe_Release(m_pAnimator);
	CMonster::Free();
}

CState* CHunting_Jump::Update(_double _timeDelta)
{
	m_vJumpVelo -= m_vJumpVelo * float(_timeDelta);
	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	pTransform->Add_Froce(m_vJumpVelo.Nomalize(), 2.f, _timeDelta);

	if (m_vJumpVelo.y > 0)
	{
		return m_pNextState;
	}

	return nullptr;
}

CHunting_Jump * CHunting_Jump::Create(CCharacter* _pActor, Vector3 _vJumpVelo)
{
	CHunting_Jump* pInstance = new CHunting_Jump(_pActor);
	if (FAILED(pInstance->Initialize(_vJumpVelo)))
	{
		MSG_BOX("Fail to create CHunting_Jump");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CHunting_Jump::Free()
{
}

HRESULT CHunting_Jump::Initialize(Vector3 _vJumpVelo)
{
	m_vJumpVelo = _vJumpVelo;
	return S_OK;
}
