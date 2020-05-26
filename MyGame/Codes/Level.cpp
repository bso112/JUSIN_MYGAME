#include "stdafx.h"
#include "Level.h"
#include "Terrain.h"
#include "Transform.h"
#include "ObjMgr.h"
#include "Door.h"
#include "Stair.h"
#include "CollisionMgr.h"
#include "StageUIMgr.h"
#include "Pipline.h"
#include "TileLoader.h"

USING(MyGame)


CLevel::CLevel(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device),
	m_pPipline(CPipline::Get_Instance())
{
	Safe_AddRef(m_pGraphic_Device);
	Safe_AddRef(m_pPipline);
	ZeroMemory(&m_pTerrains, sizeof(m_pTerrains));
}

HRESULT CLevel::Initialize(SCENEID _eSceneID, _tchar* _pFilePath)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_eSceneID = _eSceneID;
	//지형 프로토타입을 만든다.
	if (_eSceneID != SCENE_EDITOR)
		Initalize_Prototypes(m_pGraphic_Device, _eSceneID);

	m_pLoadfilePath = _pFilePath;
	return S_OK;

}


HRESULT CLevel::Render_ForEditor()
{

	_matrix camMatrix = m_pPipline->Get_CameraMatrix_inverse();



	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			if (nullptr != m_pTerrains[i][j])
			{
				CTransform* pTransform = (CTransform*)m_pTerrains[i][j]->Get_Module(L"Transform");

				Vector3 vPos = pTransform->Get_Position();
				D3DXVec4Transform(&vPos, &vPos, &camMatrix);

				//컬링
				if (-100.f <= vPos.x && g_iWinCX + 100.f >= vPos.x)
				{
					if (-100.f <= vPos.y && g_iWinCY + 100.f >= vPos.y)
					{
						m_pTerrains[i][j]->Render();
					}
				}
			}
		}
	}

	for (auto& maskTile : m_vecMask)
	{
		maskTile->Render();
	}

	return S_OK;
}

HRESULT CLevel::Set_Terrain(CTerrain * _pTerrain, POINT& _pt)
{
	if (nullptr == _pTerrain)
		return E_FAIL;

	Vector4 vPos = Vector4((float)_pt.x, (float)_pt.y, 0.f, 1.f);
	D3DXVec4Transform(&vPos, &vPos, &CPipline::Get_Instance()->Get_CameraMatrix());

	_uint x = (_uint)vPos.x / TILECX;
	_uint y = (_uint)vPos.y / TILECY;


	//타일의 인덱스에 따른 타일의 좌표를 구한다.
	float fX = (TILECX >> 1) + (float)(TILECX * x);
	float fY = (TILECY >> 1) + (float)(TILECY * y);

	if (x >= WORLDX || y >= WORLDY)
		return E_FAIL;


	//만약 이미 타일이 있고, 그 타일이 마스크 가능한 타일이면
	if (nullptr != m_pTerrains[y][x] && m_pTerrains[y][x]->IsMaskable())
	{
		//깊은복사
		CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

		//지형의 위치를 지정한다.
		CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
		if (nullptr != pTransform)
		{
			pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
			pTransform->Update_Transform();
		}

		//마스크는 나중에 지우기 위해 따로 보관한다.
		m_vecMask.push_back(pTerrain);

	}
	else
	{
		//만약 이미 타일이 있으면 지우기
		if (nullptr != m_pTerrains[y][x])
		{
			Safe_Release(m_pTerrains[y][x]);
			return S_OK;
		}

		//널포인터일때

		//깊은복사
		CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

		//지형의 위치를 지정한다.
		CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
		if (nullptr != pTransform)
		{
			pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
			pTransform->Update_Transform();
		}
		//타일을 채운다.
		m_pTerrains[y][x] = pTerrain;
	}


	return S_OK;
}

