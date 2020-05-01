#pragma once
#include "Character.h"

BEGIN(MyGame)
class CKeyMgr;
class CHero abstract : public CCharacter
{
protected:
	enum CLOTH	{ CLOTH_NAKED, CLOTH_BASIC, CLOTH_LEATHER, CLOTH_END};
	enum ANIM	{ ANIM_IDLE, ANIM_WALK, ANIM_ATTACK, ANIM_EAT,ANIM_USE, ANIM_FLOATING, ANIM_END };

protected:
	CKeyMgr*	m_pKeyMgr = nullptr;

protected:
	explicit CHero(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CHero(CHero& _hero) : CCharacter(_hero) {}
	virtual ~CHero() = default;

public:
	virtual	HRESULT KeyCheck();


public:
	_bool	Has_Key(TIER _tier);

public:
	virtual void Free() override;


};
END
