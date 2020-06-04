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
	:CMonster(_rhs)
{
	m_tStat = _rhs.m_tStat;
}

HRESULT CGoo::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Goo/");
	return S_OK;
}

HRESULT CGoo::Initialize(void * _param)
{

	m_pName = L"���� ������";
#pragma region ���ݼ���

	//���ݼ���
	m_tStat.m_fExp = 20.f;
	m_tStat.m_fMaxHp = CStat::Create(100.f);
	m_tStat.m_fHP = 100.f;
	m_tStat.m_fAtt = CStat::Create(5.f, 15.f);
	m_tStat.m_iGold = 100;
	m_tStat.m_fArmor = CStat::Create(5.f);
#pragma endregion

#pragma region ������
	//������
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

	//��ġ ����
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 25.f));
	m_pTransform->Set_ColliderSize(Vector2(25.f, 30.f));



#pragma endregion

#pragma region ���¼���
	CAIStateCon* pStateCon = dynamic_cast<CAIStateCon*>(m_pStateCon);
	pStateCon->Set_State(CAIState::STATE_IDLE, new CAIIdle(this));
	pStateCon->Set_State(CAIState::STATE_HUNTING, new CAIHunting(this));
	pStateCon->Set_State(CAIState::STATE_SLEEP, new CAISleeping(this));
	pStateCon->Set_Default_State(CAIState::STATE_SLEEP);

#pragma endregion

#pragma region �ִϸ��̼� ����

	//�ִϸ��̼� ����
	CTexture* pTexture = nullptr;

	Set_Module(L"goo_attack", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pAttackAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"attack", pAttackAnim);

	Set_Module(L"goo_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pIdleAnim = CAnimation::Create(pTexture, 0.5, true);
	m_pAnimator->Add_Animation(L"idle", pIdleAnim);

	Set_Module(L"goo_dead", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pDeadAnim = CAnimation::Create(pTexture, 0.1, false);
	m_pAnimator->Add_Animation(L"dead", pDeadAnim);

	//idle�ִϸ��̼��� ������ �� ��
	Set_Module(L"goo_idle", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pWalkAnim = CAnimation::Create(pTexture, 0.1, true);
	m_pAnimator->Add_Animation(L"walk", pWalkAnim);

	//�ִϸ��̼��� ���輳��
	pAttackAnim->Set_NextAnim(pWalkAnim);

	//�⺻ �ִϸ��̼� ����
	m_pAnimator->Play(L"idle");

#pragma endregion



	CMonster::Initialize(_param);

	//������� ����
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