HRESULT CLevel::Fill_Terrain(CTerrain * _pTerrain, POINT & _pt)
{
	if (nullptr == _pTerrain)
		return E_FAIL;

	Vector4 vPos = Vector4((float)_pt.x, (float)_pt.y, 0.f, 1.f);
	D3DXVec4Transform(&vPos, &vPos, &CPipline::Get_Instance()->Get_CameraMatrix());

	_uint x = (_uint)vPos.x / TILECX;
	_uint y = (_uint)vPos.y / TILECY;


	//타일의 인덱스에 따른 타일의 좌표를 구한다.
	float fX = (TILECX >> 1) + (float)(TILECX * x);
	float fY = (TILECY >> 1) + (float)(TILECY * y);

	if (x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	//널포인트일때만 생성
	if (nullptr == m_pTerrains[y][x])
	{
		//깊은복사
		CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

		//지형의 위치를 지정한다.
		CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
		if (nullptr != pTransform)
		{
			pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
			pTransform->Update_Transform();
		}

		//타일을 채운다.
		m_pTerrains[y][x] = pTerrain;

	}

	return S_OK;
}

HRESULT CLevel::Erase_Mask(POINT & _pt)
{
	Vector4 vPos = Vector4((float)_pt.x, (float)_pt.y, 0.f, 1.f);
	D3DXVec4Transform(&vPos, &vPos, &CPipline::Get_Instance()->Get_CameraMatrix());

	POINT pt;
	pt.x = vPos.x;
	pt.y = vPos.y;

	auto& iter = m_vecMask.begin();
	while (iter != m_vecMask.end())
	{
		CTransform* pTransform = (CTransform*)(*iter)->Get_Module(L"Transform");
		if (PtInRect(&pTransform->Get_RECT(), pt))
		{
			Safe_Release(*iter);
			m_vecMask.erase(iter);
			break;
		}

		++iter;
	}
	return S_OK;
}

HRESULT CLevel::Get_TerrainPos(POINT _dst, Vector3& _out)
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



HRESULT CLevel::Get_Route(Vector3 _src, Vector3 _dst, vector<CTerrain*>& _out, CTransform* _pMover)
{

	_int srcX = (_int)_src.x / TILECX;
	_int srcY = (_int)_src.y / TILECY;
	_int dstX = (_int)_dst.x / TILECX;
	_int dstY = (_int)_dst.y / TILECY;

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

	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			if (nullptr != m_pTerrains[i][j])
				m_pTerrains[i][j]->Clear_Node();
		}
	}

	//지나온 노드(최종경로가 아니다)
	vector<CTerrain*> visited;
	//탐사한 노드
	set<CTerrain*> open;
	//검사의 중심이 되는 현재노드(그냥 visited의 마지막 노드)
	CTerrain* pCurrNode = m_pTerrains[srcY][srcX];

	_int currX = srcX;
	_int currY = srcY;

	_int minFcost = INT_MAX;
	//Fcost가 같으면 Hcost 기준으로 루트정함
	_int minHcost = INT_MAX;

	_int diaCost = (int)sqrt(TILECX * TILECX + TILECY * TILECY);

	int startHcost = 0;
	_int tmpX = abs(dstX - srcX);
	_int tmpY = abs(dstY - srcY);
	if (tmpX > tmpY)
		startHcost = tmpY * diaCost + (tmpX - tmpY) * TILECX;
	else
		startHcost = tmpX * diaCost + (tmpY - tmpX) * TILECX;

	//시작노드를 open리스트에 넣음
	pCurrNode->Set_Node(CTerrain::NODE(0, startHcost, startHcost, srcX, srcY, nullptr));
	open.emplace(pCurrNode);

