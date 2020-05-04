#include "stdafx.h"
#include "..\Headers\Rat.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "World.h"
#include "Hero.h"

USING(MyGame)

CRat::CRat(CRat & _rhs)
	:CMonster(_rhs)
{
	m_tStat = _rhs.m_tStat;
}

HRESULT CRat::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Rat/");

	m_tStat.m_fExp = 10.f;
	m_tStat.m_fMaxHp = CStat::Create(16.f);
	m_tStat.m_fAtt = CStat::Create(5.f);
	m_tStat.m_iGold = 5;
	m_tStat.m_fArmor = CStat::Create(2.f);
	m_tStat.m_fHP = 16.f;


	return S_OK;
}

HRESULT CRat::Initialize(void * _param)
{

	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, &CTransform::STATEDESC(100.0, 100.0));

	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 20.f));


	Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator);

	CTexture* pTexture = nullptr;

	Set_Module(L"rat_att", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	Set_Module(L"rat_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);
	
	Set_Module(L"rat_dead", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pDeadAnim	= CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);
	
	Set_Module(L"rat_jump", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pJumpAnim	= CAnimation::Create(pTexture, 0.2, false);
	m_pAnimator->Add_Animation(L"jump", pJumpAnim);

	//애니메이션의 관계설정
	pAttackAnim->Set_NextAnim(pIdleAnim);
	pJumpAnim->Set_NextAnim(pIdleAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"idle");

	m_iRecogRange = 5;
	m_iAttackRange = 1;




	return S_OK;
}

_int CRat::Update(_double _timeDelta)
{

	m_pTransform->Update(_timeDelta);
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
	Safe_Release(m_pAnimator);
	CMonster::Free();
}

