#include "stdafx.h"
#include "..\Headers\World.h"
#include "Terrain.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CWorld)


HRESULT CWorld::Generate_World(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath)
{

	//지형 프로토타입을 만든다.

	//월드 정보 파일을 읽어 지형을 배치한다.

	
	////디파인 잡은 TILEX *  TILEY만큼 타일을 그린다. 
	////y축, 즉 행은 열을 모두 생성한 다음에 +1된다.
	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		//타일의 인덱스에 따른 타일의 좌표를 구한다.
	//		float fX = (TILECX >> 1) + (float)(TILECX * j);
	//		float fY = (TILECY >> 1) + (float)(TILECY * i);

	//	}
	//}

	return S_OK;

}


HRESULT CWorld::Render()
{
	return S_OK;
}


void CWorld::Free()
{
	for (auto& tile : m_vecTerrain)
	{
		Safe_Release(tile);
	}

}