#pragma endregion

	//더이상 탐색할 노드가 없을때까지
	while (open.size() > 0)
	{
		minFcost = INT_MAX;
		minHcost = INT_MAX;

		/*
		open set을 검사해서 Fcost가 가장 작은 노드를 찾는다.
		주의) 만약 INT_MAX가 아닌 curFcost랑 비교하면 Fcost가 현재 노드보다 더 커지는 경우는 배제해버린다.
		즉, 장애물을 돌아가는 경로는 아예 생각도 안해버림.
		*/
		for (auto& pTerrain : open)
		{
			CTerrain::NODE node = pTerrain->Get_Node();
			if (minFcost > node.Fcost)
			{
				minFcost = node.Fcost;
				pCurrNode = pTerrain;
				currX = node.X;
				currY = node.Y;
			}
			else if (minFcost == node.Fcost)
			{
				if (minHcost > node.Hcost)
				{
					minHcost = node.Hcost;
					pCurrNode = pTerrain;
					currX = node.X;
					currY = node.Y;
				}
			}

		}

		//선택된 노드는 open리스트에서 제거한다.
		open.erase(pCurrNode);
		//방문했다고 표시
		visited.push_back(pCurrNode);

		//목적지에 도달했으면 끝
		if (m_pTerrains[dstY][dstX] == pCurrNode)
			break;


		//현재노드의 왼쪽 위 타일의 인덱스
		int tmpY = currY - 1;
		int tmpX = currX - 1;

		//주변 8 타일을 검사해서 cost를 셋팅한다.
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
				if (!m_pTerrains[i][j]->IsMovable(_pMover))
					continue;
				//이미 방문한 곳이면 제외
				if (find(visited.begin(), visited.end(), m_pTerrains[i][j]) != visited.end())
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

				//끝 노드와의 거리
				_int distX = abs(dstX - j);
				_int distY = abs(dstY - i);

				/*
				대각선을 이용해야 최단거리다. 따라서 대각선을 만든다.
				X방향으로 1번 + Y방향으로 1번 = 대각선으로 1번
				*/
				//cost는 양수가 나와야 되기 때문에 나눠서 처리 
				if (distX > distY)
					Hcost = diaCost * distY + (distX - distY) * TILECX;
				else
					Hcost = diaCost * distX + (distY - distX) * TILECX;

				//현재노드와의 거리
				distX = abs(currX - j);
				distY = abs(currY - i);

				if (distX > distY)
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distY + (distX - distY) * TILECX);
				else
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distX + (distY - distX) * TILECX);

				Fcost = Hcost + Gcost;

				//만약 구한 Fcost가 기존의 것보다 작으면 기존 것을 갱신, 부모설정
				if (m_pTerrains[i][j]->Get_Node().Fcost > Fcost)
					m_pTerrains[i][j]->Set_Node(CTerrain::NODE(Gcost, Hcost, Fcost, j, i, pCurrNode));

				//검사대상에 넣는다. (중복없이)
				open.emplace(m_pTerrains[i][j]);


			}
		}
	}


	//visited에 들어가 있는건 방문했던 모든 노드다. 그 중에서 경로를 뽑아내야한다.

	//도착지점
	CTerrain* pLastNode = visited.back();

	//길을 찾지 못했을때는 목표와 가장 가까운 곳을 도착지로 설정
	if (open.size() == 0)
	{
		//경로중에 Hcost가 가장 낮은것을 목적지로함.
		//Hcost가 같으면 Gcost를 비교 낮은걸 취함. (더 이동이 적은것을 택함)
		if (visited.size() > 0)
		{
			pLastNode = visited[0];

			for (int i = 1; i < visited.size(); ++i)
			{
				_int lastHcost = pLastNode->Get_Node().Hcost;
				_int lastGcost = pLastNode->Get_Node().Gcost;
				_int currHcost = visited[i]->Get_Node().Hcost;
				_int currGcost = visited[i]->Get_Node().Gcost;

				if (lastHcost > currHcost)
				{
					pLastNode = visited[i];
				}
				else if (lastHcost == currHcost)
				{
					if (lastGcost > currGcost)
						pLastNode = visited[i];
				}
			}
		}
	}

	//부모가 없을때까지(시작노드까지)
	while (pLastNode->Get_Node().pParent != nullptr)
	{


		_out.push_back(pLastNode);
		//부모를 타고 들어가기
		pLastNode = pLastNode->Get_Node().pParent;
	}

	//뽑아낸건 경로의 반대이기 때문에 제대로 해줌
	reverse(_out.begin(), _out.end());
	return S_OK;
}

