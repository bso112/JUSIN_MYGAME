#include "stdafx.h"
#include "..\Headers\Warrior.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer.h"
#include "TextureLoader.h"
#include "Shader.h"
#include "Animator.h"
#include "PlayerStateCon.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
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

	m_eSceneID = CSceneMgr::Get_Instance()->Get_CurrScene();
	if (m_eSceneID >= SCENE_END)
		return E_FAIL;
	CKeyMgr::Get_Instance()->RegisterObserver(m_eSceneID, this);

	m_iDepth = 10;


#pragma region 스텟준비

	//스텟셋팅
	m_tStat.m_fExp = 0.f;
	m_tStat.m_fMaxHp = CStat::Create(50.f);
	m_tStat.m_fAtt = CStat::Create(1.f, 5.f);
	m_tStat.m_iGold = 0;
	m_tStat.m_fArmor = CStat::Create(5.f);
	m_tStat.m_fHP = 800.f;

	m_iAttackRange = 1;
#pragma endregion

#pragma region 모듈준비
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, nullptr, &CTransform::STATEDESC(250.f, 100.f, 1));
	Set_Module(L"PlayerStateCon", SCENE_STATIC, (CModule**)&m_pStateCon);
	Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader);

	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator[CLOTH_NAKED], L"Animator_Naked");
	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator[CLOTH_BASIC], L"Animator_Basic");
	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator[CLOTH_LEATHER], L"Animator_Leather");


	Set_InitialPos();
	m_pTransform->Set_Size(Vector3(20.f, 25.f));
#pragma endregion

#pragma region 상태설정
	CPlayerStateCon* pStateCon = dynamic_cast<CPlayerStateCon*>(m_pStateCon);
	pStateCon->Set_State(CPlayerState::STATE_IDLE, new CPlayerIdle(this));
	pStateCon->Set_State(CPlayerState::STATE_USING, new CPlayerUsing(this));
	pStateCon->Set_State(CPlayerState::STATE_WALK, new CPlayerWalk(this));
	pStateCon->Set_Default_State(CPlayerState::STATE_IDLE);
#pragma endregion

