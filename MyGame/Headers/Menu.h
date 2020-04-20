#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CMyButton;
class CImage;
class CMenu final : public CScene
{
private:
	explicit CMenu(PDIRECT3DDEVICE9 _pGraphic_Device) : CScene(_pGraphic_Device) {};
	virtual ~CMenu() = default;
	
public:
	virtual HRESULT Initalize() override;
	virtual _int Update(_double _timeDelta) override;
	virtual HRESULT Render() override;

private:
	CImage*				m_pImgLogo = nullptr;
	vector<CMyButton*>  m_vecBtn;



public:
	static CMenu* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CScene을(를) 통해 상속됨
	virtual void Free() override;
private:
	HRESULT Initalize_Prototypes();
	HRESULT	Initalize_Layers();
};

END