HRESULT CLevel::Get_Route(Vector3 _src, POINT & _dst, vector<CTerrain*>& _out, CTransform * _pMover)
{
	if (nullptr == m_pPipline)
		return E_FAIL;

	Vector4 dst = Vector4((float)_dst.x, (float)_dst.y, 0.f, 1.f);
	//마우스 좌표 변환
	D3DXVec4Transform(&dst, &dst, &m_pPipline->Get_CameraMatrix_inverse());

	_int srcX = (_int)_src.x / TILECX;
	_int srcY = (_int)_src.y / TILECY;
	_int dstX = (_int)dst.x / TILECX;
	_int dstY = (_int)dst.y / TILECY;

	if (dstX >= WORLDX || dstY >= WORLDY || dstX < 0 || dstY < 0)
		return E_FAIL;
	if (srcX >= WORLDX || srcY >= WORLDY || srcX < 0 || srcY < 0)
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

	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			if (nullptr != m_pTerrains[i][j])
				m_pTerrains[i][j]->Clear_Node();
		}
	}

	//지나온 노드(최종경로가 아니다)
	vector<CTerrain*> visited;
	//탐사한 노드
	set<CTerrain*> open;
	//검사의 중심이 되는 현재노드(그냥 visited의 마지막 노드)
	CTerrain* pCurrNode = m_pTerrains[srcY][srcX];

	_int currX = srcX;
	_int currY = srcY;

	_int minFcost = INT_MAX;
	//Fcost가 같으면 Hcost 기준으로 루트정함
	_int minHcost = INT_MAX;

	_int diaCost = (int)sqrt(TILECX * TILECX + TILECY * TILECY);

	int startHcost = 0;
	_int tmpX = abs(dstX - srcX);
	_int tmpY = abs(dstY - srcY);
	if (tmpX > tmpY)
		startHcost = tmpY * diaCost + (tmpX - tmpY) * TILECX;
	else
		startHcost = tmpX * diaCost + (tmpY - tmpX) * TILECX;

	//시작노드를 open리스트에 넣음
	pCurrNode->Set_Node(CTerrain::NODE(0, startHcost, startHcost, srcX, srcY, nullptr));
	open.emplace(pCurrNode);

