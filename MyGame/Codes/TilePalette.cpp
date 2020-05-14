#include "stdafx.h"
#include "..\Headers\TilePalette.h"
#include "Terrain.h"
#include "Stair.h"
#include "Door.h"
#include "Transform.h"
#include "TextureLoader.h"
#include "ObjMgr.h"


USING(MyGame)

HRESULT CTilePalette::Initalize()
{
	//�ؽ��� �ε�
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_EDITOR, L"../Bin/Resources/Textures/Terrain/level_one/");

	//�ȷ�Ʈ�� ���� �� ��ġ�� ���Ѵ�.
	m_fX = 0.f;
	m_fY = (float)g_iWinCY - (TILECY * 2);

#pragma region Ÿ�ϻ���

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	//�ȷ�Ʈ�� �� Ÿ��(������Ÿ��)�� �����.
	CTerrain* pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_bookshelf", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_bookshelf", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CDoor::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_door", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_door", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_floor", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_floor_burned", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_burned", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_floor_grass", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_grass", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_A", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_A", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_B", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_B", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_C", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_C", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_D", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_D", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_E", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_E", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_F", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_F", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_G", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_G", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_H", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_H", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_floor_mask_I", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mask_I", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_floor_mold", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_floor_mold", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_prison", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_prison", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_sign", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_sign", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CStair::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_stair", SCENE_EDITOR, L"stair");
	pObjMgr->Add_Prototype(L"lv_One_stair", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_statue_rock", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_statue_rock", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_statue_wood", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_statue_wood", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_trap_delusion", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_trap_delusion", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_trap_fire", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_trap_fire", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_trap_orange", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_trap_orange", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_trap_paralyze", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_trap_paralyze", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_trap_poison", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_trap_poison", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_trap_pupple", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_trap_pupple", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(true), L"lv_One_trap_remain", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_trap_remain", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_wall", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_wall", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);
	pTerrain = CTerrain::Create(m_pGraphic_Device, TERRAIN(false), L"lv_One_wall_sewer", SCENE_EDITOR);
	pObjMgr->Add_Prototype(L"lv_One_wall_sewer", SCENE_EDITOR, pTerrain); m_vecTile.push_back(pTerrain); Safe_AddRef(pTerrain);

	
#pragma endregion
	

	//Ÿ���ȷ�Ʈ ��ġ ���ϱ�
	//������ �� ���ϱ�
	float ratio = (float)m_vecTile.size() / (PALETTEX * PALETTEY);
	//�Ҽ����ڸ��� �ִٸ�
	if (ratio - (int)ratio > 0)
		//�������� ��
		m_iMaxPage = (int)ratio + 1;


	for (_uint page = 0; page < m_iMaxPage; ++page)
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
	int x = int(_pt.x - m_fX)/ (TILECX);
	int y = int(_pt.y - m_fY)/ (TILECY) - 1;

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
	Safe_Release(m_pGraphic_Device);
}

