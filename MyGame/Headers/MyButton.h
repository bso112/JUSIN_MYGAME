#pragma once
#include "GameObject.h"

BEGIN(MyGame)
class CMyButton final : public CGameObject
{
private:
	explicit CMyButton(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device) {};
	explicit CMyButton(CMyButton& _rhs);
	virtual ~CMyButton() = default;

private:
	list<void(*)()> m_listOnClick;
	
public:
	HRESULT Initialize_Prototype(INFO _tInfo);
	HRESULT Initialize(void* _arg);
	_int	Update(_double _timeDelta)	override ;
	HRESULT	Render(HDC _DC) override;
	HRESULT	AddListener(void(*OnClick)());
	
public:
	static CMyButton* Create(PDIRECT3DDEVICE9 _pGraphic_Device, INFO _tInfo);
	// CGameObject을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;

};

END