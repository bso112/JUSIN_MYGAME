#include "stdafx.h"
#include "..\Headers\Warrior.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "TextureLoader.h"
#include "Shader.h"
#include "Animator.h"
#include "PlayerStateCon.h"
USING(MyGame)


CWarrior::CWarrior(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CHero(_pGraphic_Device)
{
};

CWarrior::CWarrior(CWarrior & _hero)
	: CHero(_hero)
{

}

CWarrior * CWarrior::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar * _pFilePath)
{
	CWarrior* pInstance = new CWarrior(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CWarrior");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CWarrior::Clone(void * _param)
{
	CWarrior* pInstance = new CWarrior(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CWarrior");
		Safe_Release(pInstance);

	}
	return pInstance;
}


HRESULT CWarrior::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Hero/warrior/");

	return S_OK;
}

HRESULT CWarrior::Initialize(void * _param)
{

#pragma region 스텟준비

	//스텟셋팅
	m_tStat.m_fExp = 0.f;
	m_tStat.m_fMaxHp = CStat::Create(50.f);
	m_tStat.m_fAtt = CStat::Create(10.f);
	m_tStat.m_iGold = 0;
	m_tStat.m_fArmor = CStat::Create(5.f);
	m_tStat.m_fHP = 800.f;
#pragma endregion

#pragma region 모듈준비
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, nullptr, &CTransform::STATEDESC(100.f, 100.f));
	Set_Module(L"PlayerStateCon", SCENE_STATIC, (CModule**)&m_pStateCon);

	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator[CLOTH_NAKED], L"Animator_Naked");
	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator[CLOTH_BASIC], L"Animator_Basic");
	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator[CLOTH_LEATHER], L"Animator_Leather");



	m_pTransform->Set_Position(Vector3((_float)(g_iWinCX >> 1), (_float)(g_iWinCY >> 1)));
	m_pTransform->Set_Size(Vector3(20.f, 25.f));
#pragma endregion

#pragma region 상태설정
	m_pStateCon->Set_State(CPlayerState::STATE_IDLE, new CPlayerIdle(this));
	m_pStateCon->Set_State(CPlayerState::STATE_USING, new CPlayerUsing(this));
	m_pStateCon->Set_State(CPlayerState::STATE_WALK, new CPlayerWalk(this));
	m_pStateCon->Set_Default_State(CPlayerState::STATE_IDLE);
#pragma endregion

#pragma region 애니메이션 설정


	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	Set_Module(L"warrior_naked_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"idle", pNakedIdleAnim);

	Set_Module(L"warrior_naked_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedAttackAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"attack", pNakedAttackAnim);

	Set_Module(L"warrior_naked_eat", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedEatAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"eat", pNakedEatAnim);

	Set_Module(L"warrior_naked_floating", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedFloatingAnim = CAnimation::Create(pTexture, 0.2, true);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"floating", pNakedFloatingAnim);

	Set_Module(L"warrior_naked_use", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedUseAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"use", pNakedUseAnim);

	Set_Module(L"warrior_naked_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedWalkAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"walk", pNakedWalkAnim);


	pNakedAttackAnim->Set_NextAnim(pNakedIdleAnim);
	pNakedEatAnim->Set_NextAnim(pNakedIdleAnim);
	pNakedUseAnim->Set_NextAnim(pNakedIdleAnim);

	Set_Module(L"warrior_cloth_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"idle", pClothIdleAnim);

	Set_Module(L"warrior_cloth_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothAttackAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"attack", pClothAttackAnim);

	Set_Module(L"warrior_cloth_eat", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothEatAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"eat", pClothEatAnim);

	Set_Module(L"warrior_cloth_floating", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothFloatingAnim = CAnimation::Create(pTexture, 0.2, true);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"floating", pClothFloatingAnim);

	Set_Module(L"warrior_cloth_use", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothUseAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"use", pClothUseAnim);

	Set_Module(L"warrior_cloth_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothWalkAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"walk", pClothWalkAnim);

	pClothAttackAnim->Set_NextAnim(pClothIdleAnim);
	pClothEatAnim->Set_NextAnim(pClothIdleAnim);
	pClothUseAnim->Set_NextAnim(pClothIdleAnim);



	Set_Module(L"warrior_leather_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"idle", pLeatherIdleAnim);

	Set_Module(L"warrior_leather_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherAttackAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"attack", pLeatherAttackAnim);

	Set_Module(L"warrior_leather_eat", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherEatAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"eat", pLeatherEatAnim);

	Set_Module(L"warrior_leather_floating", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherFloatingAnim = CAnimation::Create(pTexture, 0.2, true);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"floating", pLeatherFloatingAnim);

	Set_Module(L"warrior_leather_use", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherUseAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"use", pLeatherUseAnim);

	Set_Module(L"warrior_leather_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherWalkeAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"walk", pLeatherWalkeAnim);

	pLeatherAttackAnim->Set_NextAnim(pLeatherIdleAnim);
	pLeatherEatAnim->Set_NextAnim(pLeatherIdleAnim);
	pLeatherUseAnim->Set_NextAnim(pLeatherIdleAnim);


#pragma endregion

	m_pAnimator[m_eCurrCloth]->Play(L"idle");


	return S_OK;
}

HRESULT CWarrior::KeyCheck(_double _timeDelta)
{
	CHero::KeyCheck(_timeDelta);

	return S_OK;
}

_int CWarrior::Update(_double _timeDelta)
{
	KeyCheck(_timeDelta);
	m_pTransform->Update(_timeDelta);
	return 0;
}

_int CWarrior::LateUpate(_double _timeDelta)
{
	m_pTransform->Late_Update();
	m_pStateCon->LateUpdate(IsTargetInRange(m_pFocus, m_iAttackRange), false);

	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;
}

HRESULT CWarrior::Render()
{
	if (nullptr == m_pVIBuffer ||
		nullptr == m_pAnimator ||
		nullptr == m_pTransform)
		return E_FAIL;


	ALPHABLEND;

	if (FAILED(m_pAnimator[m_eCurrCloth]->Render()))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix())))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	ALPHABLEND_END;

	return S_OK;
}


void CWarrior::OnCollisionEnter(CGameObject * _pOther)
{

}

void CWarrior::Scene_Change()
{
}

void CWarrior::Process()
{
}

void CWarrior::Update_State()
{
}

void CWarrior::OnDead()
{
}

void CWarrior::OnTakeDamage()
{
	if (nullptr == m_pTransform)
		return;

	m_pTransform->Stop();

}

void CWarrior::Free()
{

	for (int i = 0; i < CLOTH_END; ++i)
		Safe_Release(m_pAnimator[i]);
	Safe_Release(m_pStateCon);
	Safe_Release(m_pShader);

	CHero::Free();
}

HRESULT CWarrior::Act(_int _iTurnCnt)
{
	m_pStateCon->Act(IsTargetInRange(m_pFocus, m_iAttackRange), false ,_iTurnCnt);
	return S_OK;
}

