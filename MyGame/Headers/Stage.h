#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CTileMgr;
class CMyButton;
class CStage final : public CScene
{
private:
	explicit CStage(PDIRECT3DDEVICE9 _pGraphic_Device) : CScene(_pGraphic_Device) {};
	virtual ~CStage() = default;

public:
	virtual HRESULT Initalize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();
	virtual	HRESULT	Render(HDC _DC);


private:
	CMyButton*	m_pBtn;
	CTileMgr*	m_pTileMgr;


private:
	HRESULT	Initalize_Tile();
	HRESULT Initalize_Prototypes();
	HRESULT	Initalize_Layers();

public:
	virtual void Free() override;
};
END
