#include "stdafx.h"
#include "Level.h"
#include "Terrain.h"
#include "Transform.h"
#include "ObjMgr.h"
#include "Door.h"
#include "Stair.h"
#include "CollisionMgr.h"
#include "Stair.h"
#include "StageUIMgr.h"

USING(MyGame)


CLevel::CLevel(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
	ZeroMemory(&m_pTerrains, sizeof(m_pTerrains));
}

HRESULT CLevel::Initialize(SCENEID _eSceneID, _tchar* _pFilePath)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_eSceneID = _eSceneID;
	//���� ������Ÿ���� �����.
	if (_eSceneID != SCENE_EDITOR)
		Initalize_Prototypes(m_pGraphic_Device, _eSceneID);

	m_pLoadfilePath = _pFilePath;
	return S_OK;

}


HRESULT CLevel::Render_ForEditor()
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

HRESULT CLevel::Set_Terrain(CTerrain * _pTerrain, POINT& _pt)
{
	if (nullptr == _pTerrain)
		return E_FAIL;

	_uint x = _pt.x / TILECX;
	_uint y = _pt.y / TILECY;


	//Ÿ���� �ε����� ���� Ÿ���� ��ǥ�� ���Ѵ�.
	float fX = (TILECX >> 1) + (float)(TILECX * x);
	float fY = (TILECY >> 1) + (float)(TILECY * y);

	if (x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	//���� �̹� Ÿ���� �ִٸ� �����
	if (nullptr != m_pTerrains[y][x])
	{
		Safe_Release(m_pTerrains[y][x]);
		return S_OK;
	}


	//��������
	CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

	//������ ��ġ�� �����Ѵ�.
	CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
	if (nullptr != pTransform)
	{
		pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
		pTransform->Late_Update();
	}

	//Ÿ���� ä���.
	m_pTerrains[y][x] = pTerrain;

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


HRESULT CLevel::Get_Route(Vector3 _src, POINT _dst, vector<Vector3>& _out, CTransform* _pMover)
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

	//���̽�Ÿ
	/*
	Gcost // distance from staring node
	Hcost // distance from end node
	Fcost // Gcost + Hcost
	*/

#pragma region �ʱ�ȭ

	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			if (nullptr != m_pTerrains[i][j])
				m_pTerrains[i][j]->Clear_Node();
		}
	}

	//������ ���(������ΰ� �ƴϴ�)
	vector<CTerrain*> visited;
	//Ž���� ���
	set<CTerrain*> open;
	//�˻��� �߽��� �Ǵ� ������(�׳� visited�� ������ ���)
	CTerrain* pCurrNode = m_pTerrains[srcY][srcX];

	_int currX = srcX;
	_int currY = srcY;

	_int minFcost = INT_MAX;
	//Fcost�� ������ Hcost �������� ��Ʈ����
	_int minHcost = INT_MAX;

	_int diaCost = (int)sqrt(TILECX * TILECX + TILECY * TILECY);

	int startHcost = 0;
	_int tmpX = abs(dstX - srcX);
	_int tmpY = abs(dstY - srcY);
	if (tmpX > tmpY)
		startHcost = tmpY * diaCost + (tmpX - tmpY) * TILECX;
	else
		startHcost = tmpX * diaCost + (tmpY - tmpX) * TILECX;

	//���۳�带 open����Ʈ�� ����
	pCurrNode->Set_Node(CTerrain::NODE(0, startHcost, startHcost, srcX, srcY, nullptr));
	open.emplace(pCurrNode);

