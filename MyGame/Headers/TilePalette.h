#pragma once
#include "Base.h"

BEGIN(MyGame)

#define PALETTEX 20
#define PALETTEY 2
#define PALETTEZ 2




class CTerrain;
class CGameObject;
class CTilePalette final : public CBase
{
private:
	explicit CTilePalette(PDIRECT3DDEVICE9 _pGraphicDevice) :m_iCurrPage(0) { m_pGraphic_Device = _pGraphicDevice;  }
	virtual ~CTilePalette() = default;

private:
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr; 
	vector<CTerrain*>	m_vecTile;
	_uint				m_iCurrPage = 0;
	//팔레트의 왼쪽 위
	float				m_fX;
	float				m_fY;
	//최대 페이지 수
	_uint				m_iMaxPage = 0;

public:
	HRESULT	Initalize();
	_int	Update();
	HRESULT	Render();

public:
	CGameObject* Pick_Tile(POINT _pt);

public:
	static CTilePalette* Create(PDIRECT3DDEVICE9 _pGraphicDevice);

	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};

END