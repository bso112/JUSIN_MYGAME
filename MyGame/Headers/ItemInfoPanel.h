#pragma once
#include "Image.h"
BEGIN(MyGame)
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
	virtual HRESULT Initialize(Vector3 _vPos);
private:
	vector<CMyButton*>	m_vecBtn;
	CImage*				m_pDescription = nullptr;
	
public:
	void Set_Item(CItem* _pItem);
	HRESULT	Add_ButtonListener(function<void()> _func);
	
public:
	static CItemInfoPanel* Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector3 _vPos);
	// CGameObject을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;
	virtual void Free() override;
};
END
