#include "stdafx.h"
#include "Goo.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "LevelMgr.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"
#include "Shader.h"
#include "QuestMgr.h"

USING(MyGame)

CGoo::CGoo(CGoo & _rhs)
	:CMonster(_rhs),
	m_iHitCnt(0)
{
	//m_tStat = _rhs.m_tStat;
}

HRESULT CGoo::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Goo/");
	return S_OK;
}

HRESULT CGoo::Initialize(void * _param)
{

	m_pName = L"검은 슬라임";
#pragma region 스텟셋팅

	//스텟셋팅
	m_tStat.m_fExp = 20.f;
	m_tStat.m_fMaxHp = CStat::Create(100.f);
	m_tStat.m_fHP = 100.f;
	m_tStat.m_fAtt = CStat::Create(5.f, 15.f);
	m_tStat.m_iGold = 100;
	m_tStat.m_fArmor = CStat::Create(5.f);
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

	m_pTransform->Set_Size(Vector2(30.f, 30.f));
	m_pTransform->Set_ColliderSize(Vector2(25.f, 25.f));



#pragma endregion

#pragma region 상태셋팅
	CAIStateCon* pStateCon = dynamic_cast<CAIStateCon*>(m_pStateCon);
	pStateCon->Set_State(CAIState::STATE_IDLE, new CAIIdle(this));
	pStateCon->Set_State(CAIState::STATE_HUNTING, new CAIHunting(this));
	pStateCon->Set_State(CAIState::STATE_SLEEP, new CAISleeping(this));
	if (nullptr == m_pFocus)
		return E_FAIL;
	pStateCon->Set_Default_State(CAIState::STATE_SLEEP, IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	if (FAILED(Set_Module(L"goo_attack", SCENE_STAGE, (CModule**)&pTexture)))
		return E_FAIL;
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	if (FAILED(Set_Module(L"goo_idle", SCENE_STAGE, (CModule**)&pTexture)))
		return E_FAIL;
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 0.3, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);

	if (FAILED(Set_Module(L"goo_dead", SCENE_STAGE, (CModule**)&pTexture)))
		return E_FAIL;
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	//idle애니메이션을 빠르게 한 것
	if(FAILED(Set_Module(L"goo_idle", SCENE_STAGE, (CModule**)&pTexture, L"goo_walk")))
		return E_FAIL;
	CAnimation* pWalkAnim = CAnimation::Create(pTexture, 0.05, true);
	m_pAnimator->Add_Animation(L"rage", pWalkAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pWalkAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"idle");

#pragma endregion



	CMonster::Initialize(_param);

	//멤버변수 셋팅
	m_iRecogRange = 5;
	m_iAttackRange = 1;


	return S_OK;
}

void CGoo::OnDead()
{
	CMonster::OnDead();
	if (nullptr == m_pAnimator)
		return;
	m_pAnimator->Play(L"dead");
	CQuestMgr::Get_Instance()->SetQuestEnd();
}

void CGoo::OnTakeDamage(float _fDamage)
{
	CMonster::OnTakeDamage(_fDamage);
	
	++m_iHitCnt;
	if (m_iHitCnt == 3)
	{
		//분노
		ShowText(L"!!!", COLOR_RED);
		m_tStat.m_fAtt->AddModifier(10.f);
		m_pAnimator->Play(L"rage");
	}
}


CGoo * CGoo::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CGoo* pInstance = new CGoo(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CGoo");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CGoo::Clone(void * _param)
{
	CGoo* pInstance = new CGoo(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CGoo");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CGoo::Free()
{

	CMonster::Free();
}