#pragma region 애니메이션 설정

	_double idleAnimSpeed = 1.0;
	_double attackAnimSpeed = 0.1;
	_double eatAnimSpeed = 0.2;
	_double floatAnimSpeed = 0.2;
	_double useAnimSpeed = 0.2;
	_double walkAnimSpeed = 0.02;

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	Set_Module(L"warrior_naked_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedIdleAnim = CAnimation::Create(pTexture, idleAnimSpeed, true);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"idle", pNakedIdleAnim);

	Set_Module(L"warrior_naked_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedAttackAnim = CAnimation::Create(pTexture, attackAnimSpeed, false);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"attack", pNakedAttackAnim);

	Set_Module(L"warrior_naked_eat", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedEatAnim = CAnimation::Create(pTexture, eatAnimSpeed, false);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"eat", pNakedEatAnim);

	Set_Module(L"warrior_naked_floating", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedFloatingAnim = CAnimation::Create(pTexture, floatAnimSpeed, true);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"floating", pNakedFloatingAnim);

	Set_Module(L"warrior_naked_use", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedUseAnim = CAnimation::Create(pTexture, useAnimSpeed, false);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"use", pNakedUseAnim);

	Set_Module(L"warrior_naked_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pNakedWalkAnim = CAnimation::Create(pTexture, walkAnimSpeed, true);
	m_pAnimator[CLOTH_NAKED]->Add_Animation(L"walk", pNakedWalkAnim);


	pNakedAttackAnim->Set_NextAnim(pNakedIdleAnim);
	pNakedEatAnim->Set_NextAnim(pNakedIdleAnim);
	pNakedUseAnim->Set_NextAnim(pNakedIdleAnim);

	Set_Module(L"warrior_cloth_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothIdleAnim = CAnimation::Create(pTexture, idleAnimSpeed, true);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"idle", pClothIdleAnim);

	Set_Module(L"warrior_cloth_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothAttackAnim = CAnimation::Create(pTexture, attackAnimSpeed, false);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"attack", pClothAttackAnim);

	Set_Module(L"warrior_cloth_eat", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothEatAnim = CAnimation::Create(pTexture, eatAnimSpeed, false);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"eat", pClothEatAnim);

	Set_Module(L"warrior_cloth_floating", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothFloatingAnim = CAnimation::Create(pTexture, floatAnimSpeed, true);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"floating", pClothFloatingAnim);

	Set_Module(L"warrior_cloth_use", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothUseAnim = CAnimation::Create(pTexture, useAnimSpeed, false);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"use", pClothUseAnim);


	Set_Module(L"warrior_cloth_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pClothWalkAnim = CAnimation::Create(pTexture, walkAnimSpeed, true);
	m_pAnimator[CLOTH_BASIC]->Add_Animation(L"walk", pClothWalkAnim);


	pClothAttackAnim->Set_NextAnim(pClothIdleAnim);
	pClothEatAnim->Set_NextAnim(pClothIdleAnim);
	pClothUseAnim->Set_NextAnim(pClothIdleAnim);



	Set_Module(L"warrior_leather_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherIdleAnim = CAnimation::Create(pTexture, idleAnimSpeed, true);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"idle", pLeatherIdleAnim);

	Set_Module(L"warrior_leather_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherAttackAnim = CAnimation::Create(pTexture, attackAnimSpeed, false);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"attack", pLeatherAttackAnim);

	Set_Module(L"warrior_leather_eat", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherEatAnim = CAnimation::Create(pTexture, eatAnimSpeed, false);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"eat", pLeatherEatAnim);

	Set_Module(L"warrior_leather_floating", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherFloatingAnim = CAnimation::Create(pTexture, floatAnimSpeed, true);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"floating", pLeatherFloatingAnim);

	Set_Module(L"warrior_leather_use", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherUseAnim = CAnimation::Create(pTexture, useAnimSpeed, false);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"use", pLeatherUseAnim);

	Set_Module(L"warrior_leather_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pLeatherWalkeAnim = CAnimation::Create(pTexture, walkAnimSpeed, true);
	m_pAnimator[CLOTH_LEATHER]->Add_Animation(L"walk", pLeatherWalkeAnim);

	pLeatherAttackAnim->Set_NextAnim(pLeatherIdleAnim);
	pLeatherEatAnim->Set_NextAnim(pLeatherIdleAnim);
	pLeatherUseAnim->Set_NextAnim(pLeatherIdleAnim);

	m_pAnimator[m_eCurrCloth]->Play(L"idle");

#pragma endregion

	m_pTransform->Set_ColliderSize(Vector2(30.f, 30.f));


	return S_OK;
}


_int CWarrior::Update(_double _timeDelta)
{
	if (!m_bActive)
		return 0;
	m_pTransform->Update_Route(_timeDelta);
	return 0;
}

_int CWarrior::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	m_pTransform->Update_Transform();

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
		nullptr == m_pTransform	||
		nullptr == m_pPipline)
		return E_FAIL;
	
	if (!m_bActive)
		return S_OK;

	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
		return E_FAIL;

	ALPHABLEND;

	if (FAILED(m_pAnimator[m_eCurrCloth]->Render(m_pShader)))
		return E_FAIL;


	if (FAILED(m_pShader->Begin()))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Pass(m_iPass)))
		return E_FAIL;
	
	//반짝거리는 거였으면 원상복귀
	if (m_iPass == 3)
		m_iPass = 0;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

#ifdef MYDEBUG
	m_pTransform->Render_Collider();

	_tchar szBuff[MAX_PATH] = L"";
	wsprintf(szBuff, L"X: %d, Y: %d", (_int)m_pTransform->Get_Position().x, (_int)m_pTransform->Get_Position().y);

	g_pFont->DrawText(NULL, szBuff, -1, &m_pTransform->Get_RECT(), DT_CENTER | DT_VCENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif // MYDEBUG


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;


	ALPHABLEND_END;





	return S_OK;
}


void CWarrior::OnCollisionEnter(CGameObject * _pOther)
{
	if (!m_bActive)
		return;
}



void CWarrior::Free()
{
	if (m_eSceneID >= SCENE_END)
		return;

	CKeyMgr::Get_Instance()->UnRegisterObserver(m_eSceneID, this);


	CHero::Free();
}



