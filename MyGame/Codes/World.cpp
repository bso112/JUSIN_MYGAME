#include "stdafx.h"
#include "..\Headers\World.h"
#include "Terrain.h"
#include "Transform.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CWorld)


HRESULT CWorld::Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, _tchar* _pFilePath)
{

	//세이브파일에서 받아와 지형 프로토타입을 만든다.

	//월드 정보 파일을 읽어 지형을 배치한다.


	//디파인 잡은 TILEX *  TILEY만큼 타일을 그린다. 
	//y축, 즉 행은 열을 모두 생성한 다음에 +1된다.
	for (int i = 0; i < WORLDY; ++i)
	{
		for (int j = 0; j < WORLDX; ++j)
		{
			//타일의 인덱스에 따른 타일의 좌표를 구한다.
			float fX = (TILECX >> 1) + (float)(TILECX * j);
			float fY = (TILECY >> 1) + (float)(TILECY * i);

			CTerrain* pTerrain = CTerrain::Create(_pGraphic_Device, TERRAIN(), L"lv1_door_locked", SCENE_EDITOR);
			if (nullptr == pTerrain)
				return E_FAIL;
			CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
			if (nullptr == pTransform)
				return E_FAIL;

			pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
			pTransform->Update();
			m_vecTerrain.push_back(pTerrain);

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
	if (nullptr == _pTerrain)
		return E_FAIL;

	int x = _pt.x / WORLDX;
	int y = _pt.y / WORLDY;

	size_t index = x + y * WORLDX;

	//타일의 인덱스에 따른 타일의 좌표를 구한다.
	float fX = (TILECX >> 1) + (float)(TILECX * x);
	float fY = (TILECY >> 1) + (float)(TILECY * y);

	if (index >= m_vecTerrain.size())
		return E_FAIL;

	//깊은복사
	CTerrain* pTerrain = (CTerrain*)_pTerrain->Clone();

	CTransform* pTransform = (CTransform*)pTerrain->Get_Module(L"Transform");
	if (nullptr != pTransform)
	{
		pTransform->Set_Position(Vector2(fX, fY, 0.f, 1.f));
		pTransform->Update();
	}

	Safe_Release(m_vecTerrain[index]);

	m_vecTerrain[index] = pTerrain;

	return S_OK;
}


void CWorld::Free()
{
	for (auto& tile : m_vecTerrain)
	{
		Safe_Release(tile);
	}

}

