#pragma once
#include "Image.h"
BEGIN(MyGame)
#define PANELX 500.f
#define PANLEY 300.f
#define PADDING 30.f
#define MARGIN_BUTTON 10
#define BUTTONCX 120.f
#define BUTTONCY 40.f
//열
#define TEXT_ROW 2
//행
#define TEXT_COL 5

class CMyButton;
class CHero;
class CStatsPanel final : public CImage
{
private:
	explicit CStatsPanel(PDIRECT3DDEVICE9 _pGraphic_Device) : CImage(_pGraphic_Device) {  }
	explicit CStatsPanel(CStatsPanel& _rhs) : CImage(_rhs) {  };
	virtual ~CStatsPanel() = default;


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void * _param);
	virtual	void	OnSetActive(bool _bActive) override;
	virtual	HRESULT	Render() override; 
private:
	vector<CMyButton*>	m_vecBtn;
	MYFONT		m_Texts[TEXT_ROW][TEXT_COL];
public:
	void Set_Player();
	HRESULT	Add_ButtonListener(function<void()> _func);

public:
	static CStatsPanel* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CGameObject을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;
	virtual void Free() override;
};
END
