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
	//디파인 잡은 TILEX *  TILEY만큼 타일을 그린다. 
	//y축, 즉 행은 열을 모두 생성한 다음에 +1된다.
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			//타일의 인덱스에 따른 타일의 좌표를 구한다.
			float fX = (TILECX >> 1) + (float)(TILECX * j);
			float fY = (TILECY >> 1) + (float)(TILECY * i);

			//그 좌표에 타일을 만든다.
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

