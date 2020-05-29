#include "stdafx.h"
#include "Gnoll.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "LevelMgr.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"
#include "Shader.h"

USING(MyGame)

CGnoll::CGnoll(CGnoll & _rhs)
	:CMonster(_rhs)
{
	m_tStat = _rhs.m_tStat;
}

HRESULT CGnoll::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Gnoll/");
	return S_OK;
}

HRESULT CGnoll::Initialize(void * _param)
{

	m_pName = L"그놀";
#pragma region 스텟셋팅

	//스텟셋팅
	m_tStat.m_fExp = 20.f;
	m_tStat.m_fMaxHp = CStat::Create(30.f);
	m_tStat.m_fAtt = CStat::Create(10.f);
	m_tStat.m_iGold = 10;
	m_tStat.m_fArmor = CStat::Create(4.f);
	m_tStat.m_fHP = 30.f;
#pragma endregion

#pragma region 모듈셋팅
	//모듈셋팅
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	_int movePerturn = 1;
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, nullptr, &CTransform::STATEDESC(CalulateSpeed(movePerturn), 100.0, movePerturn))))
		return E_FAIL;
	if (FAILED(Set_Module(L"AIStateCon", SCENE_STATIC, (CModule**)&m_pStateCon)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	//위치 셋팅
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 25.f));
	m_pTransform->Set_ColliderSize(Vector2(25.f, 30.f));



#pragma endregion

#pragma region 상태셋팅
	CAIStateCon* pStateCon = dynamic_cast<CAIStateCon*>(m_pStateCon);
	pStateCon->Set_State(CAIState::STATE_IDLE, new CAIIdle(this));
	pStateCon->Set_State(CAIState::STATE_HUNTING, new CAIHunting(this));
	pStateCon->Set_State(CAIState::STATE_SLEEP, new CAISleeping(this));
	pStateCon->Set_State(CAIState::STATE_WADERING, new CAIWandering(this));
	pStateCon->Set_Default_State(CAIState::STATE_IDLE);

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	Set_Module(L"gnoll_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	Set_Module(L"gnoll_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);

	Set_Module(L"gnoll_dead", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	Set_Module(L"gnoll_walk", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pJumpAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator->Add_Animation(L"walk", pJumpAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pIdleAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"idle");

#pragma endregion





	return S_OK;
}



CGnoll * CGnoll::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CGnoll* pInstance = new CGnoll(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CGnoll");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CGnoll::Clone(void * _param)
{
	CGnoll* pInstance = new CGnoll(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CGnoll");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CGnoll::Free()
{

	CMonster::Free();
}
