#include "stdafx.h"
#include "..\Headers\World.h"
#include "Terrain.h"
#include "Transform.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CWorld)


HRESULT CWorld::Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, _tchar* _pFilePath)
{

	//���̺����Ͽ��� �޾ƿ� ���� ������Ÿ���� �����.

	//���� ���� ������ �о� ������ ��ġ�Ѵ�.

	
	//������ ���� TILEX *  TILEY��ŭ Ÿ���� �׸���. 
	//y��, �� ���� ���� ��� ������ ������ +1�ȴ�.
	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			//Ÿ���� �ε����� ���� Ÿ���� ��ǥ�� ���Ѵ�.
			float fX = (TILECX >> 1) + (float)(TILECX * j);
			float fY = (TILECY >> 1) + (float)(TILECY * i);

			m_vecTerrain.push_back(CTerrain::Create(_pGraphic_Device, TERRAIN(), L"empty", SCENE_STATIC));
		}
	}


	return S_OK;

}


HRESULT CWorld::Render()
{

	for (auto& tile : m_vecTerrain)
	{
		tile->Render();
	}
	return S_OK;
}

HRESULT CWorld::Set_Terrain(CTerrain * _pTerrain, POINT& _pt)
{
	//int x = _pt.x / WORLDX;
	//int y = _pt.y / WORLDY;

	//size_t index = x + y * WORLDX;

	////Ÿ���� �ε����� ���� Ÿ���� ��ǥ�� ���Ѵ�.
	//float fX = (TILECX >> 1) + (float)(TILECX * x);
	//float fY = (TILECY >> 1) + (float)(TILECY * y);

	//if (index >= m_vecTerrain.size())
	//	return E_FAIL;

	//CTransform* pTransform = (CTransform*)_pTerrain->Get_Module(L"Trasform");
	//if (nullptr != pTransform)
	//{
	//	pTransform->Set_Position(Vector2(fX, fY));
	//}

	//Safe_Release(m_vecTerrain[index]);
	//
	//m_vecTerrain[index] = _pTerrain;

	return S_OK;
}


void CWorld::Free()
{
	for (auto& tile : m_vecTerrain)
	{
		Safe_Release(tile);
	}

}

