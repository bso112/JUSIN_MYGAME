#pragma once
#include "GameObject.h"

#define DIALOG_PANELCX 600
#define DIALOG_PANELCY 200
#define DIALOG_ICONCX	100
#define	DIALOG_ICONCY	100
#define	DIALOG_PADDING 20
BEGIN(MyGame)
class CImage;
class CDialogPanel final :public CGameObject
{
private:
	explicit CDialogPanel(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CDialogPanel(CDialogPanel& _rhs);
	virtual ~CDialogPanel() = default;

private:
	CImage*	m_pPanel = nullptr;
	CImage*	m_pIcon = nullptr;
	MYFONT	m_tFont[2];

public:
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

protected:
	virtual	void OnSetActive(_bool _bActive);
public:
	static CDialogPanel * Create(PDIRECT3DDEVICE9 _pGrahic_Device);
	virtual CGameObject * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};
END
