#pragma once
#include "Base.h"

BEGIN(MyGame)

#define PALETTEX 20
#define PALETTEY 2
#define PALETTEZ 2




class CTerrain;
class CGameObject;
// 타일들에 대한 원본을 가지고 있다. 오브젝트 매니저에 그 원본들을 등록하기도 함.
class CTilePalette final : public CBase
{
private:
	explicit CTilePalette(PDIRECT3DDEVICE9 _pGraphicDevice) :m_iCurrPage(0) { Safe_AddRef(m_pGraphic_Device); m_pGraphic_Device = _pGraphicDevice; }
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
	//해당 위치에 있는 원본타일을 clone해서 넘겨준다.
	CGameObject* Pick_Tile(POINT _pt);


public:
	static CTilePalette* Create(PDIRECT3DDEVICE9 _pGraphicDevice);

	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};

END