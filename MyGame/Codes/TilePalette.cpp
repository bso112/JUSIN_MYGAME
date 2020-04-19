#include "stdafx.h"
#include "..\Headers\TilePalette.h"
#include "Terrain.h"
#include "Transform.h"

USING(MyGame)

HRESULT CTilePalette::Initalize()
{

	//팔레트의 왼쪽 위 위치를 정한다.

	m_fX = 300.f;
	m_fY = 300.f;

	//팔레트에 쓸 타일을 만든다.

	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_FLOOR));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_FLOOR_GRASS));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_FLOOR_BURND));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_FLOOR_GRASS));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_FLOOR_MOSSY));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_FLOOR_WOOD));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_FLOOR_BURND));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_GRASS_GREEN));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_GRASS_ASH));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_SING));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_STAIR_UP));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), MODULE_TEXTURE_STAIR_DOWN));

	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), MODULE_TEXTURE_BOOKSHELF));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), MODULE_TEXTURE_STATUE_WITH_FLOOR));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), MODULE_TEXTURE_STATUE_WITH_WOOD));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), MODULE_TEXTURE_WALL));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), MODULE_TEXTURE_WALL_SEWERS));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), MODULE_TEXTURE_DOOR));
	//m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), MODULE_TEXTURE_DOOR_LOCKED));
	

	return S_OK;
}

_int CTilePalette::Update()
{
	return _int();
}

HRESULT CTilePalette::Render()
{
	float ratio = (float)m_vecTile.size() / PALETTEX * PALETTEY;
	_uint maxPage = 0;
	//소수점자리가 있다면
	if (ratio - (int)ratio > 0)
		//한페이지 더
		maxPage = (int)ratio + 1;

	if (m_iCurrPage > maxPage)
		return E_FAIL;
	
	for (int i = 0; i < PALETTEY; ++i)
	{
		for (int j = 0; j < PALETTEX; ++j)
		{
			_uint index = (m_iCurrPage * PALETTEX * PALETTEY) + j + i * PALETTEX;
			
			if (m_vecTile.size() >= index)
				return E_FAIL;
		
			CModule* pModule = m_vecTile[index]->Get_Module(L"Transform");
			if (!pModule)
				return E_FAIL;

			((CTransform*)pModule)->Set_Position(Vector4(m_fX + j * TILECX, m_fY + i * TILECY));

			m_vecTile[index]->Render();
		}
	}
	return E_NOTIMPL;
}

CTerrain * CTilePalette::Pick_Tile(POINT _pt)
{
	return nullptr;
}

CTilePalette * CTilePalette::Create()
{
	return nullptr;
}
