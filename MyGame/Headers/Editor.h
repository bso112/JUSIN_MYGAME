#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CTilePalette;
class CEditor final: public CScene
{
private:
	explicit CEditor(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CEditor() = default;


public:
	virtual HRESULT Initalize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();

private:
	CTilePalette* m_pPalette = nullptr;


public:
	static CEditor* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CBase을(를) 통해 상속됨
	virtual void Free() override;




};
END
