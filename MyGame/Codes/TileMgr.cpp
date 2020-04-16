#include "stdafx.h"
#include "..\Headers\TileMgr.h"
#include "Tile.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CTileMgr)

CTileMgr::CTileMgr()
{
}

HRESULT CTileMgr::Initialize()
{
	//������ ���� TILEX *  TILEY��ŭ Ÿ���� �׸���. 
	//y��, �� ���� ���� ��� ������ ������ +1�ȴ�.
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			//Ÿ���� �ε����� ���� Ÿ���� ��ǥ�� ���Ѵ�.
			float fX = (TILECX >> 1) + (float)(TILECX * j);
			float fY = (TILECY >> 1) + (float)(TILECY * i);

			//�� ��ǥ�� Ÿ���� �����.
			m_vecTile.emplace_back(CTile::Create(fX, fY));
		}
	}

	return S_OK;

}

_int CTileMgr::Update()
{
	return _int();
}

HRESULT CTileMgr::Render(HDC _DC)
{
	for (auto& tile : m_vecTile)
		if(nullptr != tile)
			tile->Render(_DC);

	return S_OK;
}

void CTileMgr::Free()
{
	for (auto& tile : m_vecTile)
	{
		Safe_Release(tile);
	}

}

