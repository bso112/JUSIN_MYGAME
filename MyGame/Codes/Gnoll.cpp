#include "stdafx.h"
#include "Gnoll.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "World.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"

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

#pragma region ���ݼ���

	//���ݼ���
	m_tStat.m_fExp = 20.f;
	m_tStat.m_fMaxHp = CStat::Create(30.f);
	m_tStat.m_fAtt = CStat::Create(10.f);
	m_tStat.m_iGold = 10;
	m_tStat.m_fArmor = CStat::Create(4.f);
	m_tStat.m_fHP = 30.f;
#pragma endregion

#pragma region ������
	//������
	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform,nullptr, &CTransform::STATEDESC(100.0, 100.0, 2))))
		return E_FAIL;
	if (FAILED(Set_Module(L"AIStateCon", SCENE_STATIC, (CModule**)&m_pStateCon)))
		return E_FAIL;
	if (FAILED(Set_Module(L"Animator", SCENE_STATIC, (CModule**)&m_pAnimator)))
		return E_FAIL;

#pragma endregion

#pragma region ���¼���
	m_pStateCon->Set_State(CAIState::STATE_IDLE, new CAIIdle(this));
	m_pStateCon->Set_State(CAIState::STATE_HUNTING, new CAIHunting(this));
	m_pStateCon->Set_State(CAIState::STATE_SLEEP, new CAISleeping(this));
	m_pStateCon->Set_State(CAIState::STATE_WADERING, new CAIWandering(this));
	m_pStateCon->Set_Default_State(CAIState::STATE_IDLE);

#pragma endregion

#pragma region �ִϸ��̼� ����

	//�ִϸ��̼� ����
	CTexture* pTexture = nullptr;

	Set_Module(L"gnoll_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.2, false);
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

	//�ִϸ��̼��� ���輳��
	pAttackAnim->Set_NextAnim(pIdleAnim);

	//�⺻ �ִϸ��̼� ����
	m_pAnimator->Play(L"idle");

#pragma endregion


	//��ġ ����
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 20.f));


	//������� ����
	m_iRecogRange = 5;
	m_iAttackRange = 1;

	return S_OK;
}

_int CGnoll::Update(_double _timeDelta)
{
	m_pTransform->Update(_timeDelta);
	return 0;
}

_int CGnoll::LateUpate(_double _timeDelta)
{
	m_pTransform->Late_Update();
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;

}

HRESULT CGnoll::Act(_int _iTurnCnt)
{

	if (nullptr == m_pFocus)
		return E_FAIL;
	m_pStateCon->Act(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange), _iTurnCnt);

	return S_OK;
}




HRESULT CGnoll::Render()
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

void CGnoll::Process()
{
}

void CGnoll::Update_State()
{
}

void CGnoll::OnDead()
{
}

void CGnoll::OnTakeDamage()
{
}

void CGnoll::Scene_Change()
{
}

void CGnoll::Free()
{
	Safe_Release(m_pStateCon);
	Safe_Release(m_pAnimator);
	CMonster::Free();
}
