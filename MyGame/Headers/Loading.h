#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CMyButton;
class CTileMgr;
class CLoading final : public CScene
{
private:
	explicit CLoading(PDIRECT3DDEVICE9 _pGraphic_Device) : CScene(_pGraphic_Device) {};
	virtual ~CLoading() = default;
	
	virtual HRESULT Initalize() override;
	virtual _int Update(_double _timeDelta) override;
	virtual HRESULT Render() override;
	virtual	HRESULT	Render(HDC _DC) override;

public:
	static CLoading* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CScene을(를) 통해 상속됨
	virtual void Free() override;
private:
	HRESULT Initalize_Prototypes();
	HRESULT	Initalize_Layers();
};

END