#pragma endregion

	//더이상 탐색할 노드가 없을때까지
	while (open.size() > 0)
	{
		minFcost = INT_MAX;
		minHcost = INT_MAX;

		/*
		open set을 검사해서 Fcost가 가장 작은 노드를 찾는다.
		주의) 만약 INT_MAX가 아닌 curFcost랑 비교하면 Fcost가 현재 노드보다 더 커지는 경우는 배제해버린다.
		즉, 장애물을 돌아가는 경로는 아예 생각도 안해버림.
		*/
		for (auto& pTerrain : open)
		{
			CTerrain::NODE node = pTerrain->Get_Node();
			if (minFcost > node.Fcost)
			{
				minFcost = node.Fcost;
				pCurrNode = pTerrain;
				currX = node.X;
				currY = node.Y;
			}
			else if (minFcost == node.Fcost)
			{
				if (minHcost > node.Hcost)
				{
					minHcost = node.Hcost;
					pCurrNode = pTerrain;
					currX = node.X;
					currY = node.Y;
				}
			}

		}

		//선택된 노드는 open리스트에서 제거한다.
		open.erase(pCurrNode);
		//방문했다고 표시
		visited.push_back(pCurrNode);

		//목적지에 도달했으면 끝
		if (m_pTerrains[dstY][dstX] == pCurrNode)
			break;


		//현재노드의 왼쪽 위 타일의 인덱스
		int tmpY = currY - 1;
		int tmpX = currX - 1;

		//주변 8 타일을 검사해서 cost를 셋팅한다.
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
				if (!m_pTerrains[i][j]->IsMovable(_pMover))
					continue;
				//이미 방문한 곳이면 제외
				if (find(visited.begin(), visited.end(), m_pTerrains[i][j]) != visited.end())
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

				//끝 노드와의 거리
				_int distX = abs(dstX - j);
				_int distY = abs(dstY - i);

				/*
				대각선을 이용해야 최단거리다. 따라서 대각선을 만든다.
				X방향으로 1번 + Y방향으로 1번 = 대각선으로 1번
				*/
				//cost는 양수가 나와야 되기 때문에 나눠서 처리 
				if (distX > distY)
					Hcost = diaCost * distY + (distX - distY) * TILECX;
				else
					Hcost = diaCost * distX + (distY - distX) * TILECX;

				//현재노드와의 거리
				distX = abs(currX - j);
				distY = abs(currY - i);

				if (distX > distY)
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distY + (distX - distY) * TILECX);
				else
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distX + (distY - distX) * TILECX);

				Fcost = Hcost + Gcost;

				//만약 구한 Fcost가 기존의 것보다 작으면 기존 것을 갱신, 부모설정
				if (m_pTerrains[i][j]->Get_Node().Fcost > Fcost)
					m_pTerrains[i][j]->Set_Node(CTerrain::NODE(Gcost, Hcost, Fcost, j, i, pCurrNode));

				//검사대상에 넣는다. (중복없이)
				open.emplace(m_pTerrains[i][j]);


			}
		}
	}


	//visited에 들어가 있는건 방문했던 모든 노드다. 그 중에서 경로를 뽑아내야한다.

	//도착지점
	CTerrain* pLastNode = visited.back();

	//길을 찾지 못했을때는 목표와 가장 가까운 곳을 도착지로 설정
	if (open.size() == 0)
	{
		//경로중에 Hcost가 가장 낮은것을 목적지로함.
		//Hcost가 같으면 Gcost를 비교 낮은걸 취함. (더 이동이 적은것을 택함)
		if (visited.size() > 0)
		{
			pLastNode = visited[0];

			for (int i = 1; i < visited.size(); ++i)
			{
				_int lastHcost = pLastNode->Get_Node().Hcost;
				_int lastGcost = pLastNode->Get_Node().Gcost;
				_int currHcost = visited[i]->Get_Node().Hcost;
				_int currGcost = visited[i]->Get_Node().Gcost;

				if (lastHcost > currHcost)
				{
					pLastNode = visited[i];
				}
				else if (lastHcost == currHcost)
				{
					if (lastGcost > currGcost)
						pLastNode = visited[i];
				}
			}
		}
	}

	//부모가 없을때까지(시작노드까지)
	while (pLastNode->Get_Node().pParent != nullptr)
	{


		_out.push_back(pLastNode);
		//부모를 타고 들어가기
		pLastNode = pLastNode->Get_Node().pParent;
	}

	//뽑아낸건 경로의 반대이기 때문에 제대로 해줌
	reverse(_out.begin(), _out.end());
	return S_OK;
}

CTerrain * CLevel::Pick_Tile(POINT & _pt)
{
	vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
	for (auto& rc : UIRect)
	{
		//만약 마우스 포인트가 UI위에 있으면 무시
		if (PtInRect(&rc, _pt))
		{
			return nullptr;
		}
	}

	//마우스 좌표 변환
	Vector4 dst = Vector4(_pt.x, _pt.y, 0.f, 1.f);
	D3DXVec4Transform(&dst, &dst, &m_pPipline->Get_CameraMatrix_inverse());

	_uint x = (_uint)dst.x / TILECX;
	_uint y = (_uint)dst.y / TILECY;

	if (x >= WORLDX || y >= WORLDY || x < 0 || y < 0)
		return nullptr;

	return m_pTerrains[y][x];
}

CTerrain * CLevel::Pick_Tile(Vector3 & dst)
{
	_uint x = (_uint)dst.x / TILECX;
	_uint y = (_uint)dst.y / TILECY;

	if (x >= WORLDX || y >= WORLDY || x < 0 || y < 0)
		return nullptr;

	return m_pTerrains[y][x];
}

