#pragma once
#include "Image.h"
BEGIN(MyGame)
#define PANELX 500.f
#define PANLEY 300.f
#define PADDING_LEFT 30.f
#define PADDING_TOP 260.f
#define MARGIN_BUTTON 10
#define BUTTONCX 130.f
#define BUTTONCY 50.f

class CItem;
class CMyButton;
class CImage;
class CItemInfoPanel final : public CImage
{
private:
	explicit CItemInfoPanel(PDIRECT3DDEVICE9 _pGraphic_Device) : CImage(_pGraphic_Device) {}
	explicit CItemInfoPanel(CItemInfoPanel& _rhs) : CImage(_rhs) {};
	virtual ~CItemInfoPanel() = default;


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void * _param);
	virtual	void	OnSetActive(bool _bActive) override;
private:
	vector<CMyButton*>	m_vecBtn;
	CImage*				m_pDescription = nullptr;
	CImage*				m_pItemNameText = nullptr;
	CImage*				m_pItemIcon = nullptr;

	
public:
	void Set_Item(CItem* _pItem);
	HRESULT	Add_ButtonListener(function<void()> _func);
	
protected:
	virtual HRESULT	OnKeyDown(_int KeyCode);
public:
	static CItemInfoPanel* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CGameObject을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;
	virtual void Free() override;
};
END