#pragma endregion

	//���̻� Ž���� ��尡 ����������
	while (open.size() > 0)
	{
		minFcost = INT_MAX;
		minHcost = INT_MAX;

		/*
		open set�� �˻��ؼ� Fcost�� ���� ���� ��带 ã�´�.
		����) ���� INT_MAX�� �ƴ� curFcost�� ���ϸ� Fcost�� ���� ��庸�� �� Ŀ���� ���� �����ع�����.
		��, ��ֹ��� ���ư��� ��δ� �ƿ� ������ ���ع���.
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

		//���õ� ���� open����Ʈ���� �����Ѵ�.
		open.erase(pCurrNode);
		//�湮�ߴٰ� ǥ��
		visited.push_back(pCurrNode);

		//�������� ���������� ��
		if (m_pTerrains[dstY][dstX] == pCurrNode)
			break;


		//�������� ���� �� Ÿ���� �ε���
		int tmpY = currY - 1;
		int tmpX = currX - 1;

		//�ֺ� 8 Ÿ���� �˻��ؼ� cost�� �����Ѵ�.
		for (int i = tmpY; i <= tmpY + 2; ++i)
		{
			for (int j = tmpX; j <= tmpX + 2; ++j)
			{
#pragma region ����ó��
				//��ȿ���� ���� Ÿ�� ����
				if (i >= WORLDX || j >= WORLDY || i < 0 || j < 0)
					continue;
				if (nullptr == m_pTerrains[i][j])
					continue;
				//���� ���ϴ� ���̸� ����
				if (!m_pTerrains[i][j]->IsMovable(_pMover))
					continue;
				//�̹� �湮�� ���̸� ����
				if (find(visited.begin(), visited.end(), m_pTerrains[i][j]) != visited.end())
					continue;
				//�ڱ��ڽ� ����
				if (i == currY && j == currX)
					continue;
				//�ڱ��ڽ��� nullptr�� ����
				if (nullptr == pCurrNode)
					return E_FAIL;

#pragma endregion
				//cost ���ϱ�
				_int Gcost = 0;
				_int Hcost = 0;
				_int Fcost = 0;

				//�� ������ �Ÿ�
				_int distX = abs(dstX - j);
				_int distY = abs(dstY - i);

				/*
				�밢���� �̿��ؾ� �ִܰŸ���. ���� �밢���� �����.
				X�������� 1�� + Y�������� 1�� = �밢������ 1��
				*/
				//cost�� ����� ���;� �Ǳ� ������ ������ ó�� 
				if (distX > distY)
					Hcost = diaCost * distY + (distX - distY) * TILECX;
				else
					Hcost = diaCost * distX + (distY - distX) * TILECX;

				//��������� �Ÿ�
				distX = abs(currX - j);
				distY = abs(currY - i);

				if (distX > distY)
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distY + (distX - distY) * TILECX);
				else
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distX + (distY - distX) * TILECX);

				Fcost = Hcost + Gcost;

				//���� ���� Fcost�� ������ �ͺ��� ������ ���� ���� ����, �θ���
				if (m_pTerrains[i][j]->Get_Node().Fcost > Fcost)
					m_pTerrains[i][j]->Set_Node(CTerrain::NODE(Gcost, Hcost, Fcost, j, i, pCurrNode));

				//�˻��� �ִ´�. (�ߺ�����)
				open.emplace(m_pTerrains[i][j]);


			}
		}
	}


	//visited�� �� �ִ°� �湮�ߴ� ��� ����. �� �߿��� ��θ� �̾Ƴ����Ѵ�.

	//��������
	CTerrain* pLastNode = visited.back();

	//���� ã�� ���������� ��ǥ�� ���� ����� ���� �������� ����
	if (open.size() == 0)
	{
		//����߿� Hcost�� ���� �������� ����������.
		//Hcost�� ������ Gcost�� �� ������ ����. (�� �̵��� �������� ����)
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

	//�θ� ����������(���۳�����)
	while (pLastNode->Get_Node().pParent != nullptr)
	{
		CTransform* pTransform = (CTransform*)pLastNode->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return E_FAIL;

		_out.push_back(pTransform->Get_Position());

		//�θ� Ÿ�� ����
		pLastNode = pLastNode->Get_Node().pParent;
	}

	//�̾Ƴ��� ����� �ݴ��̱� ������ ����� ����
	reverse(_out.begin(), _out.end());
	return S_OK;
}

HRESULT CLevel::Get_Route(Vector3 _src, Vector3 _dst, vector<Vector3>& _out, CTransform* _pMover)
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

	//���̽�Ÿ
	/*
	Gcost // distance from staring node
	Hcost // distance from end node
	Fcost // Gcost + Hcost
	*/