Vector3 CLevel::Get_RandomPos()
{
	_uint ranX = 0;
	_uint ranY = 0;

	do
	{
		ranX = rand() % WORLDX;
		ranY = rand() % WORLDY;

	} while (m_pTerrains[ranY][ranX] == nullptr || !m_pTerrains[ranY][ranX]->IsMovable(nullptr));

	return Vector3((float)ranX * TILECX, (float)ranY * TILECY, 0.f, 1.f);
}

Vector3 CLevel::Get_PlayerSpawnPos()
{
	return m_vPlayerSpawnPos;
}





HRESULT CLevel::Save_World(const _tchar* _filePath)
{
	HANDLE hFile = CreateFile(_filePath, GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	int zero = 0;
	int one = 1;
	int two = 2;
	//데이터 앞에 표시를 달자. 널이면 0, 널이 아니면 1, 마스크타일이면 2
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
	for (auto& maskTile : m_vecMask)
	{
		WriteFile(hFile, &two, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &maskTile->Get_SaveData(), sizeof(CTerrain::SAVE_DATA), &dwByte, NULL);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"Success", MB_OK);
	return S_OK;
}

HRESULT CLevel::Load_World(SCENEID _eSceneID)
{
	HANDLE hFile = CreateFile(m_pLoadfilePath, GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	////할 필요가 없음. 왜냐하면 타일을 미리 깔아두는게 아니기 때문에.
	//Free();

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


			CTerrain* pTerrain = dynamic_cast<CTerrain*>(CObjMgr::Get_Instance()->Add_GO_To_Layer(tSaveData.m_PrototypeTag, m_eSceneID, tSaveData.m_LayerTag, _eSceneID));
			if (nullptr == pTerrain)
			{
				MSG_BOX("타일 로드 실패");
				continue;
			}

			//마스크 타일이면
			if (2 == prefix)
				m_vecMask.push_back(pTerrain);
			//아니면
			else
				m_pTerrains[y][x] = pTerrain;

			if (0 == lstrcmp(tSaveData.m_PrototypeTag, L"lv_One_trap")	||
				0 == lstrcmp(tSaveData.m_PrototypeTag, L"lv_One_stair"))
			{
				m_listCollidable.push_back(pTerrain);
				Safe_AddRef(pTerrain);
			}

			Safe_AddRef(pTerrain);

			pTerrain->Load_Data(tSaveData);

			//계단이라면 그 위치를 저장한다. 플레이어의 스폰위치가 되니까.
			if (0 == lstrcmp(tSaveData.m_LayerTag, L"stair"))
			{
				CStair* pStair = dynamic_cast<CStair*>(m_pTerrains[y][x]);
				RETURN_FAIL_IF_NULL(pStair);
				if (CStair::TYPE_UP == pStair->Get_Type())
				{
					CTransform* pTransform = (CTransform*)pStair->Get_Module(L"Transform");
					RETURN_FAIL_IF_NULL(pTransform);
					m_vPlayerSpawnPos = pTransform->Get_Position();

				}
			}


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

HRESULT CLevel::Next_Level()
{
	//MSG_BOX("다음층으로 갑니다.");
	return S_OK;
}

HRESULT CLevel::Prv_Level()
{
	//MSG_BOX("이전층으로 갑니다.");
	return S_OK;
}

HRESULT CLevel::Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID)
{

	//타일 생성
	CTileLoader::CreateTilePrototype(_pGraphic_Device, SCENE_STAGE);

	return S_OK;
}

////_pObj와 _pObj가 서있는 타일을 충돌처리한다. (Obj의 중심점이 타일 안에 들어왔을때 충돌임)
//HRESULT CLevel::Collision_Terrain(CGameObject* _pObj)
//{
//	if (nullptr == _pObj)
//		return E_FAIL;
//
//	CTransform* pTransform = (CTransform*)_pObj->Get_Module(L"Transform");
//
//	//_pObj가 서있는 타일의 인덱스를 구한다.
//	int x = (int)pTransform->Get_Position().x / TILECX;
//	int y = (int)pTransform->Get_Position().y / TILECY;
//
//	if (x < 0 || y < 0 || x >= WORLDX || y >= WORLDY)
//		return E_FAIL;
//
//	if (nullptr == m_pTerrains[y][x])
//		return E_FAIL;
//
//	//_pObj가 서있는 타일 중심으로 전방향의 타일을 구한다.
//	//collision Exit을 특정하기 위해서는 모든 방향의 타일을 검사해야한다.
//	//플레이어 위치와 플레이어가 서있다고 계산한 타일의 위치는 꽤 엇나갈 수 있다.
//	//따라서 넓은 범위를 충돌검사해야한다.
//	list<CGameObject*> terrains;
//	for (int i = y - 2; i < y + 2; ++i)
//	{
//		for (int j = x - 2; j < x + 2; ++j)
//		{
//			if (nullptr != m_pTerrains[i][j])
//			{
//				terrains.push_back(m_pTerrains[i][j]);
//			}
//		}
//	}
//
//	//충돌처리.
//	CCollisionMgr::GameObjectInTile(list<CGameObject*>(1, _pObj), terrains);
//
//	return S_OK;
//}
//HRESULT CLevel::Collision_Terrain(list<CGameObject*> _pObjlist)
//{
//	for (auto& _pObj : _pObjlist)
//	{
//		if (nullptr == _pObj)
//			return E_FAIL;
//
//		CTransform* pTransform = (CTransform*)_pObj->Get_Module(L"Transform");
//
//		//_pObj가 서있는 타일의 인덱스를 구한다.
//		int x = (int)pTransform->Get_Position().x / TILECX;
//		int y = (int)pTransform->Get_Position().y / TILECY;
//
//		if (x < 0 || y < 0 || x >= WORLDX || y >= WORLDY)
//			return E_FAIL;
//
//		if (nullptr == m_pTerrains[y][x])
//			return E_FAIL;
//
//		//_pObj가 서있는 타일 중심으로 전방향의 타일을 구한다.
//		//collision Exit을 특정하기 위해서는 모든 방향의 타일을 검사해야한다.
//		//플레이어 위치와 플레이어가 서있다고 계산한 타일의 위치는 꽤 엇나갈 수 있다.
//		//따라서 넓은 범위를 충돌검사해야한다.
//		list<CGameObject*> terrains;
//		for (int i = y - 2; i < y + 2; ++i)
//		{
//			for (int j = x - 2; j < x + 2; ++j)
//			{
//				if (nullptr != m_pTerrains[i][j])
//				{
//					terrains.push_back(m_pTerrains[i][j]);
//				}
//			}
//		}
//
//		//충돌처리.
//		CCollisionMgr::GameObjectInTile(list<CGameObject*>(1, _pObj), terrains);
//
//	}
//
//	return S_OK;
//}

HRESULT CLevel::Collision_Terrain(CGameObject* _pObj)
{
	CCollisionMgr::GameObjectInTile(list<CGameObject*>(1, _pObj), m_listCollidable);
	return S_OK;
}

HRESULT CLevel::Collision_Terrain(list<CGameObject*> _pObjlist)
{
	CCollisionMgr::GameObjectInTile(_pObjlist, m_listCollidable);
	return S_OK;
}


CLevel * CLevel::Create(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, _tchar * _pFilePath)
{
	CLevel* pInstance = new CLevel(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_eSceneID, _pFilePath)))
	{
		MSG_BOX("Fail to create CLevel");
		Safe_Release(pInstance);

	}
	return pInstance;

}


void CLevel::Free()
{
	for (auto& collidable : m_listCollidable)
		Safe_Release(collidable);
	for (auto& mask : m_vecMask)
		Safe_Release(mask);

	for (auto& tileArr : m_pTerrains)
	{
		for (auto& tile : tileArr)
			Safe_Release(tile);
	}
	Safe_Release(m_pPipline);
	Safe_Release(m_pGraphic_Device);


}

