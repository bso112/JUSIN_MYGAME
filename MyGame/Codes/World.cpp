#include "stdafx.h"
#include "..\Headers\World.h"
#include "Terrain.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CWorld)


HRESULT CWorld::Generate_World(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath)
{

	//���� ������Ÿ���� �����.

	//���� ���� ������ �о� ������ ��ġ�Ѵ�.

	
	////������ ���� TILEX *  TILEY��ŭ Ÿ���� �׸���. 
	////y��, �� ���� ���� ��� ������ ������ +1�ȴ�.
	//for (int i = 0; i < TILEY; ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		//Ÿ���� �ε����� ���� Ÿ���� ��ǥ�� ���Ѵ�.
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