#pragma region �ʱ�ȭ

	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			if (nullptr != m_pTerrains[i][j])
				m_pTerrains[i][j]->Clear_Node();
		}
	}

	//������ ���(������ΰ� �ƴϴ�)
	vector<CTerrain*> visited;
	//Ž���� ���
	set<CTerrain*> open;
	//�˻��� �߽��� �Ǵ� ������(�׳� visited�� ������ ���)
	CTerrain* pCurrNode = m_pTerrains[srcY][srcX];

	_int currX = srcX;
	_int currY = srcY;

	_int minFcost = INT_MAX;
	//Fcost�� ������ Hcost �������� ��Ʈ����
	_int minHcost = INT_MAX;

	_int diaCost = (int)sqrt(TILECX * TILECX + TILECY * TILECY);

	int startHcost = 0;
	_int tmpX = abs(dstX - srcX);
	_int tmpY = abs(dstY - srcY);
	if (tmpX > tmpY)
		startHcost = tmpY * diaCost + (tmpX - tmpY) * TILECX;
	else
		startHcost = tmpX * diaCost + (tmpY - tmpX) * TILECX;

	//���۳�带 open����Ʈ�� ����
	pCurrNode->Set_Node(CTerrain::NODE(0, startHcost, startHcost, srcX, srcY, nullptr));
	open.emplace(pCurrNode);

#pragma endregion

	//���̻� Ž���� ��尡 ����������
	while (open.size() > 0)
	{
		minFcost = INT_MAX;
		minHcost = INT_MAX;

		/*
		open set�� �˻��ؼ� Fcost�� ���� ���� ��带 ã�´�.
		����) ���� INT_MAX�� �ƴ� curFcost�� ���ϸ� Fcost�� ���� ��庸�� �� Ŀ���� ���� �����ع�����.
		��, ��ֹ��� ���ư��� ��δ� �ƿ� ������ ���ع���.
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

		//���õ� ���� open����Ʈ���� �����Ѵ�.
		open.erase(pCurrNode);
		//�湮�ߴٰ� ǥ��
		visited.push_back(pCurrNode);

		//�������� ���������� ��
		if (m_pTerrains[dstY][dstX] == pCurrNode)
			break;


		//�������� ���� �� Ÿ���� �ε���
		int tmpY = currY - 1;
		int tmpX = currX - 1;

		//�ֺ� 8 Ÿ���� �˻��ؼ� cost�� �����Ѵ�.
		for (int i = tmpY; i <= tmpY + 2; ++i)
		{
			for (int j = tmpX; j <= tmpX + 2; ++j)
			{
#pragma region ����ó��
				//��ȿ���� ���� Ÿ�� ����
				if (i >= WORLDX || j >= WORLDY || i < 0 || j < 0)
					continue;
				if (nullptr == m_pTerrains[i][j])
					continue;
				//���� ���ϴ� ���̸� ����
				if (!m_pTerrains[i][j]->IsMovable(_pMover))
					continue;
				//�̹� �湮�� ���̸� ����
				if (find(visited.begin(), visited.end(), m_pTerrains[i][j]) != visited.end())
					continue;
				//�ڱ��ڽ� ����
				if (i == currY && j == currX)
					continue;
				//�ڱ��ڽ��� nullptr�� ����
				if (nullptr == pCurrNode)
					return E_FAIL;

#pragma endregion
				//cost ���ϱ�
				_int Gcost = 0;
				_int Hcost = 0;
				_int Fcost = 0;

				//�� ������ �Ÿ�
				_int distX = abs(dstX - j);
				_int distY = abs(dstY - i);

				/*
				�밢���� �̿��ؾ� �ִܰŸ���. ���� �밢���� �����.
				X�������� 1�� + Y�������� 1�� = �밢������ 1��
				*/
				//cost�� ����� ���;� �Ǳ� ������ ������ ó�� 
				if (distX > distY)
					Hcost = diaCost * distY + (distX - distY) * TILECX;
				else
					Hcost = diaCost * distX + (distY - distX) * TILECX;

				//��������� �Ÿ�
				distX = abs(currX - j);
				distY = abs(currY - i);

				if (distX > distY)
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distY + (distX - distY) * TILECX);
				else
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distX + (distY - distX) * TILECX);

				Fcost = Hcost + Gcost;

				//���� ���� Fcost�� ������ �ͺ��� ������ ���� ���� ����, �θ���
				if (m_pTerrains[i][j]->Get_Node().Fcost > Fcost)
					m_pTerrains[i][j]->Set_Node(CTerrain::NODE(Gcost, Hcost, Fcost, j, i, pCurrNode));

				//�˻��� �ִ´�. (�ߺ�����)
				open.emplace(m_pTerrains[i][j]);


			}
		}
	}


	//visited�� �� �ִ°� �湮�ߴ� ��� ����. �� �߿��� ��θ� �̾Ƴ����Ѵ�.

	//��������
	CTerrain* pLastNode = visited.back();

	//���� ã�� ���������� ��ǥ�� ���� ����� ���� �������� ����
	if (open.size() == 0)
	{
		//����߿� Hcost�� ���� �������� ����������.
		//Hcost�� ������ Gcost�� �� ������ ����. (�� �̵��� �������� ����)
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

	//�θ� ����������(���۳�����)
	while (pLastNode->Get_Node().pParent != nullptr)
	{
		CTransform* pTransform = (CTransform*)pLastNode->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return E_FAIL;

		_out.push_back(pTransform->Get_Position());

		//�θ� Ÿ�� ����
		pLastNode = pLastNode->Get_Node().pParent;
	}

	//�̾Ƴ��� ����� �ݴ��̱� ������ ����� ����
	reverse(_out.begin(), _out.end());
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

	//���̽�Ÿ
	/*
	Gcost // distance from staring node
	Hcost // distance from end node
	Fcost // Gcost + Hcost
	*/

#pragma region �ʱ�ȭ

	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			if (nullptr != m_pTerrains[i][j])
				m_pTerrains[i][j]->Clear_Node();
		}
	}

	//������ ���(������ΰ� �ƴϴ�)
	vector<CTerrain*> visited;
	//Ž���� ���
	set<CTerrain*> open;
	//�˻��� �߽��� �Ǵ� ������(�׳� visited�� ������ ���)
	CTerrain* pCurrNode = m_pTerrains[srcY][srcX];

	_int currX = srcX;
	_int currY = srcY;

	_int minFcost = INT_MAX;
	//Fcost�� ������ Hcost �������� ��Ʈ����
	_int minHcost = INT_MAX;

	_int diaCost = (int)sqrt(TILECX * TILECX + TILECY * TILECY);

	int startHcost = 0;
	_int tmpX = abs(dstX - srcX);
	_int tmpY = abs(dstY - srcY);
	if (tmpX > tmpY)
		startHcost = tmpY * diaCost + (tmpX - tmpY) * TILECX;
	else
		startHcost = tmpX * diaCost + (tmpY - tmpX) * TILECX;

	//���۳�带 open����Ʈ�� ����
	pCurrNode->Set_Node(CTerrain::NODE(0, startHcost, startHcost, srcX, srcY, nullptr));
	open.emplace(pCurrNode);

