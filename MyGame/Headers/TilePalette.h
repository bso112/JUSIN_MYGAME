#pragma once
#include "Base.h"

BEGIN(MyGame)

#define PALETTEX 20
#define PALETTEY 2
#define PALETTEZ 2




class CTerrain;
class CGameObject;
// Ÿ�ϵ鿡 ���� ������ ������ �ִ�. ������Ʈ �Ŵ����� �� �������� ����ϱ⵵ ��.
class CTilePalette final : public CBase
{
private:
	explicit CTilePalette(PDIRECT3DDEVICE9 _pGraphicDevice) :m_iCurrPage(0) { Safe_AddRef(m_pGraphic_Device); m_pGraphic_Device = _pGraphicDevice; }
	virtual ~CTilePalette() = default;

private:
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr; 
	vector<CTerrain*>	m_vecTile;
	_uint				m_iCurrPage = 0;
	//�ȷ�Ʈ�� ���� ��
	float				m_fX;
	float				m_fY;
	//�ִ� ������ ��
	_uint				m_iMaxPage = 0;

public:
	HRESULT	Initalize();
	_int	Update();
	HRESULT	Render();

public:
	//�ش� ��ġ�� �ִ� ����Ÿ���� clone�ؼ� �Ѱ��ش�.
	CGameObject* Pick_Tile(POINT _pt);


public:
	static CTilePalette* Create(PDIRECT3DDEVICE9 _pGraphicDevice);

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END