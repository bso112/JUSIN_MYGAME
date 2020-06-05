#include "stdafx.h"
#include "..\Headers\Stage.h"
#include "LevelMgr.h"
#include "TextureLoader.h"
#include "StageUIMgr.h"
#include "Transform.h"
#include "TurnMgr.h"
#include "MyButton.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "BuffController.h"
#include "QuestMgr.h"


USING(MyGame)

CStage::CStage(PDIRECT3DDEVICE9 _pGraphic_Device)
	: CScene(_pGraphic_Device),
	m_pLevelMgr(CLevelMgr::Get_Instance()),
	m_pStageUIMgr(CStageUIMgr::Get_Instance()),
	m_pTurnMgr(CTurnMgr::Get_Instance())
{
	Safe_AddRef(m_pLevelMgr);
	Safe_AddRef(m_pStageUIMgr);
	Safe_AddRef(m_pTurnMgr);

};

HRESULT CStage::Initialize()
{
	if (FAILED(Initalize_Prototypes()))
		return E_FAIL;

	if (FAILED(Initalize_Layers()))
		return E_FAIL;

	if (nullptr == m_pObjMgr)
		return E_FAIL;

	m_pStageUIMgr->Initialize(m_pGraphic_Device, (CHero*)m_pObjMgr->Get_Player(SCENE_STAGE));
	m_pTurnMgr->Initialize();



	return S_OK;
}

_int CStage::Update(_double _timeDelta)
{
	m_pTurnMgr->Update_Simultaneously();
	CScene::Update(_timeDelta);

	return 0;
}

HRESULT CStage::Render()
{
	CScene::Render();
	m_pLevelMgr->Clear_DeadObjects();

	return S_OK;
}



HRESULT CStage::Initalize_Prototypes()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;



	return S_OK;
}

HRESULT CStage::Initalize_Layers()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	//레벨 생성
	if (FAILED(m_pLevelMgr->Initialize()))
		return E_FAIL;

	//카메라 생성
	CCamera* pMainCam = dynamic_cast<CCamera*>(m_pObjMgr->Add_GO_To_Layer(L"MainCamera", SCENE_STAGE, L"Camera", SCENE_STAGE, &BASEDESC(Vector3(float(g_iWinCX >> 1), float(g_iWinCY >> 1)), Vector3(1.f, 1.f, 1.f))));
	RETURN_FAIL_IF_NULL(pMainCam);
	CGameObject* pPlayer = m_pObjMgr->Get_Player(SCENE_STAGE);
	RETURN_FAIL_IF_NULL(pPlayer);
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(pPlayer->Get_Module(L"Transform"));
	RETURN_FAIL_IF_NULL(pPlayerTransform);
	pMainCam->Set_Target(pPlayerTransform);


	return S_OK;
}

CStage * CStage::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CStage* pInstance = new CStage(_pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to Create CStage Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStage::Free()
{

	Safe_Release(m_pLevelMgr);
	Safe_Release(m_pStageUIMgr);
	Safe_Release(m_pTurnMgr);

	if (0 != CQuestMgr::Destroy_Instance())
		MSG_BOX("Fail to release CQuestMgr");


	if (0 != CStageUIMgr::Destroy_Instance())
		MSG_BOX("Fail to release m_pStageUIMgr");

	if (0 != CLevelMgr::Destroy_Instance())
		MSG_BOX("Fail to release CLevelMgr");


	//스테이지 씬의 프로토타입과 레이어(게임오브젝트)들을 완전히 지움.
	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear GameObject Prototypes");


	//스테이지 씬의 모듈 프로토타입 완전히 지움.
	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear Module Prototypes");

	//별 의미없음
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		MSG_BOX("Fail to Clear Renderer");

	if (0 != CTurnMgr::Destroy_Instance())
		MSG_BOX("Fail to release CTurnMgr");

	if (FAILED(CKeyMgr::Get_Instance()->ClearObservers(SCENEID::SCENE_STAGE)))
		MSG_BOX("Fail to Clear Module Prototypes");

	CScene::Free();
}



