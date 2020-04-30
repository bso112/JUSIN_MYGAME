#include "stdafx.h"
#include "..\Headers\World.h"
#include "Terrain.h"
#include "Transform.h"
#include "ObjMgr.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CWorld)

CWorld::CWorld()
{
	ZeroMemory(&m_pTerrains, sizeof(m_pTerrains));
}

HRESULT CWorld::Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, _tchar* _pFilePath)
{

	//���̺����Ͽ��� �޾ƿ� ���� ������Ÿ���� �����.

	//���� ���� ������ �о� ������ ��ġ�Ѵ�.


	return S_OK;

}


HRESULT CWorld::Render()
{

	for (auto& tileArr : m_pTerrains)
	{
		if (tileArr != nullptr)
		{
			for (auto& tile : tileArr)
			{
				if (tile != nullptr)
					tile->Render();
			}

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


	//Ÿ���� �ε����� ���� Ÿ���� ��ǥ�� ���Ѵ�.
	float fX = (TILECX >> 1) + (float)(TILECX * x);
	float fY = (TILECY >> 1) + (float)(TILECY * y);

	if (x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	//��������
	CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

	//������ ��ġ�� �����Ѵ�.
	CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
	if (nullptr != pTransform)
	{
		pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
		pTransform->Update();
	}


	//���ŵ� ������ ������ ������ �ִ´�.
	m_pTerrains[y][x] = pTerrain;

	return S_OK;
}

HRESULT CWorld::Save_World()
{
	HANDLE hFile = CreateFile(L"../Bin/Data/Tile.dat", GENERIC_WRITE
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

HRESULT CWorld::Load_World()
{
	HANDLE hFile = CreateFile(L"../Bin/Data/Tile.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	//���� Ÿ���� ��� �����.
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
		//���� �����Ͱ� nullptr�� �ƴϸ� �д´�.
		if (0 != prefix)
		{

			ReadFile(hFile, &tSaveData, sizeof(CTerrain::SAVE_DATA), &dwByte, NULL);
			
			if (0 == dwByte)
				break;
			
			m_pTerrains[y][x] = (CTerrain*)CObjMgr::Get_Instance()->Add_GO_To_Layer(tSaveData.m_PrototypeTag, SCENE_EDITOR, L"Terrain", SCENE_EDITOR);
			if (nullptr == m_pTerrains[y][x])
				return E_FAIL;
			Safe_AddRef(m_pTerrains[y][x]);
			CTransform* pTransform = (CTransform*)m_pTerrains[y][x]->Get_Module(L"Transform");
			if (nullptr == pTransform)
				return E_FAIL;

			pTransform->Set_Position(tSaveData.m_vPosition);
			pTransform->Set_Rotation(tSaveData.m_vRotation);
			pTransform->Set_Size(tSaveData.m_vSize);
		
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


void CWorld::Free()
{
	for (auto& tileArr : m_pTerrains)
	{
		for (auto& tile : tileArr)
			Safe_Release(tile);
	}

}

