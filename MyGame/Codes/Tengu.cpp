#include "stdafx.h"
#include "Tengu.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "LevelMgr.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"
#include "Shader.h"
#include "StageUIMgr.h"
#include "SoundMgr.h"
USING(MyGame)

CTengu::CTengu(CTengu & _rhs)
	:CMonster(_rhs),
	m_iHitCnt(0)
{
	m_tStat = _rhs.m_tStat;
}

HRESULT CTengu::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Tengu/");
	return S_OK;
}

HRESULT CTengu::Initialize(void * _param)
{

	m_pName = L"텐구 암살자";
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
	pStateCon->Set_State(CAIState::STATE_HUNTING, new CAITengu(this));
	
	if (nullptr == m_pFocus)
		return E_FAIL;
	pStateCon->Set_Default_State(CAIState::STATE_IDLE, IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;

	if (FAILED(Set_Module(L"tengu_attack", SCENE_STAGE, (CModule**)&pTexture)))
		return E_FAIL;
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	if (FAILED(Set_Module(L"tengu_idle", SCENE_STAGE, (CModule**)&pTexture)))
		return E_FAIL;
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);

	if (FAILED(Set_Module(L"tengu_dead", SCENE_STAGE, (CModule**)&pTexture)))
		return E_FAIL;
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.3, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	//idle애니메이션을 빠르게 한 것
	if (FAILED(Set_Module(L"tengu_sunbo", SCENE_STAGE, (CModule**)&pTexture)))
		return E_FAIL;
	CAnimation* pSunboAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"sunbo", pSunboAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pIdleAnim);
	pSunboAnim->Set_NextAnim(pIdleAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"idle");

#pragma endregion



	CMonster::Initialize(_param);

	//멤버변수 셋팅
	m_iRecogRange = 5;
	m_iAttackRange = 1;


	return S_OK;
}

void CTengu::Sunbo()
{
	if (nullptr == m_pTransform	||
		nullptr == m_pFocus)
		return;

	CSoundMgr::Get_Instance()->PlaySound_Overwrite(L"snd_puff.mp3", CSoundMgr::MONSTER);
	Vector3 ranPos = CLevelMgr::Get_Instance()->Get_RandomPos(m_pTransform->Get_Position(), 3);
	m_pTransform->Set_Position(ranPos);
	CTransform* pFocusTransform = dynamic_cast<CTransform*>(m_pFocus->Get_Module(L"Transform"));
	if (nullptr == pFocusTransform) return;
	m_pTransform->FaceDir((pFocusTransform->Get_Position() - m_pTransform->Get_Position()).Nomalize());
}

void CTengu::OnDead()
{
	CMonster::OnDead();
	if (nullptr == m_pAnimator)
		return;

	m_pAnimator->Play(L"dead");
	CStageUIMgr* pStageUIMgr =  CStageUIMgr::Get_Instance();
	if (nullptr == pStageUIMgr) return;
	pStageUIMgr->SetActiveBossSlainBanner();
	CSoundMgr::Get_Instance()->PlaySound_Overwrite(L"snd_boss.mp3", CSoundMgr::CHANNELID::UI);
	
}

void CTengu::OnTakeDamage(float _fDamage)
{
	CMonster::OnTakeDamage(_fDamage);

}


CTengu * CTengu::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CTengu* pInstance = new CTengu(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CTengu");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CTengu::Clone(void * _param)
{
	CTengu* pInstance = new CTengu(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CTengu");
		Safe_Release(pInstance);

	}
	return pInstance;
}


void CTengu::Free()
{

	CMonster::Free();
}
