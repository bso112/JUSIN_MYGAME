#include "stdafx.h"
#include "Ghost.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "LevelMgr.h"
#include "Hero.h"
#include "Clock.h"
#include "AIStateCon.h"
#include "Shader.h"
#include "StageUIMgr.h"
#include "QuestMgr.h"
#include "ItemFactory.h"
#include "Spawner.h"
#include "Item.h"
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
	m_bNPC = true;
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
	pStateCon->Set_State(CAIState::STATE_WADERING, new CAIWandering(this));
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

	m_pDialogueForStart = L"반갑네 전사여... 한때 난 당신처럼 자신감 넘치고 강한 모험가였다네... 하지만 난 비겁한 적에게 죽어버렸네.. 그래서 난 이 곳을 떠날 수 없지... 복수를 하기 전까진 말야.. 검은 슬라임을 죽여줘.. 놈이 내 목숨을 앗아갔으니..";
	m_pDialogueForEnd = L"고맙네.. 여기 내가 간직해둔 보물이네. 이제 자네의 것이네...";

	m_vecReward.push_back(CItemFactory::Make_Item(BASEDESC(Vector3(), Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, 1));
	//마비저항의 옷도 


	for (auto& item : m_vecReward)
	{
		CSpawner::Get_Instance()->Add_Interact(item, 1);
	}
	return S_OK;
}


_int CGhost::Interact(CGameObject * _pOther)
{
	CQuestMgr* pQuestMgr = CQuestMgr::Get_Instance();
	if (nullptr == pQuestMgr) return -1;
	//퀘스트 시작안했으면 시작
	if(!pQuestMgr->IsQuestStart())
		pQuestMgr->SetQuestStart();

	//다이어로그 패널 셋팅
	CStageUIMgr* m_pUIMgr = CStageUIMgr::Get_Instance();
	if (nullptr == m_pUIMgr) return -1;
	m_pUIMgr->SetActiveDialogPanel();
	const _tchar* _pDialogue = pQuestMgr->IsQuestEnd() ? m_pDialogueForEnd : m_pDialogueForStart;
	m_pUIMgr->SetDialogInfo(L"ghost", SCENE_STAGE, L"슬픈 유령", _pDialogue);
	if (pQuestMgr->IsQuestEnd())
		pQuestMgr->Reward(&m_vecReward);
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
	for (auto& item : m_vecReward)
		Safe_Release(item);

	CMonster::Free();
}
