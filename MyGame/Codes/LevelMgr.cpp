#include "stdafx.h"
#include "LevelMgr.h"
#include "Level.h"
#include "Spawner.h"
#include "ObjMgr.h"
#include "Warrior.h"
#include "Terrain.h"
#include "TileLoader.h"
#include "KeyMgr.h"
#include "InventoryUIMgr.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CLevelMgr)

CLevelMgr::CLevelMgr()
	:m_pSpawner(CSpawner::Get_Instance()),
	m_iCurrLevel(0)
{
	Safe_AddRef(m_pSpawner);
	 ZeroMemory(m_aLevel, sizeof(m_aLevel));

}
HRESULT CLevelMgr::Initialize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	//레벨을 준비한다.
	m_aLevel[0] = CLevel::Create(_pGraphic_Device, SCENE_STAGE, L"../Bin/Data/level1.dat");
	m_aLevel[1] = CLevel::Create(_pGraphic_Device, SCENE_STAGE, L"../Bin/Data/level2.dat");
	m_aLevel[2] = CLevel::Create(_pGraphic_Device, SCENE_STAGE, L"../Bin/Data/level3.dat");

	
	//타일프로토타입 생성
	CTileLoader::CreateTilePrototype(_pGraphic_Device, SCENE_STAGE);

	RETURN_FAIL_IF_NULL(m_aLevel[0]);
	RETURN_FAIL_IF_NULL(m_aLevel[1]);
	RETURN_FAIL_IF_NULL(m_aLevel[2]);



	//아이템, 몬스터 프로토타입을 준비한다.
	if (FAILED(m_pSpawner->Ready_Prototypes(_pGraphic_Device, m_iCurrLevel)))
		return E_FAIL;


	//캐릭터를 준비한다. 이부분 캐릭터 선택 반영하게 변경
	if (FAILED(CObjMgr::Get_Instance()->Add_Prototype(L"Player", SCENE_STAGE, CWarrior::Create(_pGraphic_Device))))
		return E_FAIL;



	return S_OK;
}

HRESULT CLevelMgr::Initialize()
{
	//순서 중요!
	
	//첫번째 레벨을 로드한다.
	if (FAILED(m_aLevel[0]->Load_World(SCENE_STAGE)))
		return E_FAIL;

	//플레이어를 만든다.
	if (nullptr == CObjMgr::Get_Instance()->Add_GO_To_Layer(L"Player", SCENE_STAGE, L"Player", SCENE_STAGE))
		return E_FAIL;

	//첫번째 레벨의 아이템, 몬스터를 스폰한다.
	if (FAILED(m_pSpawner->Spawn(0)))
		return E_FAIL;

	//두번째 레벨을 로드한다.
	if (FAILED(m_aLevel[1]->Load_World(SCENE_STAGE)))
		return E_FAIL;

	//두번째 레벨의 아이템, 몬스터를 스폰한다.
	if (FAILED(m_pSpawner->Spawn(1)))
		return E_FAIL;

	//두번째 레벨을 로드한다.
	if (FAILED(m_aLevel[2]->Load_World(SCENE_STAGE)))
		return E_FAIL;

	if (FAILED(m_pSpawner->Spawn(2)))
		return E_FAIL;


	m_iCurrLevel = 0;

	for (int i = 0; i < MAX_DEPTH; ++i)
	{
		if (i == m_iCurrLevel)
			continue;

		m_aLevel[i]->SetActive(false);
		m_pSpawner->SetActive(false, i);
	}
	
	m_aLevel[m_iCurrLevel]->SetActive(true);
	m_pSpawner->SetActive(true, m_iCurrLevel);


	CKeyMgr::Get_Instance()->RegisterObserver(SCENE_STAGE, this);


	return S_OK;
}
HRESULT CLevelMgr::Next_Level()
{
	if (m_iCurrLevel + 1 >= MAX_DEPTH)
		return E_FAIL;

	m_aLevel[m_iCurrLevel]->SetActive(false);
	m_pSpawner->SetActive(false, m_iCurrLevel);
	++m_iCurrLevel;
	m_aLevel[m_iCurrLevel]->SetActive(true);
	m_pSpawner->SetActive(true, m_iCurrLevel);

	CHero* pHero = dynamic_cast<CHero*>(CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE));
	if (nullptr == pHero)
		return E_FAIL;
	pHero->Set_InitialPos();
	CTransform* pHeroTransform = dynamic_cast<CTransform*>(pHero->Get_Module(L"Transform"));
	pHeroTransform->Stop();
	return S_OK;
}
HRESULT CLevelMgr::Prv_Level()
{
	if (m_iCurrLevel - 1 < 0)
		return E_FAIL;

	m_aLevel[m_iCurrLevel]->SetActive(false);
	m_pSpawner->SetActive(false, m_iCurrLevel);
	--m_iCurrLevel;
	m_aLevel[m_iCurrLevel]->SetActive(true);
	m_pSpawner->SetActive(true, m_iCurrLevel);

	if (m_iCurrLevel <= 0)
		m_iCurrLevel = 0;

	CHero* pHero = dynamic_cast<CHero*>(CObjMgr::Get_Instance()->Get_Player(SCENE_STAGE));
	if (nullptr == pHero)
		return E_FAIL;
	pHero->Set_LastPos();
	CTransform* pHeroTransform = dynamic_cast<CTransform*>(pHero->Get_Module(L"Transform"));
	if (pHeroTransform == nullptr) return E_FAIL;
	pHeroTransform->Stop();


	return S_OK;
}
CLevel*	CLevelMgr::Get_CurrLevel()
{
	if (m_iCurrLevel >= MAX_DEPTH)
		return nullptr;

	return m_aLevel[m_iCurrLevel];
}

