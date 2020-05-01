#include "stdafx.h"
#include "..\Headers\World.h"
#include "Terrain.h"
#include "Transform.h"
#include "ObjMgr.h"
#include "Door.h"
#include "CollisionMgr.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CWorld)

CWorld::CWorld()
{
	ZeroMemory(&m_pTerrains, sizeof(m_pTerrains));
}

HRESULT CWorld::Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, _tchar* _pFilePath)
{

	m_eSceneID = _eSceneID;
	if (_pFilePath != nullptr)
	{
		//지형 프로토타입을 만든다.
		Initalize_Prototypes(_pGraphic_Device, _eSceneID);
		//월드 정보 파일을 읽어 지형을 배치한다.
		Load_World(_pFilePath, _eSceneID);
	}


	return S_OK;

}

_int CWorld::Update()
{
	//충돌처리
	CGameObject* pPlayer = CObjMgr::Get_Instance()->Get_Player(m_eSceneID);
	if (nullptr == pPlayer)
		return -1;
	Collision_Terrain(pPlayer);

	return 0;
}


HRESULT CWorld::Render()
{

	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			if (nullptr != m_pTerrains[i][j])

				m_pTerrains[i][j]->Render();
		}
	}
	return S_OK;
}

HRESULT CWorld::Set_Terrain(CTerrain * _pTerrain, POINT& _pt)
{
	if (nullptr == _pTerrain)
		return E_FAIL;

	_uint x = _pt.x / TILECX;
	_uint y = _pt.y / TILECY;


	//타일의 인덱스에 따른 타일의 좌표를 구한다.
	float fX = (TILECX >> 1) + (float)(TILECX * x);
	float fY = (TILECY >> 1) + (float)(TILECY * y);

	if (x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	//만약 이미 타일이 있다면 지우기
	if (nullptr != m_pTerrains[y][x])
	{
		Safe_Release(m_pTerrains[y][x]);
		return S_OK;
	}


	//깊은복사
	CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

	//지형의 위치를 지정한다.
	CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
	if (nullptr != pTransform)
	{
		pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
		pTransform->Late_Update();
	}

	//타일을 채운다.
	m_pTerrains[y][x] = pTerrain;

	return S_OK;
}

HRESULT CWorld::Get_TerrainPos(POINT _dst, Vector3& _out)
{
	int x = _dst.x / TILECX;
	int y = _dst.y / TILECY;

	if (x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	if (nullptr == m_pTerrains[y][x])
		return E_FAIL;

	CTransform* pDstTransform = (CTransform*)m_pTerrains[y][x]->Get_Module(L"Transform");
	_out = pDstTransform->Get_Position();

	return S_OK;
}

HRESULT CWorld::Get_Route(Vector3 _src, POINT _dst, vector<Vector3>& _out)
{
	_int srcX = _src.x / TILECX;
	_int srcY = _src.y / TILECY;
	_int dstX = _dst.x / TILECX;
	_int dstY = _dst.y / TILECY;

	if (dstX >= WORLDX || dstY >= WORLDY)
		return E_FAIL;
	if (srcX >= WORLDX || srcY >= WORLDY)
		return E_FAIL;

	if (nullptr == m_pTerrains[srcY][srcX] || nullptr == m_pTerrains[dstY][dstX])
		return E_FAIL;


	//에이스타
	/*
	 Gcost // distance from staring node
	 Hcost // distance from end node
	 Fcost // Gcost + Hcost
	*/

#pragma region 초기화


	//지나온 노드
	set<CTerrain*> visited;
	//검사할 노드
	set<CTerrain*> nodes;
	//검사의 중심이 되는 현재노드
	CTerrain* pCurrNode = m_pTerrains[srcY][srcX];

	int currX = srcX;
	int currY = srcY;

	int currFcost = INT_MAX;
	//Fcost가 같으면 Hcost 기준으로 루트정함
	int currHcost = INT_MAX;

	int diaCost = (int)sqrt(TILECX * TILECX + TILECY * TILECY);
#pragma endregion

	while (m_pTerrains[dstY][dstX] != pCurrNode)
	{

		//현재노드의 왼쪽 위 타일의 인덱스
		int tmpY = currY - 1;
		int tmpX = currX - 1;


		//주변 8 타일을 검사한다.
		for (int i = tmpY; i <= tmpY + 2; ++i)
		{
			for (int j = tmpX; j <= tmpX + 2; ++j)
			{
#pragma region 예외처리
				//유효하지 않은 타일 제외
				if (i >= WORLDX || j >= WORLDY || i < 0 || j < 0)
					continue;
				if (nullptr == m_pTerrains[i][j])
					continue;
				//가지 못하는 곳이면 제외
				if (!m_pTerrains[i][j]->IsMovable())
					continue;
				//이미 방문한 곳이면 제외
				if (visited.find(m_pTerrains[i][j]) != visited.end())
					continue;
				//자기자신 제외
				if (i == currY && j == currX)
					continue;
				//자기자신이 nullptr면 끝냄
				if (nullptr == pCurrNode)
					return E_FAIL;

#pragma endregion
				//cost 구하기
				_int Gcost = 0;
				_int Hcost = 0;
				_int Fcost = 0;

				//대각선노드면
				if (i != currY && j != currX)
				{
					//이 노드가 출발지로부터 가까워지는건지 멀어지는건지 어케암?
					Gcost =
				}
				else
				{

				}


				if (currFcost > Fcost)
				{
					currFcost = Fcost;
					currHcost = Hcost;
					pCurrNode = m_pTerrains[i][j];
					currX = j;
					currY = i;
				}
				//만약 현재 노드와 Fcost가 같으면
				else if (currFcost == Fcost)
				{
					//Hcost가 더 작은 걸 선택
					if (currHcost > Hcost)
					{
						currFcost = Fcost;
						currHcost = Hcost;
						pCurrNode = m_pTerrains[i][j];
						currX = j;
						currY = i;

					}
				}
			}
		}
		//만약 선택된 경로가 없다면 길이 없다는 것이므로 끝냄.
		if (m_pTerrains[tmpY + 1][tmpX + 1] == pCurrNode)
			break;
		//지나간 경로를 표시한다.
		visited.emplace(pCurrNode);
	}

	for (auto pTerrain : visited)
	{
		CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return E_FAIL;

		_out.push_back(pTransform->Get_Position());
	}
	return S_OK;
}

HRESULT CWorld::Save_World(const _tchar* _filePath)
{
	HANDLE hFile = CreateFile(_filePath, GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	int zero = 0;
	int one = 1;
	//데이터 앞에 표시를 달자. 널이면 0, 널이 아니면 1
	for (auto& terrainArr : m_pTerrains)
	{
		for (auto& terrain : terrainArr)
		{
			if (nullptr == terrain)
			{
				WriteFile(hFile, &zero, sizeof(int), &dwByte, NULL);
			}
			else
			{
				WriteFile(hFile, &one, sizeof(int), &dwByte, NULL);
				WriteFile(hFile, &terrain->Get_SaveData(), sizeof(CTerrain::SAVE_DATA), &dwByte, NULL);
			}
		}
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"Success", MB_OK);
	return S_OK;
}

HRESULT CWorld::Load_World(const _tchar* _filePath, SCENEID _eSceneID)
{
	HANDLE hFile = CreateFile(_filePath, GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	//현재 타일을 모두 지운다.
	Free();

	DWORD				dwByte = 0;
	int					prefix = 0;
	CTerrain::SAVE_DATA tSaveData = {};

	_uint index = 0;
	while (true)
	{
		ReadFile(hFile, &prefix, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		_uint y = index / WORLDX;
		_uint x = index % WORLDX;
		//읽을 데이터가 nullptr가 아니면 읽는다.
		if (0 != prefix)
		{

			ReadFile(hFile, &tSaveData, sizeof(CTerrain::SAVE_DATA), &dwByte, NULL);

			if (0 == dwByte)
				break;

			/*
			프로토타입 태그를 통해 올바른 클래스로 변환한다.
			예를들어 CDoor의 프로토타입에서 복사된 CGameObject가 CTerrain으로 변환되어 Load_Data를 통해 데이터가 셋팅된다.
			*/
			m_pTerrains[y][x] = (CTerrain*)CObjMgr::Get_Instance()->Add_GO_To_Layer(tSaveData.m_PrototypeTag, m_eSceneID, L"Terrain", _eSceneID);
			if (nullptr == m_pTerrains[y][x])
				return E_FAIL;
			Safe_AddRef(m_pTerrains[y][x]);

			m_pTerrains[y][x]->Load_Data(tSaveData);



		}
		else
			m_pTerrains[y][x] = nullptr;


		if (0 == dwByte)
			break;

		++index;

	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Load", L"Success", MB_OK);
	return S_OK;
}

HRESULT CWorld::Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID)
{

#pragma region 타일생성

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;
	Safe_AddRef(pObjMgr);

	//팔레트에 쓸 타일(프로토타입)을 만든다.
	CTerrain* pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_bookshelf", _eSceneID);
	//오브젝트 매니저에 등록한다.
	pObjMgr->Add_Prototype(L"lv_One_bookshelf", _eSceneID, pTerrain);
	pTerrain = CDoor::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_door", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_door", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_floor", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_floor_burned", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_burned", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_floor_grass", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_grass", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_A", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_A", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_B", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_B", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_C", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_C", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_D", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_D", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_E", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_E", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_F", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_F", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_G", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_G", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_H", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_H", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_I", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_I", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_floor_mold", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_floor_mold", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_prison", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_prison", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_sign", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_sign", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_stair_down", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_stair_down", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_stair_up", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_stair_up", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_statue_rock", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_statue_rock", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_statue_wood", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_statue_wood", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap_delusion", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap_delusion", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap_fire", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap_fire", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap_orange", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap_orange", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap_paralyze", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap_paralyze", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap_poison", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap_poison", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap_pupple", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap_pupple", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_trap_remain", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_trap_remain", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_wall", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_wall", _eSceneID, pTerrain);
	pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_wall_sewer", _eSceneID);
	pObjMgr->Add_Prototype(L"lv_One_wall_sewer", _eSceneID, pTerrain);


#pragma endregion

	Safe_Release(pObjMgr);

	return S_OK;
}

HRESULT CWorld::Collision_Terrain(CGameObject* _pObj)
{
	if (nullptr == _pObj)
		return E_FAIL;

	CTransform* pTransform = (CTransform*)_pObj->Get_Module(L"Transform");

	int x = (int)pTransform->Get_Position().x / TILECX;
	int y = (int)pTransform->Get_Position().y / TILECY;

	if (x < 0 || y < 0 || x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	if (nullptr == m_pTerrains[y][x])
		return E_FAIL;

	//m_pTerrains[y][x]이 null이 아니라는 말은 해당 타일과 충돌했다는 것.
	CCollisionMgr::Collision(list<CGameObject*>(1, _pObj), list<CGameObject*>(1, m_pTerrains[y][x]), true);

	return S_OK;
}


void CWorld::Free()
{
	for (auto& tileArr : m_pTerrains)
	{
		for (auto& tile : tileArr)
			Safe_Release(tile);
	}

}

