#pragma once
#include "Character.h"

BEGIN(MyGame)
class CKeyMgr;
class CHero abstract : public CCharacter
{
protected:
	explicit CHero(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CHero(CHero& _hero) : CCharacter(_hero) {}
	virtual ~CHero() = default;

protected:
	CKeyMgr*	m_pKeyMgr = nullptr;
public:
	virtual	HRESULT KeyCheck();



};
END
