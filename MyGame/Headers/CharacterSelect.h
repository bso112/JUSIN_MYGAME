#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CImage;
class CMyButton;
class CCharacterSelect final : public CScene
{
private:
	explicit CCharacterSelect(PDIRECT3DDEVICE9 _pGraphicDevice) :CScene(_pGraphicDevice) {};
	virtual ~CCharacterSelect() = default;


private:
	CImage*				m_pImgLogo = nullptr;
	vector<CMyButton*>	m_vecBtn;

public:
	virtual HRESULT Initialize() override;
	virtual _int Update(_double _timeDelta) override;
	virtual HRESULT Render() override;
	
private:
	HRESULT	Load_Textures();

public:
	static CCharacterSelect* Create(PDIRECT3DDEVICE9 _pGraphicDevice);
};

END