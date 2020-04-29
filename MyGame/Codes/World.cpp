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

	//세이브파일에서 받아와 지형 프로토타입을 만든다.

	//월드 정보 파일을 읽어 지형을 배치한다.


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


	//타일의 인덱스에 따른 타일의 좌표를 구한다.
	float fX = (TILECX >> 1) + (float)(TILECX * x);
	float fY = (TILECY >> 1) + (float)(TILECY * y);

	if (x >= WORLDX || y >= WORLDY)
		return E_FAIL;

	//깊은복사
	CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

	//지형의 위치를 지정한다.
	CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
	if (nullptr != pTransform)
	{
		pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
		pTransform->Update();
	}


	//제거된 공간에 생성한 지형을 넣는다.
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