#pragma endregion

	//���̻� Ž���� ��尡 ����������
	while (open.size() > 0)
	{
		minFcost = INT_MAX;
		minHcost = INT_MAX;

		/*
		open set�� �˻��ؼ� Fcost�� ���� ���� ��带 ã�´�.
		����) ���� INT_MAX�� �ƴ� curFcost�� ���ϸ� Fcost�� ���� ��庸�� �� Ŀ���� ���� �����ع�����.
		��, ��ֹ��� ���ư��� ��δ� �ƿ� ������ ���ع���.
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

		//���õ� ���� open����Ʈ���� �����Ѵ�.
		open.erase(pCurrNode);
		//�湮�ߴٰ� ǥ��
		visited.push_back(pCurrNode);

		//�������� ���������� ��
		if (m_pTerrains[dstY][dstX] == pCurrNode)
			break;


		//�������� ���� �� Ÿ���� �ε���
		int tmpY = currY - 1;
		int tmpX = currX - 1;

		//�ֺ� 8 Ÿ���� �˻��ؼ� cost�� �����Ѵ�.
		for (int i = tmpY; i <= tmpY + 2; ++i)
		{
			for (int j = tmpX; j <= tmpX + 2; ++j)
			{
#pragma region ����ó��
				//��ȿ���� ���� Ÿ�� ����
				if (i >= WORLDX || j >= WORLDY || i < 0 || j < 0)
					continue;
				if (nullptr == m_pTerrains[i][j])
					continue;
				//���� ���ϴ� ���̸� ����
				if (!m_pTerrains[i][j]->IsMovable(_pMover))
					continue;
				//�̹� �湮�� ���̸� ����
				if (find(visited.begin(), visited.end(), m_pTerrains[i][j]) != visited.end())
					continue;
				//�ڱ��ڽ� ����
				if (i == currY && j == currX)
					continue;
				//�ڱ��ڽ��� nullptr�� ����
				if (nullptr == pCurrNode)
					return E_FAIL;

#pragma endregion
				//cost ���ϱ�
				_int Gcost = 0;
				_int Hcost = 0;
				_int Fcost = 0;

				//�� ������ �Ÿ�
				_int distX = abs(dstX - j);
				_int distY = abs(dstY - i);

				/*
				�밢���� �̿��ؾ� �ִܰŸ���. ���� �밢���� �����.
				X�������� 1�� + Y�������� 1�� = �밢������ 1��
				*/
				//cost�� ����� ���;� �Ǳ� ������ ������ ó�� 
				if (distX > distY)
					Hcost = diaCost * distY + (distX - distY) * TILECX;
				else
					Hcost = diaCost * distX + (distY - distX) * TILECX;

				//��������� �Ÿ�
				distX = abs(currX - j);
				distY = abs(currY - i);

				if (distX > distY)
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distY + (distX - distY) * TILECX);
				else
					Gcost = pCurrNode->Get_Node().Gcost + (diaCost * distX + (distY - distX) * TILECX);

				Fcost = Hcost + Gcost;

				//���� ���� Fcost�� ������ �ͺ��� ������ ���� ���� ����, �θ���
				if (m_pTerrains[i][j]->Get_Node().Fcost > Fcost)
					m_pTerrains[i][j]->Set_Node(CTerrain::NODE(Gcost, Hcost, Fcost, j, i, pCurrNode));

				//�˻��� �ִ´�. (�ߺ�����)
				open.emplace(m_pTerrains[i][j]);


			}
		}
	}


	//visited�� �� �ִ°� �湮�ߴ� ��� ����. �� �߿��� ��θ� �̾Ƴ����Ѵ�.

	//��������
	CTerrain* pLastNode = visited.back();

	//���� ã�� ���������� ��ǥ�� ���� ����� ���� �������� ����
	if (open.size() == 0)
	{
		//����߿� Hcost�� ���� �������� ����������.
		//Hcost�� ������ Gcost�� �� ������ ����. (�� �̵��� �������� ����)
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

	//�θ� ����������(���۳�����)
	while (pLastNode->Get_Node().pParent != nullptr)
	{


		_out.push_back(pLastNode);
		//�θ� Ÿ�� ����
		pLastNode = pLastNode->Get_Node().pParent;
	}

	//�̾Ƴ��� ����� �ݴ��̱� ������ ����� ����
	reverse(_out.begin(), _out.end());
	return S_OK;
}

