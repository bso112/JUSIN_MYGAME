#include "stdafx.h"
#include "Crab.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "World.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"

USING(MyGame)

CCrab::CCrab(CCrab & _rhs)
	:CMonster(_rhs)
{
	m_tStat = _rhs.m_tStat;
}

HRESULT CCrab::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Crab/");
	return S_OK;
}

HRESULT CCrab::Initialize(void * _param)
{

#pragma region 스텟셋팅

	//스텟셋팅
	m_tStat.m_fExp = 20.f;
	m_tStat.m_fMaxHp = CStat::Create(30.f);
	m_tStat.m_fAtt = CStat::Create(6.f);
	m_tStat.m_iGold = 15;
	m_tStat.m_fArmor = CStat::Create(3.f);
	m_tStat.m_fHP = 20.f;
#pragma endregion

#pragma region 모듈셋팅
	//모듈셋팅
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, nullptr, &CTransform::STATEDESC(100.0, 100.0, 3))))
		return E_FAIL;
	if (FAILED(Set_Module(L"AIStateCon", SCENE_STATIC, (CModule**)&m_pStateCon)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator)))
		return E_FAIL;

#pragma endregion

#pragma region 상태셋팅
	m_pStateCon->Set_State(CAIState::STATE_IDLE, new CAIIdle(this));
	m_pStateCon->Set_State(CAIState::STATE_HUNTING, new CAIHunting(this));
	m_pStateCon->Set_State(CAIState::STATE_SLEEP, new CAISleeping(this));
	m_pStateCon->Set_State(CAIState::STATE_WADERING, new CAIWandering(this));
	m_pStateCon->Set_Default_State(CAIState::STATE_SLEEP);

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	Set_Module(L"crab_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	Set_Module(L"crab_sleep", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"sleep", pIdleAnim);

	Set_Module(L"crab_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pSleepAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"idle", pSleepAnim);

	Set_Module(L"crab_dead", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	Set_Module(L"crab_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pJumpAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator->Add_Animation(L"walk", pJumpAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pIdleAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"sleep");

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

_int CCrab::Update(_double _timeDelta)
{
	m_pTransform->Update(_timeDelta);
	return 0;
}

_int CCrab::LateUpate(_double _timeDelta)
{
	m_pTransform->Late_Update();
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;

}

HRESULT CCrab::Act(_int _iTurnCnt)
{

	if (nullptr == m_pFocus)
		return E_FAIL;
	m_pStateCon->Act(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange), _iTurnCnt);

	return S_OK;
}




HRESULT CCrab::Render()
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

CCrab * CCrab::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CCrab* pInstance = new CCrab(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CCrab");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CCrab::Clone(void * _param)
{
	CCrab* pInstance = new CCrab(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CCrab");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CCrab::Process()
{
}

void CCrab::Update_State()
{
}

void CCrab::OnDead()
{
}

void CCrab::OnTakeDamage()
{
}

void CCrab::Scene_Change()
{
}

void CCrab::Free()
{
	Safe_Release(m_pStateCon);
	Safe_Release(m_pAnimator);
	CMonster::Free();
}
