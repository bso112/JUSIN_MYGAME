#pragma once
#include "GameObject.h"

#define DIALOG_PANELCX 500
#define DIALOG_PANELCY 250
#define DIALOG_ICONCX	50
#define	DIALOG_ICONCY	50
#define	DIALOG_PADDING 35
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

public:
	HRESULT	Set_Speacker(const _tchar* _pIconTextureTag, SCENEID _eTextureSceneID, const _tchar* _pSpeakerName, const _tchar* _pDialog);
	RECT	Get_Rect();
protected:
	virtual	void OnSetActive(_bool _bActive);
	virtual HRESULT	OnKeyDown(_int KeyCode);
public:
	static CDialogPanel * Create(PDIRECT3DDEVICE9 _pGrahic_Device);
	virtual CGameObject * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};
END
