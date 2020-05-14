#pragma once
#include "Character.h"

BEGIN(MyGame)
class CKeyMgr;
class CHero abstract : public CCharacter
{
protected:
	enum CLOTH	{ CLOTH_NAKED, CLOTH_BASIC, CLOTH_LEATHER, CLOTH_END};

protected:
	CKeyMgr*	m_pKeyMgr = nullptr;
	CLOTH		m_eCurrCloth = CLOTH_BASIC;
	CAnimator*	m_pAnimator[CLOTH_END];

protected:
	Vector3		m_vDst = {};

protected:
	explicit CHero(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CHero(CHero& _hero);
	virtual ~CHero() = default;

protected:
	virtual	HRESULT KeyCheck(_double _timeDelta);
	HRESULT	Set_InitialPos();
	

public:
	HRESULT	PlayAnimation(const _tchar* _pTag);
	_bool	Has_Key(TIER _tier);

public:
	virtual void Free() override;


};
END