CLevel * CLevelMgr::Get_Level(_int index)
{
	if (index >= MAX_DEPTH || index < 0)
		return nullptr;

	return m_aLevel[index];
}

_int CLevelMgr::Get_CurrDepth()
{
	if (m_iCurrLevel < 0)
		return  0;
	if (m_iCurrLevel >= MAX_DEPTH)
		return MAX_DEPTH - 1;

	return m_iCurrLevel;
}

void CLevelMgr::Clear_DeadObjects()
{
	m_pSpawner->Clear_DeadObjects(m_iCurrLevel);
}

HRESULT CLevelMgr::Set_Visuable(Vector3 _vPos, _int _iRange)
{
	CLevel* pLevel = Get_CurrLevel();
	RETURN_FAIL_IF_NULL(pLevel);
	if (FAILED(pLevel->Set_Visuable(_vPos, _iRange)))
		return E_FAIL;
	if (FAILED(m_pSpawner->Set_Visuable(_vPos, _iRange, m_iCurrLevel)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevelMgr::Explore(Vector3 _vPos)
{
	return m_aLevel[Get_CurrDepth()]->Explore(_vPos);
}

Vector3 CLevelMgr::Get_RandomPos(Vector3 _vPos, _int _iRange)
{
	return m_aLevel[Get_CurrDepth()]->Get_RandomPos(_vPos, _iRange);
}

vector<Vector3> CLevelMgr::Get_Area(Vector3 _vPos, _int _iRange)
{
	return m_aLevel[Get_CurrDepth()]->Get_Area(_vPos, _iRange);
}


CTerrain * CLevelMgr::PickTile(POINT & pt)
{
	CLevel* pLevel = Get_CurrLevel();
	if (nullptr == pLevel)
		return nullptr;

	return pLevel->Pick_Tile(pt);
}

CGameObject * CLevelMgr::PickObject(POINT & pt)
{
	return m_pSpawner->PickObject(pt, m_iCurrLevel);
}

CCharacter * CLevelMgr::PickCharacter(POINT & pt)
{
	return dynamic_cast<CCharacter*>(m_pSpawner->PickCharacter(pt, Get_CurrDepth(), nullptr));
}

_bool CLevelMgr::IsMovable(Vector3 & _vPos)
{

	CLevel* pLevel = Get_CurrLevel();
	if (nullptr == pLevel)
		return nullptr;

	CTerrain* pTerrain = pLevel->Pick_Tile(_vPos);
	if (nullptr == pTerrain)
		return false;
	return pTerrain->IsMovable(nullptr);
}

HRESULT CLevelMgr::OnKeyDown(_int KeyCode)
{
 	if (KeyCode == VK_RBUTTON)
	{
		Next_Level();

		CInventoryUIMgr* pInventoryUIMgr = CInventoryUIMgr::Get_Instance();
		if (nullptr == pInventoryUIMgr) return -1;
		CInventory* pInven = pInventoryUIMgr->GetInventory();
		if (nullptr == pInven) return -1;
		m_pSpawner->Ready_BasicItem(pInven);
	}

	return S_OK;
}

void CLevelMgr::Free()
{
	CKeyMgr::Get_Instance()->UnRegisterObserver(SCENE_STAGE, this);

	Safe_Release(m_pSpawner);

	if (0 != CSpawner::Destroy_Instance())
		MSG_BOX("Fail to Destroy Spawner");

	for (int i = 0; i < MAX_DEPTH; ++i)
	{
		Safe_Release(m_aLevel[i]);
	}
}
