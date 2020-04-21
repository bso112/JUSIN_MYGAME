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
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_bookshelf"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_bookshelf_remain"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_door"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_door_hidden"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_door_locked"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_burned"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_grass"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_grass_remain"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask1"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask2"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask3"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask4"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask5"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask6"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask7"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask8"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask9"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mold"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_prison"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_prison_opened"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_sign"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_stair_down"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_stair_up"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_statue_rock"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_statue_wood"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_trap_delusion"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_fire"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_orange"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_paralyze"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_poison"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_pupple"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_remain"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_wall"));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_wall_sewer"));

	

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

			((CTransform*)pModule)->Set_Position(Vector4(m_fX + (float)((TILECX >> 1)  + TILECX * j ), m_fY + (float)((TILECY >> 1) + i * TILECY)));

			m_vecTile[index]->Render();
		}
	}
	return S_OK;
}

CTerrain * CTilePalette::Pick_Tile(POINT _pt)
{

	return nullptr;
}

CTilePalette * CTilePalette::Create(PDIRECT3DDEVICE9 _pGraphicDevice)
{
	CTilePalette* pInstance = new CTilePalette(_pGraphicDevice);
	if (FAILED(pInstance->Initalize()))
	{
		MSG_BOX("Fail to create CTilePalette");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTilePalette::Free()
{
	for (auto& tile : m_vecTile)
	{
		Safe_Release(tile);
	}
}
