#include "stdafx.h"
#include "..\Headers\World.h"
#include "Terrain.h"
#include "Transform.h"
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
				if(tile != nullptr)
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


void CWorld::Free()
{
	for (auto& tileArr : m_pTerrains)
	{
		for (auto& tile : tileArr)
			Safe_Release(tile);
	}

}

