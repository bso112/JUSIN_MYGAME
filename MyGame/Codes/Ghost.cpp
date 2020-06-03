#include "stdafx.h"
#include "Ghost.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "LevelMgr.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"
#include "Shader.h"
USING(MyGame)

CGhost::CGhost(CGhost & _rhs)
	:CMonster(_rhs)
{
	//얕은복사하면 릭남. 터짐. CStat은 동적할당이기 때문
	//m_tStat = _rhs.m_tStat;
}

HRESULT CGhost::Initialize_Prototype(_tchar * _pFilePath)
{
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Monster/Ghost/");
	return S_OK;
}

HRESULT CGhost::Initialize(void * _param)
{

	m_pName = L"유령";
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
	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, nullptr, &CTransform::STATEDESC(CalulateSpeed(movePerturn), 100.0, movePerturn))))
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
	pStateCon->Set_State(CAIState::STATE_IDLE, new CAIWandering(this));
	pStateCon->Set_Default_State(CAIState::STATE_WADERING);

#pragma endregion

#pragma region 애니메이션 셋팅

	//애니메이션 셋팅
	CTexture* pTexture = nullptr;


	Set_Module(L"ghost", SCENE_STAGE, (CModule**)&pTexture);
	CAnimation* pWanderingAnim = CAnimation::Create(pTexture, 1.0, true);
	m_pAnimator->Add_Animation(L"ghost_wandering", pWanderingAnim);

	//기본 애니메이션 설정
	m_pAnimator->Play(L"ghost_wandering");

#pragma endregion


	//위치 셋팅
	if (nullptr != _param)
		m_pTransform->Set_Position(*((Vector3*)_param));

	m_pTransform->Set_Size(Vector2(20.f, 20.f));
	m_pTransform->Set_ColliderSize(Vector2(30.f, 30.f));


	CMonster::Initialize(_param);

	m_pDialogue = L"나는 전에 이 던전을 탐사하다가 죽은 영혼이오. 만약 내 원한을 풀어준다면 생전에 발견한 보물을 주겠소. 구(Goo)를 퇴치해주시오.";

	return S_OK;
}


_int CGhost::Interact(CGameObject * _pOther)
{
	return 0;
}

CGhost * CGhost::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CGhost* pInstance = new CGhost(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CGhost");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CGhost::Clone(void * _param)
{
	CGhost* pInstance = new CGhost(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to clone CGhost");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CGhost::Free()
{
	CMonster::Free();
}
