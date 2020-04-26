#include "stdafx.h"
#include "..\Headers\TilePalette.h"
#include "Terrain.h"
#include "Transform.h"
#include "TextureLoader.h"
USING(MyGame)

HRESULT CTilePalette::Initalize()
{
	//�ؽ��� �ε�
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_EDITOR, L"../Bin/Resources/Textures/Terrain/level1/");

	//�ȷ�Ʈ�� ���� �� ��ġ�� ���Ѵ�.
	m_fX = 0.f;
	m_fY = (float)g_iWinCY - (TILECY * 2);

#pragma region Ÿ�ϻ���


	//�ȷ�Ʈ�� �� Ÿ���� �����.
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_bookshelf", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_bookshelf_remain", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_door", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_door_hidden", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_door_locked", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_burned", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_grass", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_grass_remain", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask1", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask2", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask3", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask4", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask5", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask6", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask7", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask8", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mask9", SCENE_EDITOR));

	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_floor_mold", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_prison", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_prison_opened", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_sign", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_stair_down", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_stair_up", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_statue_rock", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_statue_wood", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_trap_delusion", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_fire", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_orange", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_paralyze", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_poison", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_pupple", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv1_trap_remain", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_wall", SCENE_EDITOR));
	m_vecTile.push_back(CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv1_wall_sewer", SCENE_EDITOR));


#pragma endregion


	//������ �� ���ϱ�
	float ratio = (float)m_vecTile.size() / (PALETTEX * PALETTEY);
	//�Ҽ����ڸ��� �ִٸ�
	if (ratio - (int)ratio > 0)
		//�������� ��
		m_iMaxPage = (int)ratio + 1;


	for (int page = 0; page < m_iMaxPage; ++page)
	{
		//��ġ���ϱ�
		for (int i = 0; i < PALETTEY; ++i)
		{
			for (int j = 0; j < PALETTEX; ++j)
			{
				_uint index = (page * PALETTEX * PALETTEY) + j + i * PALETTEX;

				if (m_vecTile.size() <= index)
					break;

				CModule* pModule = m_vecTile[index]->Get_Module(L"Transform");
				if (!pModule)
					return E_FAIL;

				((CTransform*)pModule)->Set_Position(Vector4(m_fX + (float)((TILECX >> 1) + TILECX * j), m_fY + (float)((TILECY >> 1) + i * TILECY)));

			}
		}
	}

	return S_OK;
}

_int CTilePalette::Update()
{
	return _int();
}

HRESULT CTilePalette::Render()
{
	for (int i = 0; i < PALETTEY; ++i)
	{
		for (int j = 0; j < PALETTEX; ++j)
		{
			int index = (m_iCurrPage * PALETTEX * PALETTEY) + j + (PALETTEX * i);

			if (m_vecTile.size() <= index)
				break;

			m_vecTile[index]->Render();
		}
	}
	return S_OK;
}

CGameObject* CTilePalette::Pick_Tile(POINT _pt)
{
	int x = (_pt.x - m_fX)/ (TILECX);
	int y = (_pt.y - m_fY)/ (TILECY) - 1;

	size_t index = x + y * PALETTEX;

	if (index < 0 || index >= m_vecTile.size())
		return nullptr;
	
	return m_vecTile[index]->Clone();
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
