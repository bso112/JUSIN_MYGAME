#include "stdafx.h"
#include "..\Headers\Rat.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "LevelMgr.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"
#include "Shader.h"
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

	m_pName = L"시궁쥐";
#pragma region 스텟셋팅

	//스텟셋팅
	m_tStat.m_fExp = 10.f;
	m_tStat.m_fMaxHp = CStat::Create(25.f);
	m_tStat.m_fHP = 25.f;
	m_tStat.m_fAtt = CStat::Create(1.f, 5.f);
	m_tStat.m_iGold = 5;
	m_tStat.m_fArmor = CStat::Create(2.f);
#pragma endregion

#pragma region 모듈셋팅
	//모듈셋팅
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (nullptr == m_pFocus)
		return E_FAIL;

	//한턴 당 움직이는 타일 수
	_int movePerturn = 1;
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, nullptr,  &CTransform::STATEDESC(CalulateSpeed(movePerturn), 100.0, movePerturn))))
		return E_FAIL;
	if (FAILED(Set_Module(L"AIStateCon", SCENE_STATIC, (CModule**)&m_pStateCon)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;


#pragma endregion

#pragma region 상태셋팅
	CAIStateCon* pStateCon = dynamic_cast<CAIStateCon*>(m_pStateCon);
	pStateCon->Set_State(CAIState::STATE_IDLE, new CAIIdle(this));
	pStateCon->Set_State(CAIState::STATE_HUNTING, new CAIHunting_Jump(this));
	pStateCon->Set_State(CAIState::STATE_SLEEP, new CAISleeping(this));
	pStateCon->Set_State(CAIState::STATE_WADERING, new CAIWandering(this));
	pStateCon->Set_Default_State(CAIState::STATE_IDLE);

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	Set_Module(L"rat_att", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	Set_Module(L"rat_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);

	Set_Module(L"rat_dead", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	Set_Module(L"rat_jump", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pJumpAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator->Add_Animation(L"walk", pJumpAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pIdleAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"idle");

#pragma endregion


	//위치 셋팅
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 20.f));
	m_pTransform->Set_ColliderSize(Vector2(30.f, 30.f));


	CMonster::Initialize(_param);

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

void CRat::OnDead()
{
	CMonster::OnDead();
	if (nullptr == m_pAnimator)
		return;
	m_pAnimator->Play(L"dead");
}



void CRat::Free()
{
	CMonster::Free();
}
