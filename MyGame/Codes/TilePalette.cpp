#include "stdafx.h"
#include "..\Headers\TilePalette.h"
#include "Terrain.h"
#include "Stair.h"
#include "Door.h"
#include "Transform.h"
#include "TextureLoader.h"
#include "ObjMgr.h"
#include "TileLoader.h"


USING(MyGame)

HRESULT CTilePalette::Initalize()
{
	//텍스쳐 로드
	CTextureLoader::Get_Instance()->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_EDITOR, L"../Bin/Resources/Textures/Terrain/level_one/");

	//팔레트의 왼쪽 위 위치를 정한다.
	m_fX = 0.f;
	m_fY = (float)g_iWinCY - (TILECY * 2);

#pragma region 타일생성

	CTileLoader::CreateTilePrototype(m_pGraphic_Device, SCENE_EDITOR, &m_vecTile);
	for (auto& tile : m_vecTile)
		Safe_AddRef(tile);

#pragma endregion
	

	//타일팔레트 위치 구하기
	//페이지 수 구하기
	float ratio = (float)m_vecTile.size() / (PALETTEX * PALETTEY);
	//소수점자리가 있다면
	if (ratio - (int)ratio > 0)
		//한페이지 더
		m_iMaxPage = (int)ratio + 1;


	for (_uint page = 0; page < m_iMaxPage; ++page)
	{
		//위치정하기
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

