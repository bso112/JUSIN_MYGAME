#include "stdafx.h"
#include "LevelMgr.h"
#include "Level.h"
#include "Spawner.h"
#include "ObjMgr.h"
#include "Warrior.h"
#include "Terrain.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CLevelMgr)

CLevelMgr::CLevelMgr()
	:m_pSpawner(CSpawner::Get_Instance())
{
	Safe_AddRef(m_pSpawner);
	 ZeroMemory(m_aLevel, sizeof(m_aLevel));

}
HRESULT CLevelMgr::Initialize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	//레벨을 준비한다.
	m_aLevel[0] = CLevel::Create(_pGraphic_Device, SCENE_STAGE, L"../Bin/Data/level2.dat");
	RETURN_FAIL_IF_NULL(m_aLevel[0]);


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

	//현재 레벨의 아이템, 몬스터를 스폰한다.
	if (FAILED(m_pSpawner->Spawn(m_iCurrLevel)))
		return E_FAIL;

	return S_OK;
}
CLevel*	CLevelMgr::Get_CurrLevel()
{
	if (m_iCurrLevel >= MAX_DEPTH)
		return nullptr;

	return m_aLevel[m_iCurrLevel];
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

void CLevelMgr::Free()
{
	Safe_Release(m_pSpawner);

	if (0 != CSpawner::Destroy_Instance())
		MSG_BOX("Fail to Destroy Spawner");

	for (int i = 0; i < MAX_DEPTH; ++i)
	{
		Safe_Release(m_aLevel[i]);
	}
}
