#pragma once
#include "Base.h"

BEGIN(MyGame)

#define PALETTEX 5
#define PALETTEY 3
#define PALETTEZ 2




class CTerrain;
class CTilePalette final : public CBase
{
private:
	explicit CTilePalette(PDIRECT3DDEVICE9 _pGraphicDevice) :m_iCurrPage(0) { m_pGraphic_Device = _pGraphicDevice;  }
	virtual ~CTilePalette() = default;

private:
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr; 
	vector<CTerrain*>	m_vecTile;
	_uint				m_iCurrPage = 0;
	//∆»∑π∆Æ¿« øﬁ¬  ¿ß
	float				m_fX;
	float				m_fY;

public:
	HRESULT	Initalize();
	_int	Update();
	HRESULT	Render();

public:
	CTerrain* Pick_Tile(POINT _pt);

public:
	static CTilePalette* Create(PDIRECT3DDEVICE9 _pGraphicDevice);

	// CBase¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void Free() override;
};

END