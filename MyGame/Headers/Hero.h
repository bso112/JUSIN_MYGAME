#pragma once
#include "Character.h"

BEGIN(MyGame)
class CKeyMgr;
class CHero abstract : public CCharacter
{
protected:
	enum CLOTH	{ CLOTH_NAKED, CLOTH_BASIC, CLOTH_LEATHER, CLOTH_END};

protected:
	CLOTH		m_eCurrCloth = CLOTH_BASIC;
	CAnimator*	m_pAnimator[CLOTH_END];

protected:
	Vector3		m_vDst = {};

public:
	virtual	_int	Interact(CGameObject* _pOther);
	
public:
	HRESULT	PlayAnimation(const _tchar* _pTag);
	_bool	Has_Key(TIER _tier);

protected:
	explicit CHero(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CHero(CHero& _hero);
	virtual ~CHero() = default;

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	//히어로가 위치할 처음 위치를 구한다.
	HRESULT	Set_InitialPos();
	
public:
	virtual void Free() override;


};
END