CTerrain * CLevel::Pick_Tile(POINT & _pt)
{
	vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
	for (auto& rc : UIRect)
	{
		//���� ���콺 ����Ʈ�� UI���� ������ ����
		if (PtInRect(&rc, _pt))
		{
			return nullptr;
		}
	}

	_uint x = _pt.x / TILECX;
	_uint y = _pt.y / TILECY;

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
	//������ �տ� ǥ�ø� ����. ���̸� 0, ���� �ƴϸ� 1
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

HRESULT CLevel::Load_World(SCENEID _eSceneID)
{
	HANDLE hFile = CreateFile(m_pLoadfilePath, GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	////���� Ÿ���� ��� �����.
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
		//���� �����Ͱ� nullptr�� �ƴϸ� �д´�.
		if (0 != prefix)
		{

			ReadFile(hFile, &tSaveData, sizeof(CTerrain::SAVE_DATA), &dwByte, NULL);

			if (0 == dwByte)
				break;

			/*
			������Ÿ�� �±׸� ���� �ùٸ� Ŭ������ ��ȯ�Ѵ�.
			������� CDoor�� ������Ÿ�Կ��� ����� CGameObject�� CTerrain���� ��ȯ�Ǿ� Load_Data�� ���� �����Ͱ� ���õȴ�.
			*/
			m_pTerrains[y][x] = dynamic_cast<CTerrain*>(CObjMgr::Get_Instance()->Add_GO_To_Layer(tSaveData.m_PrototypeTag, m_eSceneID, tSaveData.m_LayerTag, _eSceneID));
			if (nullptr == m_pTerrains[y][x])
				return E_FAIL;
			Safe_AddRef(m_pTerrains[y][x]);

			m_pTerrains[y][x]->Load_Data(tSaveData);

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
	MSG_BOX("���������� ���ϴ�.");
	return S_OK;
}

HRESULT CLevel::Prv_Level()
{
	MSG_BOX("���������� ���ϴ�.");
	return S_OK;
}

HRESULT CLevel::Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID)
{

#pragma region Ÿ�ϻ���

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;
	Safe_AddRef(pObjMgr);

	//�ȷ�Ʈ�� �� Ÿ��(������Ÿ��)�� �����.
	CTerrain* pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(false), L"lv_One_bookshelf", _eSceneID);
	//������Ʈ �Ŵ����� ����Ѵ�.
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
	pTerrain = CStair::Create(_pGraphic_Device, TERRAIN(true), L"lv_One_stair", _eSceneID, L"stair");
	pObjMgr->Add_Prototype(L"lv_One_stair", _eSceneID, pTerrain);
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

//_pObj�� _pObj�� ���ִ� Ÿ���� �浹ó���Ѵ�. 
HRESULT CLevel::Collision_Terrain(CGameObject* _pObj)
{
	if (nullptr == _pObj)
		return E_FAIL;

	CTransform* pTransform = (CTransform*)_pObj->Get_Module(L"Transform");

	//_pObj�� ���ִ� Ÿ���� �ε����� ���Ѵ�.
	int x = (int)pTransform->Get_Position().x / TILECX;
	int y = (int)pTransform->Get_Position().y / TILECY;

	if (x < 0 || y < 0 || x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	if (nullptr == m_pTerrains[y][x])
		return E_FAIL;

	//_pObj�� ���ִ� Ÿ�� �߽����� �������� Ÿ���� ���Ѵ�.
	//collision Exit�� Ư���ϱ� ���ؼ��� ��� ������ Ÿ���� �˻��ؾ��Ѵ�.
	//�÷��̾� ��ġ�� �÷��̾ ���ִٰ� ����� Ÿ���� ��ġ�� �� ������ �� �ִ�.
	//���� ���� ������ �浹�˻��ؾ��Ѵ�.
	list<CGameObject*> terrains;
	for (int i = y - 2; i < y + 2; ++i)
	{
		for (int j = x - 2; j < x + 2; ++j)
		{
			if (nullptr != m_pTerrains[i][j])
			{
				terrains.push_back(m_pTerrains[i][j]);
			}
		}
	}

	//�浹ó��.
	CCollisionMgr::GameObjectInTile(list<CGameObject*>(1, _pObj), terrains);

	return S_OK;
}




HRESULT CLevel::Collision_Terrain(list<CGameObject*> _pObjlist)
{
	for (auto& _pObj : _pObjlist)
	{
		if (nullptr == _pObj)
			return E_FAIL;

		CTransform* pTransform = (CTransform*)_pObj->Get_Module(L"Transform");

		//_pObj�� ���ִ� Ÿ���� �ε����� ���Ѵ�.
		int x = (int)pTransform->Get_Position().x / TILECX;
		int y = (int)pTransform->Get_Position().y / TILECY;

		if (x < 0 || y < 0 || x >= WORLDX || y >= WORLDY)
			return E_FAIL;

		if (nullptr == m_pTerrains[y][x])
			return E_FAIL;

		//_pObj�� ���ִ� Ÿ�� �߽����� �������� Ÿ���� ���Ѵ�.
		//collision Exit�� Ư���ϱ� ���ؼ��� ��� ������ Ÿ���� �˻��ؾ��Ѵ�.
		//�÷��̾� ��ġ�� �÷��̾ ���ִٰ� ����� Ÿ���� ��ġ�� �� ������ �� �ִ�.
		//���� ���� ������ �浹�˻��ؾ��Ѵ�.
		list<CGameObject*> terrains;
		for (int i = y - 2; i < y + 2; ++i)
		{
			for (int j = x - 2; j < x + 2; ++j)
			{
				if (nullptr != m_pTerrains[i][j])
				{
					terrains.push_back(m_pTerrains[i][j]);
				}
			}
		}

		//�浹ó��.
		CCollisionMgr::GameObjectInTile(list<CGameObject*>(1, _pObj), terrains);

	}

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
	for (auto& tileArr : m_pTerrains)
	{
		for (auto& tile : tileArr)
			Safe_Release(tile);
	}
	Safe_Release(m_pGraphic_Device);


}

