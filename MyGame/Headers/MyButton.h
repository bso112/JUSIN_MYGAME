#pragma once
#include "GameObject.h"

BEGIN(MyGame)
class CVIBuffer;
class CTransform;
class CTexture;
class CMyButton final : public CGameObject
{
public:
	enum TAG { BTN_CHARACTER_SELECT, BTN_GAMESATART,BTN_EDITOR, BTN_QUIT, BTN_END};
private:
	explicit CMyButton(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device) {};
	explicit CMyButton(CMyButton& _rhs);
	virtual ~CMyButton() = default;


private:
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTransform*	m_pTransform = nullptr;
	CTexture*	m_pTexture = nullptr;
	RECT		m_tRect = {};
	TAG			m_eBtnTag = {};
public:
	HRESULT Initialize(Vector4 _vPos, Vector2 _vSize, CMyButton::TAG _eTag, _tchar* _pTextureTag);
	_int	Update(_double _timeDelta)	override;
	HRESULT	Render();
	
public:
	static CMyButton*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, CMyButton::TAG _eTag, _tchar* _pTextureTag);
public:
	virtual CGameObject * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END